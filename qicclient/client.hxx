#ifndef QRTCLIENT_CLIENT_HXX
#define QRTCLIENT_CLIENT_HXX

#include <QObject>

namespace ICClient {

	class Client : public QObject
	{
		Q_OBJECT

		public:
			Client(char const* url, char const* certificate = NULL);
			~Client();

		public slots:
			void logIn(QString const& username, QString const& password);
			void logOut();

		signals:
			void loggedIn(QString const& username);
			void loggedOut();
	};

}

#endif // QRTCLIENT_CLIENT_HXX
