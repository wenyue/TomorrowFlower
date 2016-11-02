#pragma once

#include "TFBase.h"
#include <functional>
#include <unordered_map>
#include <unordered_set>

namespace TomorrowFlower {
	template <int _ID, typename _FunctionType>
	class TFEvent
	{
	public:
		typedef _FunctionType FunctionType;
		static const int ID = _ID;
	};
	
#define DEFINE_EVENT(name, parameters) using name = TFEvent<__COUNTER__, function<parameters>>


	template<typename _Event, typename _FunctionType = _Event::FunctionType>
	class TFEventHandler
	{
	public:
		typedef _Event Event;
		typedef _FunctionType FunctionType;
		static const int ID = _Event::ID;

		TFEventHandler(const FunctionType &callback)
			: mCallback(callback)
		{
		}

		template <typename ...Arg>
		void operator() (Arg &&...parameters)
		{
			mCallback(forward<Arg>(parameters)...);
		}

		void clear()
		{
			mCallback = nullptr;
		}

		bool canCall()
		{
			return mCallback != nullptr;
		}
		
	private:
		FunctionType mCallback;
	};


	template<typename _Event, typename _FunctionType = _Event::FunctionType>
	class TFEventPool
	{
	public:
		typedef _Event Event;
		typedef _FunctionType FunctionType;
		static const int ID = _Event::ID;

		typedef TFEventHandler<_Event, _FunctionType> HandlerType;
		typedef weak_ptr<HandlerType> HandlerPtr;

		HandlerPtr registerEvent(const FunctionType &callback)
		{
			auto &handler = make_shared<HandlerType>(callback);
			mHandlers.insert(handler);
			return handler;
		}

		void unregisterEvent(const HandlerPtr &handler)
		{
			auto ptr = handler.lock();
			if (!ptr) {
				TFError("trying to do operation for a handler that already expired");
				return;
			}

			auto iter = mHandlers.find(ptr);
			if (iter == mHandlers.end()) {
				TFError("could not find this handler in the pool");
				return;
			}

			if (mIsDispatching) {
				mDeletingHandlers.push_back(ptr);
			}
			else {
				mHandlers.erase(iter);
			}
		}

		template <typename ...Arg>
		void dispatchEvent(Arg &&...parameters)
		{
			mIsDispatching = true;
			for (auto &handler : mHandlers) {
				if (handler->canCall()) {
					(*handler)(forward<Arg>(parameters)...);
				}
				else {
					mDeletingHandlers.push_back(handler);
				}
			}
			mIsDispatching = false;

			clearDeletingHandlers();
		}

	private:
		void clearDeletingHandlers()
		{
			for (auto &handler : mDeletingHandlers) {
				mHandlers.erase(handler);
			}
			mDeletingHandlers.clear();
		}

		bool mIsDispatching = false;
		unordered_set<shared_ptr<HandlerType>> mHandlers;
		vector<shared_ptr<HandlerType>> mDeletingHandlers;
	};

	class TF_DLL TFEventProtocol
	{
	public:
		~TFEventProtocol()
		{
			if (mEventPools) {
				for (auto &iter : *mEventPools) {
					delete (iter.second);
				}

				delete mEventPools;
			}
		}

		template <typename Event, typename FunctionType = Event::FunctionType>
		auto registerEvent(const FunctionType &callback)
		{
			auto pool = findEventPool<Event>();
			if (!pool) {
				if (!mEventPools) {
					mEventPools = new unordered_map<int, void*>;
				}
				pool = new TFEventPool<Event>();
				(*mEventPools)[Event::ID] = pool;
			}
			return pool->registerEvent(callback);
		}

		template <typename HandlerPtr, typename HandlerType = HandlerPtr::element_type, typename Event = HandlerType::Event>
		void unregisterEvent(const HandlerPtr &handler)
		{
			auto pool = findEventPool<Event>();
			if (pool) {
				pool->unregisterEvent(handler);
			}
		}

		template <typename Event, typename ...Arg>
		void dispatchEvent(Arg &&...parameters)
		{
			auto pool = findEventPool<Event>();
			if (pool) {
				pool->dispatchEvent(forward<Arg>(parameters)...);
			}
		}
		
	private:
		template <typename Event, typename FunctionType = Event::FunctionType>
		auto findEventPool() -> TFEventPool<Event, FunctionType>*
		{
			if (!mEventPools) {
				return nullptr;
			}
			auto iter = mEventPools->find(Event::ID);
			if (iter != mEventPools->end()) {
				return static_cast<TFEventPool<Event>*>(iter->second);
			}
			return nullptr;
		}

		unordered_map<int, void*> *mEventPools = nullptr;
	};
}
