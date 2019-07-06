#include "entity.h"

namespace psychedelic::network
{
	u32 Entity::GetID()
	{
		assert(mLibrgEntity != nullptr);
		return mLibrgEntity->id;
	}

	u32 Entity::GetType()
	{
		assert(mLibrgEntity != nullptr);
		return mLibrgEntity->type;
	}

	void Entity::SetType(u32 type)
	{
		assert(mLibrgEntity != nullptr);
		mLibrgEntity->type = type;
	}

	u64 Entity::GetFlags()
	{
		assert(mLibrgEntity != nullptr);
		return mLibrgEntity->flags;
	}

	void Entity::SetFlags(u64 flags)
	{
		assert(mLibrgEntity != nullptr);
		mLibrgEntity->flags = flags;
	}

	zpl_vec3 Entity::GetPosition()
	{
		assert(mLibrgEntity != nullptr);
		return mLibrgEntity->position;
	}

	void Entity::SetPosition(zpl_vec3 position)
	{
		assert(mLibrgEntity != nullptr);
		mLibrgEntity->position = position;
	}

	f32 Entity::GetStreamRange()
	{
		assert(mLibrgEntity != nullptr);
		return mLibrgEntity->stream_range;
	}

	void Entity::SetStreamRange(f32 streamRange)
	{
		assert(mLibrgEntity != nullptr);
		mLibrgEntity->stream_range = streamRange;
	}

	void Entity::SetControl(Peer controllPeer)
	{
		auto librgPeer = controllPeer.GetLibrgPeer();
		assert(mLibrgContext != nullptr && librgPeer != nullptr && mLibrgEntity != nullptr);

		//NOTE(DavoSK): You can do SetControll only on serverside
		assert(mLibrgContext->mode == LIBRG_MODE_SERVER);
		librg_entity_control_set(mLibrgContext, mLibrgEntity->id, librgPeer);
	}

	void Entity::RemoveControl()
	{
		assert(mLibrgContext != nullptr && mLibrgEntity != nullptr);

		//NOTE(DavoSK): You can do RemoveControl only on serverside
		assert(mLibrgContext->mode == LIBRG_MODE_SERVER);
		librg_entity_control_remove(mLibrgContext, mLibrgEntity->id);
	}

	Peer Entity::GetControl()
	{
		assert(mLibrgContext != nullptr && mLibrgEntity != nullptr);
		
		//NOTE(DavoSK): You can do RemoveControl only on serverside
		//meybe later also on client ?
		assert(mLibrgContext->mode == LIBRG_MODE_SERVER);

		return { librg_entity_control_get(mLibrgContext, mLibrgEntity->id) };
	}
}