#include <cstddef>
#include "interchange/catalog.hxx"

namespace QInterchange {

	Catalog::Catalog(struct interchange_catalog catalog, QObject* parent) :
		QAbstractListModel{parent}
	{
		for (size_t i = 0; i < catalog.length; i++)
			addProduct(Product{catalog.products[i]});
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
			case Product::DescriptionRole:
				return product.description;
			case Product::TitleRole:
				return product.title;
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
			case Product::CategoryRole:
				return product.category;
			case Product::WeightRole:
				return product.weight;
			case Product::OptionTypeRole:
				return product.optionType;
			case Product::AuthorRole:
				return product.author;
			case Product::CrossSellRole:
				return product.crossSell;
			case Product::ImageLargeRole:
				return product.imageLarge;
			default:
				return QVariant();
		}
	}

	QHash<int, QByteArray> Catalog::roleNames() const
	{
		return QHash<int, QByteArray>{
			{ Product::SkuRole, "sku" },
			{ Product::DescriptionRole, "description" },
			{ Product::TitleRole, "title" },
			{ Product::CommentRole, "comment" },
			{ Product::ThumbRole, "thumb" },
			{ Product::ImageRole, "image" },
			{ Product::PriceRole, "price" },
			{ Product::ProdGroupRole, "prodGroup" },
			{ Product::CategoryRole, "category" },
			{ Product::WeightRole, "weight" },
			{ Product::OptionTypeRole, "optionType" },
			{ Product::AuthorRole, "author" },
			{ Product::CrossSellRole, "crossSell" },
			{ Product::ImageLargeRole, "imageLarge" }
		};
	}

	void Catalog::addProduct(Product const& product)
	{
		beginInsertRows(QModelIndex(), rowCount(), rowCount());
		products << product;
		endInsertRows();
	}

}
