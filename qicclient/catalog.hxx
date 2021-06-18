#ifndef QICCLIENT_CATALOG_HXX
#define QICCLIENT_CATALOG_HXX

#include <QAbstractListModel>
#include "product.hxx"

struct icclient_catalog;

namespace QICClient {

	class Catalog : public QAbstractListModel
	{
		Q_OBJECT

		public:
			Catalog(icclient_catalog* catalog, QObject* parent = nullptr);
			~Catalog();
			int rowCount(QModelIndex const& parent = QModelIndex()) const Q_DECL_OVERRIDE;
			QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
			icclient_catalog const* constData() const { return m_data; }

		protected:
			QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;

		private:
			void addProduct(Product const& product);
			QList<Product> products;
			icclient_catalog* m_data;
	};

}

#endif
