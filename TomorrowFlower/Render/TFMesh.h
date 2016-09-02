#pragma once

#include "TFBase.h"
#include "TFObject.h"
#include "TFVertex.h"
#include "TFTexture.h"
#include "TFMaterialInstance.h"

namespace TomorrowFlower {
	class TF_DLL TFMesh : public TFObject
	{
		OBJECT_BODY(TFMesh)
	public:
		static Ptr create();

		virtual void draw() = 0;

		virtual void setVertices(vector<TFVertex> &&vertices, vector<GLuint> &&indices) = 0;
		virtual void setMaterialInstance(const TFMaterialInstance::Ptr &materialInstance) = 0;
	};
}
