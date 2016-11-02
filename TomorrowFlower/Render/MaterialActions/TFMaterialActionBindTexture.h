#pragma once

#include "TFMaterialAction.h"
#include "TFTexture.h"

namespace TomorrowFlower {
	TFMaterialAction::Ptr createMaterialActionBindTexture(
		const string &samplerName,
		const TFTexture::Ptr &texture
	);
}
