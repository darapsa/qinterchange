#ifndef QICCLIENT_HXX
#define QICCLIENT_HXX

#include <QObject>
#include <qicclient/catalog.hxx>
#include <icclient.h>

namespace QICClient {

	using std::shared_ptr;
	class Ord;

	class Client : public QObject
	{
		Q_OBJECT

		public:
			/*!
			 * \brief Constructor.
			 * \param url Server root URL.
			 * \param certificate Path to the CA certificate file.
			 */
			Client(char const* url, char const* certificate = nullptr);
			~Client();
			void emitResults(icclient_fetch_t* fetch);
			/*!
			 * \brief For fetching data about a specific product.
			 * \param sku The SKU of the item to order.
			 * \param handler A pointer to a cURL write function callback.
			 */
			void flyPage(QString const& sku, void (*handler)(icclient_fetch_t*));
			/*!
			 * \brief For putting an item to a cart.
			 * \param sku The SKU of the item to order.
			 * \param catalog The catalog from which the item is.
			 * \param order The order.
			 */
			void order(QString const& sku, Catalog const& catalog, Ord& order);

		public slots:
			/*!
			 * \brief For fetching products that belong a specific group.
			 * \param prodGroup The name of the product group.
			 */
			void results(QString const& prodGroup);
			/*!
			 * \brief For fetching data about all active products.
			 */
			void allProducts();

		signals:
			void gotResults(icclient_fetch_t* fetch);
			void gotFlyPage(shared_ptr<Product> product);
	};

}

#endif
