#include <cstddef>
#include <memory>
#include <QObject>
#include "qicclient.hxx"
#include "qicclient/ord.hxx"

static QICClient::Client* client;

static void handleResults(icclient_fetch_t* fetch)
{
	client->emitResults(fetch);
}

static void callback(icclient_catalog* catalog)
{
	client->emitCatalog(catalog);
	icclient_free_catalog(catalog);
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
		icclient_results(prodGroup.toLatin1().constData(), handleResults, nullptr);
	}
/*
	void Client::results(QString const& prodGroup, void (*handler)(icclient_fetch_t*))
	{
		icclient_results(prodGroup.toLatin1().constData(), handler, callback);
	}
*/
	void Client::allProducts()
	{
		icclient_allproducts(handleResults, nullptr);
	}

	void Client::allproducts(void (*handler)(icclient_fetch_t* fetch))
	{
		icclient_allproducts(handler, callback);
	}

	void Client::emitResults(icclient_fetch_t* fetch)
	{
		emit gotResults(fetch);
	}

	void Client::emitCatalog(icclient_catalog* catalog)
	{
		emit gotCatalog(new Catalog{catalog});
	}

	void Client::flyPage(QString const& sku,void (*handler)(icclient_fetch_t*))
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
