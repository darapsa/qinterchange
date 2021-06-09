#include <cstddef>
#include <memory>
#include <QObject>
#include <icclient/typedefs.h>
#include <icclient/client.h>
#include "qicclient/catalog.hxx"
#ifndef __EMSCRIPTEN__
#include "qicclient/ord.hxx"
#endif
#include "qicclient/client.hxx"

namespace QICClient {

	Client::Client(char const* url, char const* certificate)
	{
		icclient_init(url, certificate);
	}

	Client::~Client()
	{
		icclient_cleanup();
	}

	void Client::results(QString const& prodGroup, icclient_handler handler)
	{
		icclient_catalog* catalog = nullptr;
		icclient_results(prodGroup.toLatin1().constData(), handler, &catalog);
		if (catalog) emit gotResults(new Catalog{catalog});
	}

	void Client::allProducts(icclient_handler handler)
	{
		icclient_catalog* catalog = nullptr;
		icclient_allproducts(handler, &catalog);
		if (catalog) emit gotResults(new Catalog{catalog});
	}

	void Client::flyPage(QString const& sku,icclient_handler handler)
	{
		icclient_product* product = nullptr;
		icclient_flypage(sku.toLatin1().constData(), handler, &product);
		if (product) emit gotFlyPage(shared_ptr<Product>{new Product{product}});
	}

#ifndef __EMSCRIPTEN__
	void Client::order(QString const& sku, Catalog const& catalog, Ord& order)
	{
		auto c_order = order.data();
		icclient_ord_order(sku.toLatin1().constData(), catalog.constData(),
				&c_order);
		order.setData(c_order);
	}
#endif

}
