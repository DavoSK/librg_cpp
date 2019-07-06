#pragma once
#include "librg/librg.h"

namespace psychedelic::network
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
		librg_peer* GetLibrgPeer() { return mLibrgPeer; };
		
	private:
		librg_peer* mLibrgPeer;
	};
}