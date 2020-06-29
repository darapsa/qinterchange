#ifndef QICCLIENT_BASKET_HXX
#define QICCLIENT_BASKET_HXX

#include <QAbstractListModel>
#include <icclient/ord.h>
#include "product.hxx"

struct icclient_ord_order;

namespace ICClient {

	struct Item
	{
		enum ItemRoles {
			QuantityRole = Product::PriceRole + 1
		};

		Item(icclient_ord_item* item)
			: product{item->product}
			, quantity{item->quantity}
		{}

		Product product;
		unsigned int quantity;

		bool operator==(Item const& item)
		{
			return product.sku == item.product.sku;
		}
	};

	class Basket : public QAbstractListModel
	{
		Q_OBJECT
		Q_PROPERTY(int rowCount READ rowCount NOTIFY rowCountChanged)
		Q_PROPERTY(double subtotal READ subtotal NOTIFY subtotalChanged)
		Q_PROPERTY(double shipping READ shipping NOTIFY shippingChanged)
		Q_PROPERTY(double totalCost READ totalCost NOTIFY totalCostChanged)

		public:
			explicit Basket(QObject* parent = nullptr)
				: QAbstractListModel{parent}
				, m_subtotal{.0}
				, m_shipping{.0}
				, m_totalCost{.0}
			{}

			QVariant data(const QModelIndex& index,
					int role = Qt::DisplayRole
				     ) const Q_DECL_OVERRIDE;
			int rowCount(QModelIndex const& parent
					= QModelIndex()) const Q_DECL_OVERRIDE;

			double subtotal() const { return m_subtotal; }
			double shipping() const { return m_shipping; }
			double totalCost() const { return m_totalCost; }
			icclient_ord_order* c_order() { return order; }

		signals:
			void rowCountChanged();
			void subtotalChanged();
			void shippingChanged();
			void totalCostChanged();

		protected:
			QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;

		private:
			void addItem(Item const& item);
			QList<Item> items;
			double m_subtotal;
			double m_shipping;
			double m_totalCost;
			icclient_ord_order* order;
	};

}

#endif // QICCLIENT_BASKET_HXX
