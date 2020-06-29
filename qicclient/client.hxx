#ifndef QICCLIENT_CLIENT_HXX
#define QICCLIENT_CLIENT_HXX

#include <QObject>

struct icclient_user;

namespace ICClient {

	using std::shared_ptr;
	class Catalog;
	class Product;
	class Basket;

	class Client : public QObject
	{
		Q_OBJECT

		public:
			Client(char const* url, char const* certificate = nullptr);
			~Client();

			void results(size_t (*handler)(void* contents,
						size_t size, size_t nmemb,
						void* userdata),
					QString const& prodGroup);
			void allProducts(size_t (*handler)(void* contents,
						size_t size, size_t nmemb,
						void* userdata));
			void flyPage(size_t (*handler)(void* contents,
						size_t size, size_t nmemb,
						void* userdata),
					QString const& sku);
			void order(QString const& sku, Catalog const& catalog,
					Basket& order);
			void logIn(size_t (*handler)(void*, size_t, size_t, void*),
					icclient_user* user,
					QString const& username,
					QString const& password,
					QString const& successPage = nullptr,
					QString const& nextPage = nullptr,
					QString const& failPage = nullptr);

		public slots:
			/*
			void remove(unsigned int const& indices);
			void checkout();
			*/
		/*
			void account(QString const& firstName
					, QString const& lastName
					, QString const& address1
					, QString const& address2
					, QString const& city
					, QString const& state
					, QString const& zip
					, QString const& email
					, QString const& phoneDay);
			void changePassword(QString const& passwordOld
					, QString const& password
					, QString const& verify);
					*/
			void logOut();
			/*
			void newItem(QString const& description
					, QString const& comment,
					QString const& price
					, QString const& imagePath);
					*/

		signals:
			void gotResults(Catalog* catalog);
			void gotFlyPage(shared_ptr<Product> product);
			void loggedIn(icclient_user* user);
			void loggedOut();
	};

}

#endif // QICCLIENT_CLIENT_HXX
