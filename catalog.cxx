#include <cstddef>
#include <icclient/catalog.h>
#include <icclient/client.h>
#include "qicclient/catalog.hxx"

namespace ICClient {

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
			case Product::CommentRole:
				return product.comment;
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
			{Product::SkuRole, "sku"}
			, {Product::DescriptionRole, "description"}
			, {Product::CommentRole, "comment"}
			, {Product::ImageRole, "image"}
			, {Product::PriceRole, "price"}
			, {Product::ProdGroupRole, "prodGroup"}
			, {Product::WeightRole, "weight"}
			, {Product::AuthorRole, "author"}
			, {Product::CrossSellRole, "crossSell"}
		};
	}

	void Catalog::addProduct(Product const& product)
	{
		beginInsertRows(QModelIndex(), rowCount(), rowCount());
		products << product;
		endInsertRows();
	}

	void Catalog::update(icclient_catalog* catalog)
	{
		if (catalog) {
			for (size_t i = 0; i < catalog->length; i++)
				addProduct(Product{catalog->products[i]});
			emit updated();
		}
	}

}
