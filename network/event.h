#pragma once
#include "datastream.h"
#include "librg/librg.h"
#include "entity.h"
#include "peer.h"

namespace network
{
	class Event
	{
	public:
		Event(librg_event* event) : mEvent(event)
		{
			assert(event != nullptr);
		}
		
		~Event() 
		{
		}

		template<typename T> 
		T* GetUserData()
		{
			assert(mEvent->ctx != nullptr && mEvent->ctx->user_data != nullptr);
			return reinterpret_cast<T*>(mEvent->ctx->user_data);
		}
		
		Entity GetEntity();
		DataStream GetStream();
		Peer GetPeer() { return mEvent->peer; }
		void Reject() { librg_event_reject(mEvent); }
	private:
		librg_event* mEvent;
	};
};