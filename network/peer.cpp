#include "peer.h"

namespace psychedelic::network
{
	void Peer::SetDefaultTimeout(u32 minLimit, u32 maxLimit)
	{
		assert(mLibrgPeer != nullptr);
		enet_peer_timeout(mLibrgPeer, 10, minLimit, maxLimit);
	}
}