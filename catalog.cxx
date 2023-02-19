#include <cstddef>
#include "interchange/catalog.hxx"

namespace QInterchange {

	Catalog::Catalog(struct interchange_catalog* catalog, QObject* parent) :
		QAbstractListModel{parent},
		m_data{catalog}
	{
		for (size_t i = 0; i < catalog->length; i++) addProduct(Product{catalog->products[i]});
	}

	Catalog::~Catalog()
	{
		interchange_free_catalog(m_data);
	}

	int Catalog::rowCount(QModelIndex const& parent) const
	{
		Q_UNUSED(parent)
		return products.count();
	}

	QVariant Catalog::data(QModelIndex const& index, int role) const
	{
		auto row = index.row();
		if (row < 0 || row >= products.count()) return QVariant();
		auto product = products[row];
		switch (role) {
			case Product::SkuRole:
				return product.sku;
			case Product::TitleRole:
				return product.title;
			case Product::DescriptionRole:
				return product.description;
			case Product::CommentRole:
				return product.comment;
			case Product::ThumbRole:
				return product.thumb;
			case Product::ImageRole:
				return product.image;
			case Product::PriceRole:
				return product.price;
			case Product::ProdGroupRole:
				return product.prodGroup;
			case Product::WeightRole:
				return product.weight;
			case Product::AuthorRole:
				return product.author;
			case Product::CrossSellRole:
				return product.crossSell;
			default:
				return QVariant();
		}
	}

	QHash<int, QByteArray> Catalog::roleNames() const
	{
		return QHash<int, QByteArray>{
			{ Product::SkuRole, "sku" },
			{ Product::TitleRole, "title" },
			{ Product::DescriptionRole, "description" },
			{ Product::CommentRole, "comment" },
			{ Product::ThumbRole, "thumb" },
			{ Product::ImageRole, "image" },
			{ Product::PriceRole, "price" },
			{ Product::ProdGroupRole, "prodGroup" },
			{ Product::WeightRole, "weight" },
			{ Product::AuthorRole, "author" },
			{ Product::CrossSellRole, "crossSell" }
		};
	}

	void Catalog::addProduct(Product const& product)
	{
		beginInsertRows(QModelIndex(), rowCount(), rowCount());
		products << product;
		endInsertRows();
	}

}
