#include "qicclient/basket.hxx"

namespace ICClient {

	int Basket::rowCount(QModelIndex const& parent) const
	{
		Q_UNUSED(parent)
		return items.count();
	}

	QVariant Basket::data(QModelIndex const& index, int role) const
	{
		auto row = index.row();

		if (row < 0 || row >= items.count()) return QVariant();

		auto item = items[row];
		switch (role) {
			case Product::SkuRole:
				return item.product.sku;
			case Product::DescriptionRole:
				return item.product.description;
			case Product::PriceRole:
				return item.product.price;
			case Item::QuantityRole:
				return item.quantity;
			default:
				return QVariant();
		}
	}

	QHash<int, QByteArray> Basket::roleNames() const
	{
		return QHash<int, QByteArray>{
			{Product::SkuRole, "sku"}
			, {Product::DescriptionRole, "description"}
			, {Product::PriceRole, "price"}
			, {Item::QuantityRole, "quantity"}
		};
	}

	void Basket::addItem(Item const& item)
	{
		beginInsertRows(QModelIndex(), rowCount(), rowCount());
		items << item;
		endInsertRows();
		emit rowCountChanged();
	}

	void Basket::update(icclient_ord_order* order)
	{
		if (order) {
			for (size_t i = 0; i < order->nitems; i++)
				addItem(Item{order->items[i]});
			icclient_ord_free(order);
			emit updated();
		}
	}

}
