#ifndef QICCLIENT_CATALOG_HXX
#define QICCLIENT_CATALOG_HXX

#include <QAbstractListModel>
#include <icclient/product.h>

struct icclient_catalog;

namespace ICClient {

	class Product
	{
		public:
			Product(icclient_product* product) : m_sku{product->sku}
			{
				if (product->description)
					m_description
						= QString{product->description};
				if (product->comment)
					m_comment = QString{product->comment};
				if (product->image)
					m_image = QString{product->image};
				m_price = product->price;
			}
			QString const& sku() const { return m_sku; }
			QString const& description() const
			{
				return m_description;
			}
			QString const& comment() const { return m_comment; }
			QString const& image() const { return m_image; }
			double price() const { return m_price; }

		private:
			QString m_sku;
			QString m_description;
			QString m_comment;
			QString m_image;
			double m_price;
	};

	class Catalog : public QAbstractListModel
	{
		Q_OBJECT

		public:
			enum ProductRoles {
				SkuRole = Qt::UserRole + 1,
				DescriptionRole,
				CommentRole,
				ImageRole,
				PriceRole
			};

			explicit Catalog(QObject* parent = nullptr)
				: QAbstractListModel{parent} {}

			int rowCount(QModelIndex const& parent
					= QModelIndex()) const Q_DECL_OVERRIDE;
			QVariant data(const QModelIndex& index
					, int role = Qt::DisplayRole
					) const Q_DECL_OVERRIDE;

		public slots:
			void update(icclient_catalog* catalog);

		signals:
			void updated();

		protected:
			QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;

		private:
			QList<Product> products;
			void addProduct(Product const& product);
	};

}

#endif // QICCLIENT_CATALOG_HXX
