#ifndef INTERCHANGE_ORD_HXX
#define INTERCHANGE_ORD_HXX

#include <QAbstractListModel>
#include <interchange/ord.h>
#include "member.hxx"
#include "product.hxx"

namespace QInterchange {

	struct Item
	{
		enum ItemRoles {
			QuantityRole = Product::PriceRole + 1,
			NameRole
		};
		Item(interchange_ord_item item) :
			product{item.product},
			quantity{item.quantity},
			name{item.name} {}
		Product product;
		unsigned int quantity;
		QString name;
		bool operator==(Item const& item)
		{
			return product.sku == item.product.sku;
		}
	};

	class Ord : public QAbstractListModel
	{
		Q_OBJECT
		Q_PROPERTY(int rowCount READ rowCount NOTIFY rowCountChanged)
		Q_PROPERTY(double subtotal READ subtotal NOTIFY subtotalChanged)
		Q_PROPERTY(double shipping READ shipping NOTIFY shippingChanged)
		Q_PROPERTY(double totalCost READ totalCost NOTIFY totalCostChanged)

		public:
			explicit Ord(struct interchange_ord_order *order,
					QObject* parent = nullptr);
			~Ord() {}
			int rowCount(QModelIndex const& parent = QModelIndex()) const Q_DECL_OVERRIDE;
			QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const
				Q_DECL_OVERRIDE;
			double subtotal() const { return m_subtotal; }
			double shipping() const { return m_shipping; }
			double totalCost() const { return m_totalCost; }
			void setProfile(QString const& profile);
		public slots:
			void update(const QString &name,
					const int quantity = 0,
					const QString &orderPage = "",
					const QString &nextPage = "");
			void remove(const QString &name,
					const QString &orderPage = "",
					const QString &nextPage = "");
			void checkout(const Member& member);
		signals:
			void rowCountChanged();
			void subtotalChanged();
			void shippingChanged();
			void totalCostChanged();
			void updated(const QString &response);
			void gotTransaction(QString const& response);

		protected:
			QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;
			void emitUpdate(const QString &response);
			void emitTransaction(QString const& response);

		private:
			void addItem(Item const& item);
			QList<Item> items;
			QString profile;
			double m_subtotal;
			double m_shipping;
			double m_totalCost;
	};

}

#endif
