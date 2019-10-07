#ifndef QICCLIENT_CATALOG_HXX
#define QICCLIENT_CATALOG_HXX

#include <QAbstractListModel>
#include "product.hxx"

struct icclient_catalog;

namespace ICClient {

	class Catalog : public QAbstractListModel
	{
		Q_OBJECT

		public:
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
			void addProduct(Product const& product);
			QList<Product> products;
	};

}

#endif // QICCLIENT_CATALOG_HXX
