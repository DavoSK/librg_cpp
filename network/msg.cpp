#include "msg.h"
#include <assert.h>

namespace psychedelic::network
{
	DataStream Message::GetStream()
	{
		assert(mLibrgMessage->data != nullptr);
		return { mLibrgMessage->data };
	}
}