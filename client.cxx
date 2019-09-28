#include <cstddef>
#include <icclient/client.h>
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
		icclient_allproducts(&catalog, handler);
		emit gotAllProducts(catalog);
	}

	void Client::logIn(QString const& username, QString const& password)
	{
		icclient_login(username.toLatin1().constData()
				, password.toLatin1().constData(), nullptr, nullptr
				, nullptr);
		emit loggedIn(username);
	}

	void Client::logOut()
	{
		icclient_logout();
		emit loggedOut();
	}

}
