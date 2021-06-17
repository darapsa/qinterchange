#ifndef QICCLIENT_HXX
#define QICCLIENT_HXX

#include <QObject>
#include "qicclient/catalog.hxx"
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
			 * \param sampleURL The value of the SAMPLEURL setting in products/variable.txt.
			 * \param image_Dir The value of the IMAGE_DIR setting in products/variable.txt.
			 * \param certificate Path to the CA certificate file.
			 */
			Client(char const* sampleURL, char const* image_Dir, char const* certificate = nullptr);
			~Client();
			/*!
			 * \brief For fetching products that belong a specific group.
			 * \param prodGroup The name of the product group.
			 * \param handler A C style pointer to function for custom handling.
			 */
			//void results(QString const& prodGroup, void (*handler)(icclient_response*));
			/*!
			 * \brief For fetching data about all active products.
			 * \param handler A C style pointer to function for custom handling.
			 */
			void allproducts(void (*handler)(icclient_response*) = nullptr);
			void emitResults(icclient_response* response);
			void emitCatalog(icclient_catalog* catalog);
			/*!
			 * \brief For fetching data about a specific product.
			 * \param sku The SKU of the item to order.
			 * \param handler A pointer to a cURL write function callback.
			 */
			void flyPage(QString const& sku, void (*handler)(icclient_response*));
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
			void gotResults(icclient_response* response);
			void gotCatalog(Catalog* catalog);
			void gotFlyPage(shared_ptr<Product> product);
	};

}

#endif
