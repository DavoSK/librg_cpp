#pragma once
#include "datastream.h"
#include "librg/librg.h"
#include "entity.h"
#include "peer.h"

namespace psychedelic::network
{
	class Server;
	class Event
	{
	public:
		Event(librg_event* event) : mEvent(event) {}
		~Event() {}
	
		template<typename T> 
		T* GetUserData()
		{
			assert(mEvent != nullptr && mEvent->ctx != nullptr && mEvent->ctx->user_data != nullptr);
			return reinterpret_cast<T*>(mEvent->ctx->user_data);
		}
		
		Entity GetEntity();
		DataStream GetStream();
		Peer GetPeer();
		void Reject();
	private:
		librg_event* mEvent;
	};
};