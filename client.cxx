#include <cstddef>
#include <memory>
#include <QObject>
#include <icclient/client.h>
#include <icclient/member.h>
#include "qicclient/catalog.hxx"
#include "qicclient/basket.hxx"
#include "qicclient/client.hxx"

namespace ICClient {

	Client::Client(char const* url, char const* certificate)
	{
		icclient_init(url, certificate);
	}

	Client::~Client()
	{
		icclient_cleanup();
	}

	void Client::results(size_t (*handler)(void* contents, size_t size,
				size_t nmemb, void* userdata),
			QString const& prodGroup)
	{
		icclient_catalog* catalog = nullptr;
		icclient_results(handler, &catalog, prodGroup.toLatin1().constData());
		if (catalog) emit gotResults(new Catalog{catalog});
	}

	void Client::allProducts(size_t (*handler)(void*, size_t, size_t, void*))
	{
		icclient_catalog* catalog = nullptr;
		icclient_allproducts(handler, &catalog);
		if (catalog) emit gotResults(new Catalog{catalog});
	}

	void Client::flyPage(size_t (*handler)(void* contents, size_t size,
				size_t nmemb, void* userdata),
			QString const& sku)
	{
		icclient_product* product = nullptr;
		icclient_flypage(handler, &product, sku.toLatin1().constData());
		if (product) emit gotFlyPage(shared_ptr<Product>{new Product{product}});
	}

	void Client::order(QString const& sku, Catalog const& catalog, Basket& order)
	{
		auto c_order = order.c_order();
		icclient_order(sku.toLatin1().constData(), catalog.c_catalog(), &c_order);
		order.update(c_order);
	}

	void Client::logIn(size_t (*handler)(void*, size_t, size_t, void*)
			, icclient_user* user, QString const& username
			, QString const& password, QString const& successPage
			, QString const& nextPage, QString const& failPage)
	{
		icclient_login(handler, user, username.toLatin1().constData()
				, password.toLatin1().constData()
				, successPage.toLatin1().constData()
				, nextPage.toLatin1().constData()
				, failPage.toLatin1().constData());
		emit loggedIn(user);
	}

	void Client::logOut()
	{
		icclient_logout();
		emit loggedOut();
	}

}
