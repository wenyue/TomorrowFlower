#pragma once

// Base header
#include "TFDefine.h"
#include "TFCommon.h"

// GLEW
#include <GL/glew.h>

// GLM
#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
typedef glm::vec3 TFVec3;
typedef glm::vec2 TFVec2;
typedef glm::mat4 TFMat4;
typedef glm::quat TFQuat;
template struct TF_DLL glm::tvec2<float, glm::highp>;
template struct TF_DLL glm::tvec3<float, glm::highp>;
template struct TF_DLL glm::tvec4<float, glm::highp>;
template struct TF_DLL glm::tmat4x4<float, glm::highp>;
template struct TF_DLL glm::tquat<float, glm::highp>;

// STD header
using namespace std;
#include <memory>
#include <vector>
#include <string>

