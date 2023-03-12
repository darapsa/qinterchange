#ifndef INTERCHANGE_HXX
#define INTERCHANGE_HXX

#include <QObject>
#include "interchange/catalog.hxx"

namespace QInterchange {

	class Ord;

	class Interchange : public QObject
	{
		Q_OBJECT

		public:
			/*!
			 * \brief Constructor.
			 * \param sampleURL The value of the SAMPLEURL setting in products/variable.txt.
			 * \param image_Dir The value of the IMAGE_DIR setting in products/variable.txt.
			 * \param cookie Path to the cookie file.
			 * \param certificate Path to the CA certificate file.
			 */
			Interchange(const char* sampleURL,
					const char* image_Dir,
					const QString& cookie = "",
					const QString& certificate = "");
			/*!
			 * \brief Destructor.
			 */
			~Interchange();

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
			/*!
			 * \brief For putting an item to a cart.
			 * \param sku The SKU of the item to order.
			 */
			void order(QString const& sku);

		signals:
			void gotCatalog(QString const& response);
			void gotProduct(QString const& response);
			void gotPage(QString const& response);
			void gotOrder(QString const& response);

		protected:
			void emitCatalog(QString const& response);
			void emitProduct(QString const& response);
			void emitPage(QString const& response);
			void emitOrder(QString const& response);
	};

}

#endif
