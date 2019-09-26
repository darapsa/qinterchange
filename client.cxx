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

	void productAll(icclient_catalog** catalogptr
			, size_t (*callback)(void* contents
				, size_t size, size_t nmemb
				, void* userdata))
	{
		icclient_product_all(catalogptr, callback);
		emit gotProductAll(*catalogptr);
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
