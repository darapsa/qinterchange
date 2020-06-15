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
			ImageRole,
			PriceRole,
			ProdGroupRole,
			WeightRole,
			AuthorRole
		};

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
			if (product->image)
				image = QString{product->image};
			if (product->prod_group)
				prodGroup = QString{product->prod_group};
			if (product->author)
				author = QString{product->author};
		}

		QString sku;
		QString description;
		QString comment;
		QString image;
		double price;
		QString prodGroup;
		double weight;
		QString author;
	};

}

#endif // QICCLIENT_PRODUCT_HXX
