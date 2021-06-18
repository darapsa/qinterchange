#include <cstddef>
#include <memory>
#include <QObject>
#include "qicclient.hxx"
#include "qicclient/ord.hxx"

namespace QICClient {

	static Client* client;

	static void resultsHandler(icclient_response* response)
	{
		client->emitResults(QString{response->data});
		icclient_free_response(response);
	}

	static void catalogCallback(icclient_catalog* catalog)
	{
		client->emitCatalog(new Catalog{catalog});
		icclient_free_catalog(catalog);
	}

	Client::Client(char const* sampleURL, char const* image_Dir, char const* certificate)
	{
		client = this;
		icclient_init(sampleURL, image_Dir, certificate);
	}

	Client::~Client()
	{
		icclient_cleanup();
	}

	void Client::results(QString const& prodGroup)
	{
		icclient_results(prodGroup.toLatin1().constData(), resultsHandler, nullptr);
	}

	void Client::allProducts()
	{
		icclient_allproducts(resultsHandler, nullptr);
	}

	void Client::strapResults(QString const& prodGroup)
	{
		icclient_results(prodGroup.toLatin1().constData(), nullptr, catalogCallback);
	}

	void Client::strapAllProducts()
	{
		icclient_allproducts(nullptr, catalogCallback);
	}

	void Client::emitResults(QString const& results)
	{
		emit gotResults(results);
	}

	void Client::emitCatalog(Catalog* catalog)
	{
		emit gotCatalog(catalog);
	}

	void Client::flyPage(QString const& sku,void (*handler)(icclient_response*))
	{
		icclient_product* product = nullptr;
		icclient_flypage(sku.toLatin1().constData(), handler, &product);
		if (product) emit gotFlyPage(shared_ptr<Product>{new Product{product}});
	}

	void Client::order(QString const& sku, Catalog const& catalog, Ord& order)
	{
		auto c_order = order.data();
		icclient_ord_order(sku.toLatin1().constData(), catalog.constData(),
				&c_order);
		order.setData(c_order);
	}

}
