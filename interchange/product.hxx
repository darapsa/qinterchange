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
			OptionTypeRole,
			AuthorRole,
			CrossSellRole,
			ImageLargeRole
		};

		Product() {}
		Product(struct interchange_product *product) :
			price{product->price},
			weight{product->weight}
		{
			if (product->sku)
				sku = QString{product->sku};
			if (product->description)
				description = QString{product->description};
			if (product->title)
				title = QString{product->title};
			if (product->comment)
				comment = QString{product->comment};
			if (product->thumb)
				thumb = QString{product->thumb};
			if (product->image)
				image = QString{product->image};
			if (product->prod_group)
				prodGroup = QString{product->prod_group};
			if (product->category)
				category = QString{product->category};
			if (product->option_type)
				optionType = QString{product->option_type};
			if (product->author)
				author = QString{product->author};
			if (product->crosssell) {
				auto crosssell = product->crosssell;
				for (size_t i = 0; i < crosssell->length; i++)
					crossSell << QString{crosssell->skus[i]};
			}
			if (product->image_large)
				imageLarge = QString{product->image_large};
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
		QString optionType;
		QString author;
		QStringList crossSell;
		QString imageLarge;
	};

}

#endif
