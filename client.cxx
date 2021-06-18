#include <cstddef>
#include <memory>
#include <QObject>
#include "qicclient.hxx"
#include "qicclient/ord.hxx"

static QICClient::Client* client;

static void responseHandler(icclient_response* response)
{
	client->emitResponse(response);
}

static void catalogCallback(icclient_catalog* catalog)
{
	client->emitCatalog(catalog);
}

namespace QICClient {

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
		icclient_results(prodGroup.toLatin1().constData(), responseHandler, nullptr);
	}

	void Client::allProducts()
	{
		icclient_allproducts(responseHandler, nullptr);
	}

	void Client::strapResults(QString const& prodGroup)
	{
		icclient_results(prodGroup.toLatin1().constData(), nullptr, catalogCallback);
	}

	void Client::strapAllProducts()
	{
		icclient_allproducts(nullptr, catalogCallback);
	}

	void Client::emitResponse(icclient_response* response)
	{
		emit gotResults(QString{response->data});
		icclient_free_response(response);
	}

	void Client::emitCatalog(icclient_catalog* catalog)
	{
		emit gotCatalog(new Catalog{catalog});
		icclient_free_catalog(catalog);
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
