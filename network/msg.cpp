#include "msg.h"
#include <assert.h>

namespace psychedelic::network
{
	Server* Message::GetServer()
	{
		assert(mLibrgMessage != nullptr && mLibrgMessage->ctx != nullptr && mLibrgMessage->ctx->user_data != nullptr);
		return reinterpret_cast<Server*>(mLibrgMessage->ctx->user_data);
	}

	Peer Message::GetPeer()
	{
		assert(mLibrgMessage != nullptr);
		return { mLibrgMessage->peer };
	}

	DataStream Message::GetStream()
	{
		assert(mLibrgMessage != nullptr && mLibrgMessage->data != nullptr);
		return { mLibrgMessage->data };
	}
}