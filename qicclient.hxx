#ifndef QICCLIENT_HXX
#define QICCLIENT_HXX

#include <QObject>
#include "qicclient/catalog.hxx"

namespace QICClient {

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
			/*!
			 * \brief Destructor.
			 */
			~Client();
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
			void catalog(QString const& prodGroup);
			/*!
			 * \brief For fetching data about all active products.
			 */
			void allProducts();
			/*!
			 * \brief For fetching data about a specific product.
			 * \param sku The SKU of the item to order.
			 */
			void product(QString const& sku);
			/*!
			 * \brief For fetching data from a specific path.
			 * \param path The path.
			 */
			void page(QString const& path);
			/*!
			 * \brief For fetching products that belong a specific group.
			 * \param prodGroup The name of the product group.
			 */
			void defaultCatalog(QString const& prodGroup);
			/*!
			 * \brief For fetching data about all active products.
			 */
			void defaultAllProducts();

		signals:
			void gotCatalog(QString const& response);
			void gotProduct(QString const& response);
			void gotPage(QString const& response);

		protected:
			void emitCatalog(QString const& response);
			void emitProduct(QString const& response);
			void emitPage(QString const& response);
	};

}

#endif
