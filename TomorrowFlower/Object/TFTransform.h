#pragma once

#include "TFBase.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"

namespace TomorrowFlower {
	struct TF_DLL TFTransform
	{
		// Rotation of this tranformation, as quaternion
		TFQuat rotation;
		// Translation of this transformation, as vector
		TFVec3 translation;
		// 3D scale (always applied in local space) as a vector
		TFVec3 scale;

		TFMat4 toMatrix()
		{
			auto &matrix = static_cast<TFMat4>(rotation);
			matrix = glm::scale(matrix, scale);
			matrix = glm::translate(matrix, translation);
			return matrix;
		}

		TFVec3 forward()
		{
			return rotation * TFVec3(0, 0, 1);
		}

		TFVec3 up()
		{
			return rotation * TFVec3(0, 1, 0);
		}

		TFVec3 left()
		{
			return rotation * TFVec3(-1, 0, 0);
		}

		void lookAt(const TFVec3 &center)
		{
			lookAt(center, up());
		}

		void lookAt(const TFVec3 &center, const TFVec3 &up)
		{
			rotation = TFQuat(glm::lookAt(translation, center, up));
		}
	};
}
