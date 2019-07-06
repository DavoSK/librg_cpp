#pragma once
#include "librg/librg.h"
#include "datastream.h"
#include "peer.h"

namespace psychedelic::network
{
	class Message
	{
	public:
		Message(librg_message* message) :
			mLibrgMessage(message)
		{
			assert(message != nullptr);
		};

		~Message() 
		{
		};
		
		template<typename T>
		T* GetUserData()
		{
			assert(mLibrgMessage->ctx != nullptr && mLibrgMessage->ctx->user_data != nullptr);
			return reinterpret_cast<T*>(mLibrgMessage->ctx->user_data);
		}
		
		Peer GetPeer() { return { mLibrgMessage->peer }; };
		DataStream GetStream();
	private:
		librg_message* mLibrgMessage;
	};
}