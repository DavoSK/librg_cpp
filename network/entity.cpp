#include "entity.h"

namespace network
{
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