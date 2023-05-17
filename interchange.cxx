#include "interchange.hxx"
#include "interchange/ord.hxx"

namespace QInterchange {

	static Interchange* interchange;
	static int sampleUrlLength = 0;
	static char *mv_sku = nullptr, *mv_order_item = nullptr;

	Interchange::Interchange(const char* sampleURL, const char* image_Dir,
			const QString& cookie, const QString& certificate)
	{
		interchange = this;
#ifndef __EMSCRIPTEN__
		auto length = strlen(sampleURL);
		sampleUrlLength = length + (sampleURL[length - 1] != '/');
#endif
		interchange_init(sampleURL, image_Dir,
				cookie.isEmpty() ? nullptr
				: cookie.toLatin1().constData(),
				certificate.isEmpty() ? nullptr
				: certificate.toLatin1().constData());
	}

	Interchange::~Interchange()
	{
		interchange_cleanup();
	}

	void Interchange::page(QString const& path)
	{
		interchange_page(path.toLatin1().constData(),
				[](interchange_response* response) {
			interchange->emitPage(QString{response->url}
					.remove(0, sampleUrlLength),
					QString{response->data});
			interchange_free_response(response);
		});
	}

	void Interchange::catalog(QString const& prodGroup)
	{
		interchange_catalog(prodGroup.toLatin1().constData(), [](interchange_response* response) {
			interchange->emitCatalog(QString{response->data});
			interchange_free_response(response);
		}, nullptr);
	}

	void Interchange::allProducts()
	{
		catalog("All-Products");
	}

	void Interchange::product(QString const& sku)
	{
		interchange_product(sku.toLatin1().constData(), [](interchange_response* response) {
			interchange->emitProduct(QString{response->data});
			interchange_free_response(response);
		}, nullptr);
	}

	void Interchange::defaultCatalog(QString const& prodGroup)
	{
		interchange_catalog(prodGroup.toLatin1().constData(), nullptr, [](struct interchange_catalog* catalog) {
			interchange_free_catalog(catalog);
		});
	}

	void Interchange::defaultAllProducts()
	{
		defaultCatalog("All-Products");
	}

	void Interchange::order(const QString &sku, const QString &item,
			const int quantity, const QVariant &options)
	{
		mv_sku = (char *)malloc(sku.size() + 1);
		strcpy(mv_sku, sku.toLatin1().constData());
		if (item.isEmpty()) {
			mv_order_item = (char *)malloc(sku.size() + 1);
			strcpy(mv_order_item, sku.toLatin1().constData());
		} else {
			mv_order_item = (char *)malloc(item.size() + 1);
			strcpy(mv_order_item, item.toLatin1().constData());
		}
		auto opts = options.toList();
		auto size = opts.size();
		const char *mv_order_s[size + 1][2];
		for (int i = 0; i < size; i++) {
			auto pair = opts.at(i).toList();
			mv_order_s[i][0] = pair.at(0)
				.toByteArray().constData();
			mv_order_s[i][1] = pair.at(1)
				.toByteArray().constData();
		}
		mv_order_s[size][0] = nullptr;
		interchange_ord_order(mv_sku, mv_order_item, quantity,
				mv_order_s, [](interchange_response *response) {
			free(mv_sku);
			mv_sku = nullptr;
			free(mv_order_item);
			mv_order_item = nullptr;
			interchange->emitOrder(QString{response->data});
			interchange_free_response(response);
		});
	}

	void Interchange::emitPage(QString const& path, QString const& response)
	{
		emit gotPage(path, response);
	}

	void Interchange::emitCatalog(QString const& response)
	{
		emit gotCatalog(response);
	}

	void Interchange::emitProduct(QString const& response)
	{
		emit gotProduct(response);
	}

	void Interchange::emitOrder(const QString &response)
	{
		emit gotOrder(response);
	}
}
