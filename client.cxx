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

	void Client::logIn(QString const& username, QString const& password)
	{
		icclient_login(username.toLatin1().constData()
				, password.toLatin1().constData(), NULL, NULL
				, NULL);
		emit loggedIn(username);
	}

	void Client::logOut()
	{
		icclient_logout();
		emit loggedOut();
	}

}
