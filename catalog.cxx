#include <cstddef>
#include <icclient/catalog.h>
#include <icclient/client.h>
#include "qicclient/catalog.hxx"

namespace ICClient {

	Catalog::Catalog(icclient_catalog* catalog, QObject* parent) :
		QAbstractListModel{parent}
	{
		for (size_t i = 0; i < catalog->length; i++)
			addProduct(Product{catalog->products[i]});
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
			{Product::SkuRole, "sku"}
			, {Product::DescriptionRole, "description"}
			, {Product::CommentRole, "comment"}
			, {Product::ThumbRole, "thumb"}
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

	void Catalog::update(Catalog* catalog)
	{
		for (int i = 0; i < catalog->rowCount(); i++) {
			auto index = catalog->index(i, 0);
			Product product;
			product.sku = catalog->data(index, Product::SkuRole).toString();
			product.description = catalog->data(index, Product::DescriptionRole).toString();
			product.comment = catalog->data(index, Product::CommentRole).toString();
			product.thumb = catalog->data(index, Product::ThumbRole).toString();
			product.image = catalog->data(index, Product::ImageRole).toString();
			product.price = catalog->data(index, Product::PriceRole).toDouble();
			product.prodGroup = catalog->data(index, Product::ProdGroupRole).toString();
			product.weight = catalog->data(index, Product::WeightRole).toDouble();
			product.author = catalog->data(index, Product::AuthorRole).toString();
			product.crossSell = catalog->data(index, Product::CrossSellRole).toStringList();
			addProduct(product);
			emit updated();
		}
	}

}
