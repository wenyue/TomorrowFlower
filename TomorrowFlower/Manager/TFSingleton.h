#pragma once

#include "TFDefine.h"

namespace TomorrowFlower {
	// Base class of other singleton classes.
	template <class T>
	class TF_DLL TFSingleton
	{
	public:
		static T* getInstance()
		{
			if (mInstance == nullptr) {
				mInstance = new T();
			}
			return mInstance;
		}

		static void destroy()
		{
			delete mInstance;
			mInstance = nullptr;
		}

	protected:
		TFSingleton() {};
		~TFSingleton() {};

	private:
		static T* mInstance;
		TFSingleton(const TFSingleton &) {};
	};

	template<class T>
	T* TFSingleton<T>::mInstance = nullptr;
}