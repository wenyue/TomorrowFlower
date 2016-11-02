#include "TFPrimitive.h"
#include "TFComponentImpl.h"
#include "TFMesh.h"

namespace TomorrowFlower {
	class TFPrimitiveImplement : public TFComponentImpl<TFPrimitive>
	{
	public:
		// Contructor
		TFPrimitiveImplement()
		{
		}

		void beginPlay() override
		{
			registerHook(COMPONENT_HOOK_DRAW);
		}

		void draw() override
		{
			if (mMesh) {
				mMesh->draw();
			}
		}

		void setMesh(const TFMesh::Ptr &mesh) override
		{
			mMesh = mesh;
		}

	private:
		MEMBER_GET(TFMesh::Ptr, Mesh);
	};

	TFPrimitive::Ptr TFPrimitive::create()
	{
		return createObject<TFPrimitiveImplement>();
	}
}