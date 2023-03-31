#include <algorithm>
#include <memory>
#include "interchange.hxx"
#include "interchange/ord.hxx"

namespace QInterchange {

	static Ord* ord;
	static char* order_profile;
	static char *fname, *lname, *address1, *address2, *city, *state, *zip,
		    *phone_day, *email;

	static interchange_member* mPtr;

	Ord::Ord(struct interchange_ord_order order, QObject* parent) :
		QAbstractListModel{parent}
	{
		ord = this;
		for (size_t i = 0; i < order.nitems; i++)
			addItem(Item{order.items[i]});
		m_subtotal = order.subtotal;
		m_shipping = order.shipping;
		m_totalCost = order.total_cost;
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
			case Item::NameRole:
				return item.name;
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
			{ Item::QuantityRole, "quantity" },
			{ Item::NameRole, "name" }
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

	void Ord::checkout(const Member& member)
	{
		order_profile = (char*)malloc(profile.size() + 1);
		strcpy(order_profile, profile.toLatin1().constData());

		fname = (char*)malloc(member.fName().size() + 1);
		strcpy(fname, member.fName().toLatin1().constData());
		lname = (char*)malloc(member.lName().size() + 1);
		strcpy(lname, member.lName().toLatin1().constData());
		address1 = (char*)malloc(member.address1().size() + 1);
		strcpy(address1, member.address1().toLatin1().constData());
		address2 = (char*)malloc(member.address2().size() + 1);
		strcpy(address2, member.address1().toLatin1().constData());
		city = (char*)malloc(member.city().size() + 1);
		strcpy(city, member.city().toLatin1().constData());
		state = (char*)malloc(member.state().size() + 1);
		strcpy(state, member.state().toLatin1().constData());
		zip = (char*)malloc(member.zip().size() + 1);
		strcpy(zip, member.zip().toLatin1().constData());
		phone_day = (char*)malloc(member.phoneDay().size() + 1);
		strcpy(phone_day, member.phoneDay().toLatin1().constData());
		email = (char*)malloc(member.email().size() + 1);
		strcpy(email, member.email().toLatin1().constData());
		interchange_member m {
			.fname = fname,
			.lname = lname,
			.address1 = address1,
			.address2 = address2,
			.city = city,
			.state = state,
			.zip = zip,
			.phone_day = phone_day,
			.email = email
		};

		interchange_ord_checkout(order_profile, m,
				[](interchange_response* response) {
			free(fname);
			free(lname);
			free(address1);
			free(address2);
			free(city);
			free(state);
			free(zip);
			free(phone_day);
			free(email);
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
