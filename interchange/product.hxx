#ifndef INTERCHANGE_PRODUCT_HXX
#define INTERCHANGE_PRODUCT_HXX

#include <interchange.h>

namespace QInterchange {

	struct Product
	{
		enum ProductRoles {
			SkuRole = Qt::UserRole + 1,
			DescriptionRole,
			TitleRole,
			CommentRole,
			ThumbRole,
			ImageRole,
			PriceRole,
			ProdGroupRole,
			CategoryRole,
			WeightRole,
			AuthorRole,
			CrossSellRole
		};

		Product() {}
		Product(struct interchange_product product) :
			price{product.price},
			weight{product.weight}
		{
			if (product.sku)
				sku = QString{product.sku};
			if (product.description)
				description = QString{product.description};
			if (product.title)
				title = QString{product.title};
			if (product.comment)
				comment = QString{product.comment};
			if (product.thumb)
				thumb = QString{product.thumb};
			if (product.image)
				image = QString{product.image};
			if (product.prod_group)
				prodGroup = QString{product.prod_group};
			if (product.category)
				category = QString{product.category};
			if (product.author)
				author = QString{product.author};
			if (product.crosssell) {
				auto crosssell = product.crosssell;
				for (size_t i = 0; i < crosssell->length; i++)
					crossSell << QString{crosssell->skus[i]};
			}
		}

		QString sku;
		QString description;
		QString title;
		QString comment;
		QString thumb;
		QString image;
		double price;
		QString prodGroup;
		QString category;
		double weight;
		QString author;
		QStringList crossSell;
	};

}

#endif
