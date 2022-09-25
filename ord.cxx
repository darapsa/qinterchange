#include <algorithm>
#include <memory>
#include "interchange/ord.hxx"

namespace Interchange {

	int Ord::rowCount(QModelIndex const& parent) const
	{
		Q_UNUSED(parent)
		return items.count();
	}

	QVariant Ord::data(QModelIndex const& index, int role) const
	{
		auto row = index.row();
		if (row < 0 || row >= items.count()) return QVariant();
		auto item = items[row];
		switch (role) {
			case Product::SkuRole:
				return item.product.sku;
			case Product::DescriptionRole:
				return item.product.description;
			case Product::ImageRole:
				return item.product.image;
			case Product::PriceRole:
				return item.product.price;
			case Item::QuantityRole:
				return item.quantity;
			default:
				return QVariant();
		}
	}

	QHash<int, QByteArray> Ord::roleNames() const
	{
		return QHash<int, QByteArray>{
			{ Product::SkuRole, "sku" },
			{ Product::DescriptionRole, "description" },
			{ Product::ImageRole, "image" },
			{ Product::PriceRole, "price" },
			{ Item::QuantityRole, "quantity" }
		};
	}

	void Ord::addItem(Item const& item)
	{
		auto product = item.product;
		auto iterator = std::find_if(items.begin(), items.end(), [&product](Item const& item) {
			return product.sku == item.product.sku;
		});
		if (iterator != items.end()) {
			auto index = items.indexOf(*iterator);
			beginRemoveRows(QModelIndex(), index, index);
			items.removeAt(index);
			endRemoveRows();
		}
		beginInsertRows(QModelIndex(), rowCount(), rowCount());
		items << item;
		endInsertRows();
		emit rowCountChanged();
	}

	void Ord::setData(struct interchange_ord_order* order)
	{
		if (!order) return;
		this->m_data = order;
		for (size_t i = 0; i < order->nitems; i++) addItem(Item{order->items[i]});
		m_subtotal = order->subtotal;
		emit subtotalChanged();
		m_totalCost = order->total_cost;
		emit totalCostChanged();
	}

	void Ord::checkout(Member& member)
	{
		interchange_ord_checkout(m_data, member.data());
	}
}
