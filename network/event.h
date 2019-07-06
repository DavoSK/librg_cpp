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
	
		Server* GetServer();
		Entity GetEntity();
		DataStream GetStream();
		Peer GetPeer();
		void Reject();
	private:
		librg_event* mEvent;
	};
};