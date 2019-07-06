#include <assert.h>
#include "event.h"

namespace psychedelic::network
{
	DataStream Event::GetStream()
	{
		assert(mEvent != nullptr && mEvent->data != nullptr);
		return { mEvent->data };
	}

	Peer Event::GetPeer()
	{
		assert(mEvent != nullptr);
		return mEvent->peer;
	}

	void Event::Reject()
	{
		assert(mEvent != nullptr);
		librg_event_reject(mEvent);
	}

	Entity Event::GetEntity()
	{
		assert(mEvent != nullptr && mEvent->entity != nullptr);
		return { mEvent->entity };
	}
}