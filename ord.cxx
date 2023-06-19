#include "interchange.hxx"
#include "interchange/ord.hxx"

namespace QInterchange {

	static Ord* ord;
	static char *item_name, *order_page, *next_page;
	static char* order_profile;
	static char *fname, *lname, *address1, *address2, *city, *state, *zip,
		    *phone_day, *email;

	Ord::Ord(struct interchange_ord_order *order, QObject *parent) :
		QAbstractListModel{parent}
	{
		init(order);
		for (size_t i = 0; i < order->nitems; i++)
			addItem(new Item{order->items[i]});
	}

	void Ord::init(struct interchange_ord_order *order)
	{
		ord = this;
		m_subtotal = order->subtotal;
		m_shipping = order->shipping;
		m_totalCost = order->total_cost;
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
		auto item = items.at(row);
		switch (role) {
			case Product::SkuRole:
				return item->sku;
			case Product::TitleRole:
				return item->title;
			case Product::DescriptionRole:
				return item->description;
			case Product::ImageRole:
				return item->image;
			case Product::PriceRole:
				return item->price;
			case Product::OptionTypeRole:
				return item->optionType;
			case Item::QuantityRole:
				return item->quantity;
			case Item::NameRole:
				return item->name;
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
			{ Product::OptionTypeRole, "optionType" },
			{ Item::QuantityRole, "quantity" },
			{ Item::NameRole, "name" }
		};
	}

	void Ord::addItem(Item *item)
	{
		auto sku = item->sku;
		auto iterator = std::find_if(items.begin(), items.end(),
				[&sku](Item *item) {
			return sku == item->sku;
		});
		if (iterator != items.end()) {
			auto index = items.indexOf(*iterator);
			beginRemoveRows(QModelIndex(), index, index);
			items.removeAt(index);
			endRemoveRows();
			delete *iterator;
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

	void Ord::update(const QString &name, const int quantity,
			const QString &orderPage, const QString &nextPage)
	{
		item_name = (char *)malloc(name.size() + 1);
		strcpy(item_name, name.toLatin1().constData());
		if (orderPage.isEmpty())
			order_page = nullptr;
		else {
			order_page = (char *)malloc(orderPage.size() + 1);
			strcpy(order_page, orderPage.toLatin1().constData());
		}
		if (nextPage.isEmpty())
			next_page = nullptr;
		else {
			next_page = (char *)malloc(nextPage.size() + 1);
			strcpy(next_page, nextPage.toLatin1().constData());
		}
		interchange_ord_update(item_name, quantity, order_page,
				next_page, [](interchange_response *response) {
			free(item_name);
			if (order_page) free(order_page);
			if (next_page) free(next_page);
			ord->emitUpdate(QString{response->data});
			interchange_free_response(response);
		});
	}

	void Ord::remove(const QString &name, const QString &orderPage,
			const QString &nextPage)
	{
		update(name, 0, orderPage, nextPage);
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

	void Ord::emitUpdate(const QString &response)
	{
		emit updated(response);
	}

	void Ord::emitTransaction(QString const& response)
	{
		emit gotTransaction(response);
	}
}
