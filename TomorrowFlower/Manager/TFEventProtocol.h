#pragma once

#include "TFBase.h"
#include <functional>
#include <unordered_map>

namespace TomorrowFlower {
	
	static int uniqueId = 0;

	template <typename T>
	class TFEvent
	{
	public:
		typedef function<T> FunctionType;

		TFEvent()
		{
			mId = ++uniqueId;
		}

		int getId() const
		{
			return mId;
		}

	private:
		int mId;
	};

	template<typename T>
	class TFEventHandler
	{
	public:
		typedef function<T> FunctionType;

		TFEventHandler(const FunctionType &callback)
			: mCallback(callback)
		{
		}

		template <typename ...Arg>
		void operator() (Arg &&...parameters)
		{
			mCallback(forward<Arg>(parameters)...);
		}
		
	private:
		FunctionType mCallback;
	};


	template<typename T>
	class TFEventPool
	{
	public:
		typedef function<T> FunctionType;
		typedef TFEventHandler<T> HandlerType;

		weak_ptr<HandlerType> registerEvent(const FunctionType &callback)
		{
			auto &handler = make_shared<HandlerType>(callback);
			mHandlers.push_back(handler);
			return handler;
		}

		template <typename ...Arg>
		void dispatchEvent(Arg &&...parameters)
		{
			for (auto &handler : mHandlers) {
				(*handler)(forward<Arg>(parameters)...);
			}
		}

	private:
		vector<shared_ptr<HandlerType>> mHandlers;
	};


	class TFEventProtocol
	{
	public:
		template <typename T, typename _CB>
		auto registerEvent(const TFEvent<T> &event, const _CB &callback)
		{
			return _registerEvent<T>(event, callback);
		}

		template <typename T>
		void unregisterEvent(weak_ptr<TFEventHandler<T>> handler)
		{

		}

		template <typename T, typename ...Arg>
		void dispatchEvent(const TFEvent<T> &event, Arg &&...parameters)
		{
			int id = event.getId();
			auto eventIter = mEventPools.find(id);
			if (eventIter != mEventPools.end()) {
				static_cast<TFEventPool<T>*>(eventIter->second)->dispatchEvent(forward<Arg>(parameters)...);
			}
		}

	private:
		template <typename T>
		auto _registerEvent(const TFEvent<T> &event, const function<T> &callback)
		{
			int id = event.getId();
			auto eventIter = mEventPools.find(id);
			if (eventIter == mEventPools.end()) {
				TFEventPool<T>* _event = new TFEventPool<T>();
				mEventPools[id] = _event;
				eventIter = mEventPools.find(id);
			}
			return static_cast<TFEventPool<T>*>(eventIter->second)->registerEvent(callback);
		}

	private:
		unordered_map<int, void*> mEventPools;
	};
}
