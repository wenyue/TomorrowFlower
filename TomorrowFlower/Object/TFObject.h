#pragma once

#include "TFDefine.h"

namespace TomorrowFlower {
template<class _Ty,	class... _Types>
inline shared_ptr<_Ty> createObject(_Types&&... _Args)
{
	auto ptr = make_shared<_Ty>(forward<_Types>(_Args)...);
	ptr->mSelf = ptr;
	return ptr;
}

#define OBJECT_BODY(CLASS_NAME)			\
OBJECT_SHARED_PTR(CLASS_NAME)			\
OBJECT_WEAK_PTR(CLASS_NAME)				\
OBJECT_GET_SELF(CLASS_NAME)

#define OBJECT_SHARED_PTR(CLASS_NAME)	\
public: typedef shared_ptr<CLASS_NAME> Ptr;

#define OBJECT_WEAK_PTR(CLASS_NAME)	\
public: typedef weak_ptr<CLASS_NAME> WPtr;

#define OBJECT_GET_SELF(CLASS_NAME)		\
public: Ptr inline self() {				\
	return dynamic_pointer_cast<CLASS_NAME>(mSelf.lock());	\
}

	class TFObject;
	template class TF_DLL weak_ptr<TFObject>;
	class TF_DLL TFObject
	{
		OBJECT_BODY(TFObject)
	public:
		virtual ~TFObject()
		{
		}

	protected:
		template<class _Ty, class... _Types>
		friend shared_ptr<_Ty> createObject(_Types&&... _Args);

		TFObject::WPtr mSelf;
	};
}