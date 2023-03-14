#include "interchange.hxx"
#include "interchange/ord.hxx"

namespace QInterchange {

	static Interchange* interchange;

	Interchange::Interchange(const char* sampleURL, const char* image_Dir,
			const QString& cookie, const QString& certificate)
	{
		interchange = this;
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

	void Interchange::flypage(QString const& path)
	{
		interchange_flypage(path.toLatin1().constData(),
				[](interchange_response* response) {
			interchange->emitFlypage(QString{response->data});
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

	void Interchange::emitFlypage(QString const& response)
	{
		emit gotFlypage(response);
	}

	void Interchange::emitCatalog(QString const& response)
	{
		emit gotCatalog(response);
	}

	void Interchange::emitProduct(QString const& response)
	{
		emit gotProduct(response);
	}

	void Interchange::emitOrder(QString const& response)
	{
		emit gotOrder(response);
	}

	void Interchange::order(QString const& sku)
	{
		interchange_ord_order(sku.toLatin1().constData(),
				[](interchange_response* response) {
			interchange->emitOrder(QString{response->data});
			interchange_free_response(response);
		});
	}
}
