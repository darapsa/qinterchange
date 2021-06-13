#ifndef QICCLIENT_CLIENT_HXX
#define QICCLIENT_CLIENT_HXX

#include <QObject>
#include <icclient.h>

namespace QICClient {

	using std::shared_ptr;
	class Catalog;
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

			/*!
			 * \brief For fetching products that belong a specific group.
			 * \param prodGroup The name of the product group.
			 * \param handler A pointer to a cURL write function callback.
			 */
			void results(QString const& prodGroup, icclient_handler handler = nullptr);

			/*!
			 * \brief For fetching data about all active products.
			 * \param handler A pointer to a cURL write function callback.
			 */
			void allProducts(icclient_handler handler = nullptr);

			void emitCatalog(icclient_catalog *catalog);

			/*!
			 * \brief For fetching data about a specific product.
			 * \param sku The SKU of the item to order.
			 * \param handler A pointer to a cURL write function callback.
			 */
			void flyPage(QString const& sku, icclient_handler handler);

			/*!
			 * \brief For putting an item to a cart.
			 * \param sku The SKU of the item to order.
			 * \param catalog The catalog from which the item is.
			 * \param order The order.
			 */
			void order(QString const& sku, Catalog const& catalog, Ord& order);

		signals:
			void gotResults(Catalog* catalog);
			void gotFlyPage(shared_ptr<Product> product);
	};

}

#endif
