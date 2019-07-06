#pragma once
#include <assert.h>
#include "librg/librg.h"
#include "peer.h"

namespace psychedelic::network
{
	class Entity
	{
	public:
		Entity(librg_ctx* librgContext, librg_entity* librgEntity) :
			mLibrgContext(librgContext),
			mLibrgEntity(librgEntity) 
		{
			assert(mLibrgEntity != nullptr && mLibrgContext != nullptr);
		}

		~Entity() 
		{
		}

		u32 GetID()								{ return mLibrgEntity->id; }

		u32 GetType()							{ return mLibrgEntity->type; }
		void SetType(u32 type)					{ mLibrgEntity->type = type; }

		u64 GetFlags()							{ return mLibrgEntity->flags; }
		void SetFlags(u64 flags)				{ mLibrgEntity->flags = flags; }

		zpl_vec3 GetPosition()					{ return mLibrgEntity->position; }
		void SetPosition(zpl_vec3 position)		{ mLibrgEntity->position = position; }

		f32 GetStreamRange()					{ return mLibrgEntity->stream_range; }
		void SetStreamRange(f32 streamRange)	{ mLibrgEntity->stream_range = streamRange; }

		void SetControl(Peer controllPeer);
		void RemoveControl();
		Peer GetControl();

		template<typename T>
		T* GetUserData()
		{
			assert(mLibrgEntity != nullptr && mLibrgEntity->user_data != nullptr);
			return reinterpret_cast<T*>(mLibrgEntity->user_data);
		}

		template<typename T> 
		void SetUserData(T* userData)
		{
			assert(mLibrgEntity != nullptr && userData != nullptr);
			mLibrgEntity->user_data = reinterpret_cast<void*>(userData);
		}
	private:
		librg_entity* mLibrgEntity;
		librg_ctx* mLibrgContext;
	};
}