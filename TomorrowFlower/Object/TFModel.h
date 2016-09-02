#pragma once

#include "TFBase.h"
#include "TFComponent.h"
#include "TFMesh.h"

namespace TomorrowFlower {
	class TF_DLL TFModelNode : public TFObject
	{
		OBJECT_BODY(TFModelNode)
	public:
		static Ptr createByEngine(
			const vector<TFMesh::Ptr> &meshes,
			const vector<Ptr> &subNodes
		);

		virtual void draw() = 0;
	};



	class TF_DLL TFModel : public TFComponent
	{
		OBJECT_BODY(TFModel)
	public:
		static Ptr create(const string &path);

		static Ptr createByEngine(
			const string &path,
			const TFModelNode::Ptr &rootNode
		);

		virtual void beginPlay() override = 0;
		virtual void draw() override = 0;

		virtual const string & getPath() = 0;
	};
}
