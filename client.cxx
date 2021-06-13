#include <cstddef>
#include <memory>
#include <QObject>
#include "qicclient.hxx"
#include "qicclient/ord.hxx"

static QICClient::Client* client;

static void handle_results(icclient_fetch_t* fetch)
{
	client->emitResults(fetch);
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

	void Client::results(QString const& prodGroup)
	{
		icclient_results(prodGroup.toLatin1().constData(), [](icclient_catalog* catalog) {
				icclient_free_catalog(catalog);
				}, handle_results);
	}

	void Client::allProducts()
	{
		icclient_allproducts([](icclient_catalog* catalog) {
				icclient_free_catalog(catalog);
				}, handle_results);
	}

	void Client::emitResults(icclient_fetch_t* fetch)
	{
		emit gotResults(fetch);
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
