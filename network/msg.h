#pragma once

#include "librg/librg.h"
#include "datastream.h"
#include "peer.h"

namespace psychedelic::network
{
	class Server;
	class Message
	{
	public:
		Message(librg_message* message) :
			mLibrgMessage(message)
		{
		};

		~Message() {};
		
		Server* GetServer();
		Peer GetPeer();
		DataStream GetStream();
	private:
		librg_message* mLibrgMessage;
	};
}