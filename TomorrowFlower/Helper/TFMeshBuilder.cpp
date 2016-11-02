#include "TFMeshBuilder.h"
#include "TFMaterial.h"

namespace TomorrowFlower {
	TFMesh::Ptr buildCube(const TFVec3 &size)
	{
		auto mesh = TFMesh::create();

		// vertex
		vector<TFVertex> vertices = {
			{ TFVec3(-size.x,	size.y,		-size.z) },
			{ TFVec3(size.x,	size.y,		-size.z) },
			{ TFVec3(-size.x,	-size.y,	-size.z) },
			{ TFVec3(size.x,	-size.y,	-size.z) },
			{ TFVec3(-size.x,	size.y,		size.z) },
			{ TFVec3(size.x,	size.y,		size.z) },
			{ TFVec3(-size.x,	-size.y,	size.z) },
			{ TFVec3(size.x,	-size.y,	size.z) }
		};
		vector<GLuint> indices = {
			0, 1, 2,
			2, 1, 3,
			1, 5, 3,
			3, 5, 7,
			5, 4, 7,
			7, 4, 6,
			4, 0, 6,
			6, 0, 2,
			4, 5, 0,
			0, 5, 1,
			7, 6, 3,
			3, 6, 2
		};
		mesh->setVertices(move(vertices), move(indices));

		return mesh;
	}
}