#pragma once

#include "TFBase.h"
#include "TFEntity.h"

namespace TomorrowFlower {
	class TF_DLL TFEntityManager
	{
	public:
		static TFEntityManager *getInstance();
		static void destroy();

		virtual TFEntity *getRootEntity() = 0;
	};
}