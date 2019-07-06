#include <assert.h>
#include "event.h"
#include "shared_interface.h"

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
		assert(mEvent != nullptr && mEvent->entity != nullptr && mEvent->ctx != nullptr);
		auto sharedInterface = reinterpret_cast<SharedInterface*>(mEvent->ctx);
		return { sharedInterface->GetContext(), mEvent->entity };
	}
}