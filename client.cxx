#include <memory>
#include <QObject>
#include <icclient/typedefs.h>
#include "qicclient.hxx"
#include "qicclient/ord.hxx"

static QICClient::Client *client;

static void callback(icclient_catalog* catalog)
{
	client->emitCatalog(catalog);
	icclient_free_catalog(catalog);
}

namespace QICClient {

	Client::Client(char const* url, char const* certificate)
	{
		client = this;
		icclient_init(url, certificate);
	}

	Client::~Client()
	{
		icclient_cleanup();
	}

	void Client::results(QString const& prodGroup, icclient_handler handler)
	{
		icclient_results(prodGroup.toLatin1().constData(), callback, handler);
	}

	void Client::allProducts(icclient_handler handler)
	{
		icclient_allproducts(callback, handler);
	}

	void Client::emitCatalog(icclient_catalog* catalog)
	{
		emit gotResults(new Catalog{catalog});
	}

	void Client::flyPage(QString const& sku,icclient_handler handler)
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
