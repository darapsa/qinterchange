#ifndef INTERCHANGE_CATALOG_HXX
#define INTERCHANGE_CATALOG_HXX

#include <QAbstractListModel>
#include "product.hxx"

struct interchange_catalog;

namespace QInterchange {

	class Catalog : public QAbstractListModel
	{
		Q_OBJECT

		public:
			Catalog(QObject* parent = nullptr) : QAbstractListModel{parent} {}
			Catalog(struct interchange_catalog* catalog, QObject* parent = nullptr);
			~Catalog();
			int rowCount(QModelIndex const& parent = QModelIndex()) const Q_DECL_OVERRIDE;
			QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
			struct interchange_catalog const* constData() const { return m_data; }

		protected:
			QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;

		private:
			void addProduct(Product const& product);
			QList<Product> products;
			struct interchange_catalog* m_data;
	};

}

#endif
