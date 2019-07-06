#pragma once
#include "librg/librg.h"
#include "peer.h"
#include <assert.h>

namespace psychedelic::network
{
	class Entity
	{
	public:
		Entity(librg_ctx* librgContext, librg_entity* librgEntity) :
			mLibrgContext(librgContext),
			mLibrgEntity(librgEntity) 
		{

		}

		~Entity() {}
		
		u32 GetID();
		u32 GetType();
		void SetType(u32 type);

		u64 GetFlags();
		void SetFlags(u64 flags);

		zpl_vec3 GetPosition();
		void SetPosition(zpl_vec3 position);
		
		f32 GetStreamRange();
		void SetStreamRange(f32 streamRange);

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