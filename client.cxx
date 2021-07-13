#include "qicclient.hxx"
#include "qicclient/ord.hxx"

namespace QICClient {

	static Client* client;

	Client::Client(char const* sampleURL, char const* image_Dir, char const* certificate)
	{
		client = this;
		icclient_init(sampleURL, image_Dir, certificate);
	}

	Client::~Client()
	{
		icclient_cleanup();
	}

	void Client::catalog(QString const& prodGroup)
	{
		icclient_catalog(prodGroup.toLatin1().constData(), [](icclient_response* response) {
			client->emitCatalog(QString{response->data});
			icclient_free_response(response);
		}, nullptr);
	}

	void Client::allProducts()
	{
		catalog("All-Products");
	}

	void Client::product(QString const& sku)
	{
		icclient_product(sku.toLatin1().constData(), [](icclient_response* response) {
			client->emitProduct(QString{response->data});
			icclient_free_response(response);
		}, nullptr);
	}

	void Client::page(QString const& path)
	{
		icclient_page(path.toLatin1().constData(), [](icclient_response* response) {
			client->emitPage(QString{response->data});
			icclient_free_response(response);
		});
	}

	void Client::defaultCatalog(QString const& prodGroup)
	{
		icclient_catalog(prodGroup.toLatin1().constData(), nullptr, [](struct icclient_catalog* catalog) {
			icclient_free_catalog(catalog);
		});
	}

	void Client::defaultAllProducts()
	{
		defaultCatalog("All-Products");
	}

	void Client::emitCatalog(QString const& response)
	{
		emit gotCatalog(response);
	}

	void Client::emitProduct(QString const& response)
	{
		emit gotProduct(response);
	}

	void Client::emitPage(QString const& response)
	{
		emit gotPage(response);
	}

	void Client::order(QString const& sku, Catalog const& catalog, Ord& order)
	{
		auto c_order = order.data();
		icclient_ord_order(sku.toLatin1().constData(), catalog.constData(), &c_order);
		order.setData(c_order);
	}

}
