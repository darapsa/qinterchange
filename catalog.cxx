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
			case SkuRole:
				return product.sku();
			case DescriptionRole:
				return product.description();
			case CommentRole:
				return product.comment();
			case ImageRole:
				return product.image();
			case PriceRole:
				return product.price();
			default:
				return QVariant();
		}
	}

	QHash<int, QByteArray> Catalog::roleNames() const
	{
		return QHash<int, QByteArray>{
			{SkuRole, "sku"}
			, {DescriptionRole, "description"}
			, {CommentRole, "comment"}
			, {ImageRole, "image"}
			, {PriceRole, "price"}
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
			icclient_catalog_free(catalog);
			emit updated();
		}
	}

}
