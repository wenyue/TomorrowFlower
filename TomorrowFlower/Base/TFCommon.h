#pragma once

#include "TFDefine.h"

namespace TomorrowFlower {

void TF_DLL TFLog(const char *pszFormat, ...);
void TF_DLL TFMessageBox(const char *pszTitle, const char *pszFormat, ...);

#ifndef TFError
#define TFError(pszFormat, ...) TFLog("Error: " pszFormat, ##__VA_ARGS__)
#endif

#ifndef TFAssert
#ifdef DEBUG
#define TFAssert(cond, pszFormat, ...) do {				\
		if (!(cond)) {							\
			TFLog("Assert failed: " pszFormat, ##__VA_ARGS__);	\
			assert(false);						\
		}										\
	} while (0)
#else
#define TFAssert(cond, pszFormat, ...) ((void)(cond))
#endif
#endif
}