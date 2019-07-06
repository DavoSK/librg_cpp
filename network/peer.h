#pragma once
#include "librg/librg.h"
#include "entity.h"

namespace psychedelic::network
{
	class Peer
	{
	public:
		Peer(librg_peer* librgPeer) : 
			mLibrgPeer(librgPeer) {}
		~Peer() {}

		librg_peer* GetLibrgPeer() { return mLibrgPeer; }
		void SetDefaultTimeout(u32 minLimit, u32 maxLimit);
	private:
		librg_peer* mLibrgPeer;
	};
}