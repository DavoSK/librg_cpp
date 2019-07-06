#pragma once
#include "librg/librg.h"

namespace network
{
	class Peer
	{
	public:
		Peer(librg_peer* librgPeer) : 
			mLibrgPeer(librgPeer) 
		{
		}

		~Peer() 
		{
		}

		void SetDefaultTimeout(u32 minLimit, u32 maxLimit);
		u32 GetPing() { return mLibrgPeer->roundTripTime; };
		librg_peer* GetLibrgPeer() { return mLibrgPeer; };
		
	private:
		librg_peer* mLibrgPeer;
	};
}