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

#define OBJECT_BODY(CLASS_NAME)								\
public: typedef shared_ptr<CLASS_NAME> Ptr;					\
public: Ptr inline self() {									\
	return dynamic_pointer_cast<CLASS_NAME>(mSelf.lock());	\
}															\
public: typedef weak_ptr<CLASS_NAME> WPtr


	class TFObject;
	template class TF_DLL weak_ptr<TFObject>;
	class TF_DLL TFObject
	{
		OBJECT_BODY(TFObject);
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