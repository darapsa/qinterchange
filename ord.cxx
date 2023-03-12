#include <algorithm>
#include <memory>
#include "interchange.hxx"
#include "interchange/ord.hxx"

namespace QInterchange {

	static Ord* ord;
	static char* order_profile;

	Ord::Ord(struct interchange_ord_order *order, QObject* parent) :
		QAbstractListModel{parent},
		m_data{nullptr},
		m_subtotal{.0},
		m_shipping{.0},
		m_totalCost{.0}
	{
		ord = this;
		if (!order) return;
		for (size_t i = 0; i < order->nitems; i++)
			addItem(Item{order->items[i]});
		m_subtotal = order->subtotal;
		m_totalCost = order->total_cost;
		m_data = order;
	}

	Ord::~Ord()
	{
		if (m_data) interchange_ord_free_order(m_data);
	}

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
			case Product::TitleRole:
				return item.product.title;
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
			{ Product::TitleRole, "title" },
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

	void Ord::setProfile(QString const& profile)
	{
		if (this->profile != profile) this->profile = profile;
	}

	void Ord::checkout(Member& member)
	{
		order_profile = (char*)malloc(profile.size() + 1);
		strcpy(order_profile, profile.toLatin1().constData());
		interchange_ord_checkout(order_profile, member.data(),
				[](interchange_response* response) {
			free(order_profile);
			ord->emitTransaction(QString{response->data});
			interchange_free_response(response);
		});
	}

	void Ord::emitTransaction(QString const& response)
	{
		emit gotTransaction(response);
	}
}
