#include <assert.h>
#include "event.h"
#include "shared_interface.h"

namespace psychedelic::network
{
	DataStream Event::GetStream()
	{
		assert(mEvent->data != nullptr);
		return { mEvent->data };
	}

	Entity Event::GetEntity()
	{
		assert(mEvent->entity != nullptr && mEvent->ctx != nullptr);
		auto sharedInterface = reinterpret_cast<SharedInterface*>(mEvent->ctx);
		return { sharedInterface->GetContext(), mEvent->entity };
	}
}