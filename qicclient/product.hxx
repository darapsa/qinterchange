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
			AuthorRole
		};

		Product(icclient_product* product) :
			sku{product->sku},
			price{product->price}
		{
			if (product->description)
				description = QString{product->description};
			if (product->comment)
				comment = QString{product->comment};
			if (product->image)
				image = QString{product->image};
			if (product->author)
				author = QString{product->author};
		}

		QString sku;
		QString description;
		QString comment;
		QString image;
		double price;
		QString author;
	};

}

#endif // QICCLIENT_PRODUCT_HXX
