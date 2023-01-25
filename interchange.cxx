#include "interchange.hxx"
#include "interchange/ord.hxx"

namespace QInterchange {

	static Interchange* interchange;

	Interchange::Interchange(char const* sampleURL, char const* image_Dir,
			char const* cookie, char const* certificate)
	{
		interchange = this;
		interchange_init(sampleURL, image_Dir, cookie, certificate);
	}

	Interchange::~Interchange()
	{
		interchange_cleanup();
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

	void Interchange::page(QString const& path)
	{
		interchange_page(path.toLatin1().constData(), [](interchange_response* response) {
			interchange->emitPage(QString{response->data});
			interchange_free_response(response);
		});
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

	void Interchange::emitCatalog(QString const& response)
	{
		emit gotCatalog(response);
	}

	void Interchange::emitProduct(QString const& response)
	{
		emit gotProduct(response);
	}

	void Interchange::emitPage(QString const& response)
	{
		emit gotPage(response);
	}

	void Interchange::order(QString const& sku, Catalog const& catalog, Ord& order)
	{
		auto c_order = order.data();
		interchange_ord_order(sku.toLatin1().constData(), catalog.constData(), &c_order);
		order.setData(c_order);
	}

}
