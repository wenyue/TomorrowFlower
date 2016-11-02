#pragma once

#include "MaterialActions/TFMaterialAction.h"
#include "TFModel.h"

namespace TomorrowFlower {
	class TFMaterialActionModelMatrix : public TFMaterialAction
	{
		OBJECT_BODY(TFMaterialActionModelMatrix);
	public:
		static Ptr create(
			const TFModel::Ptr &model
		)
		{
			return createObject<TFMaterialActionModelMatrix>(model);
		}

		// Constructor
		TFMaterialActionModelMatrix(
			const TFModel::Ptr &model
		)
			: mModel(model)
		{
		}

		void onRenderBegin(const TFShader::Ptr &shader) override
		{
			auto model = mModel.lock();
			if (!model) {
				return;
			}
			model->getEntity()->beginPlay();
		}

	private:
		TFModel::WPtr mModel;
	};
}
