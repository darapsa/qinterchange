#include <cstddef>
#include <icclient/client.h>
#include <icclient/member.h>
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

	void Client::allProducts(size_t (*handler)(void*, size_t, size_t, void*))
	{
		icclient_catalog* catalog = nullptr;
		icclient_allproducts(handler, &catalog);
		emit gotAllProducts(catalog);
	}

	void Client::order(icclient_ord_order** orderPtr, QString const& sku
			, icclient_catalog* catalog)
	{
		icclient_order(orderPtr, sku.toLatin1().constData(), catalog);
		icclient_ord_order* order = *orderPtr;
		emit ordered(order);
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
