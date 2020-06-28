#ifndef QICCLIENT_PRODUCT_HXX
#define QICCLIENT_PRODUCT_HXX

#include <icclient/product.h>

namespace ICClient {

	struct Product
	{
		enum ProductRoles {
			SkuRole = Qt::UserRole + 1,
			DescriptionRole,
			CommentRole,
			ThumbRole,
			ImageRole,
			PriceRole,
			ProdGroupRole,
			WeightRole,
			AuthorRole,
			CrossSellRole
		};

		Product() {}
		Product(icclient_product* product) :
			price{product->price},
			weight{product->weight}
		{
			if (product->sku)
				sku = QString{product->sku};
			if (product->description)
				description = QString{product->description};
			if (product->comment)
				comment = QString{product->comment};
			if (product->thumb)
				thumb = QString{product->thumb};
			if (product->image)
				image = QString{product->image};
			if (product->prodgroup)
				prodGroup = QString{product->prodgroup};
			if (product->author)
				author = QString{product->author};
			if (product->crosssell) {
				auto crosssell = product->crosssell;
				for (size_t i = 0; i < crosssell->length; i++)
					crossSell << QString{crosssell->skus[i]};
			}
		}

		QString sku;
		QString description;
		QString comment;
		QString thumb;
		QString image;
		double price;
		QString prodGroup;
		double weight;
		QString author;
		QStringList crossSell;
	};

}

#endif // QICCLIENT_PRODUCT_HXX
