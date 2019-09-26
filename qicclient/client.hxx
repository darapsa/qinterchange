#ifndef QRTCLIENT_CLIENT_HXX
#define QRTCLIENT_CLIENT_HXX

#include <QObject>
#include <icclient/product.h>

struct icclient_catalog;

namespace ICClient {

	class Client : public QObject
	{
		Q_OBJECT

		public:
			Client(char const* url, char const* certificate = nullptr);
			~Client();

			void productAll(icclient_catalog** catalogptr
					, size_t (*callback)(void* contents
						, size_t size, size_t nmemb
						, void* userdata));

		public slots:
			void logIn(QString const& username, QString const& password);
			void logOut();

		signals:
			void gotProductAll(icclient_catalog*);
			void loggedIn(QString const& username);
			void loggedOut();
	};

}

#endif // QRTCLIENT_CLIENT_HXX
