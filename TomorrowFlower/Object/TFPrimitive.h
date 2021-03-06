#pragma once

#include "TFBase.h"
#include "TFComponent.h"
#include "TFMesh.h"

namespace TomorrowFlower {
	class TF_DLL TFPrimitive : public TFComponent
	{
		OBJECT_BODY(TFPrimitive);
	public:
		static Ptr create();

		PORPERTY(TFMesh::Ptr, Mesh);
	};
}
