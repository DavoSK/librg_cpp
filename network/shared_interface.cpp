#include "shared_interface.h"

namespace network
{
	Entity SharedInterface::FindEntity(Peer entityPeer)
	{
		auto librgPeer = entityPeer.GetLibrgPeer();
		assert(librgPeer != nullptr);
		return { mNetworkContext, librg_entity_find(mNetworkContext, librgPeer) };
	}

	Entity SharedInterface::FetchEntity(u32 entityId)
	{
		return { mNetworkContext, librg_entity_fetch(mNetworkContext, entityId) };
	}

	void SharedInterface::EachEntity(std::function<void(const Entity&)> lambda, i32 entityType)
	{
		if (lambda != nullptr)
		{
			for (u32 i = 0; i < mNetworkContext->max_entities; i++)
			{
				auto librgEntity = librg_entity_fetch(mNetworkContext, i);
				if (librgEntity != nullptr)
				{
					if (entityType > -1 && librgEntity->type != entityType)
						continue;

					Entity wrappedEntity(mNetworkContext, librgEntity);
					lambda(wrappedEntity);
				}
			}
		}
	}

	void SharedInterface::Stop()
	{
		librg_network_stop(mNetworkContext);
		librg_free(mNetworkContext);
	}

	void SharedInterface::Tick()
	{
		librg_tick(mNetworkContext);
	}

	void SharedInterface::RegisterMessage(u32 messageId, std::function<void(const Message&)> message)
	{
		if (message != nullptr)
		{
			librg_network_add(mNetworkContext, messageId, OnAllMessages);
			mRegisteredMessages[messageId] = message;
		}
	}

	void SharedInterface::OnConnect(std::function<void(const Event&)> onConnect)
	{
		if (onConnect)
			mEvents[LIBRG_CONNECTION_ACCEPT] = onConnect;
	}

	void SharedInterface::OnDisconnect(std::function<void(const Event&)> onDisconnect)
	{
		if (onDisconnect)
			mEvents[LIBRG_CONNECTION_DISCONNECT] = onDisconnect;
	}

	void SharedInterface::OnRequest(std::function<void(const Event&)> onRequest)
	{
		if (onRequest)
			mEvents[LIBRG_CONNECTION_REQUEST] = onRequest;
	}

	void SharedInterface::OnClientStreamerUpdate(std::function<void(const Event&)> onClientStreamerUpdate)
	{
		if (onClientStreamerUpdate)
			mEvents[LIBRG_CLIENT_STREAMER_UPDATE] = onClientStreamerUpdate;
	}

	void SharedInterface::OnClientStreamerAdd(std::function<void(const Event&)> onClientStreamerAdd)
	{
		if (onClientStreamerAdd)
			mEvents[LIBRG_CLIENT_STREAMER_ADD] = onClientStreamerAdd;
	}

	void SharedInterface::OnClientStreamerRemove(std::function<void(const Event&)> onClientStreamerRemove)
	{
		if (onClientStreamerRemove)
			mEvents[LIBRG_CLIENT_STREAMER_REMOVE] = onClientStreamerRemove;
	}

	void SharedInterface::OnEntityUpdate(std::function<void(const Event&)> onEntityUpdate)
	{
		if (onEntityUpdate)
			mEvents[LIBRG_ENTITY_UPDATE] = onEntityUpdate;
	}

	void SharedInterface::OnEntityCreate(std::function<void(const Event&)> onEntityCreate)
	{
		if (onEntityCreate)
			mEvents[LIBRG_ENTITY_CREATE] = onEntityCreate;
	}

	void SharedInterface::OnEntityRemove(std::function<void(const Event&)> onEntityRemove)
	{
		if (onEntityRemove)
			mEvents[LIBRG_ENTITY_REMOVE] = onEntityRemove;
	}

	void SharedInterface::SendMessageTo(u32 messageId, Peer destinationPeer, std::function<void(DataStream& stream)> lambdaStream)
	{
		auto librgPeer = destinationPeer.GetLibrgPeer();
		assert(librgPeer != nullptr);

		librg_data data;
		librg_data_init(&data);
		if (lambdaStream)
		{
			DataStream dataStream(&data);
			lambdaStream(dataStream);
		}

		librg_message_send_to(mNetworkContext, messageId, librgPeer, data.rawptr, librg_data_get_wpos(&data));
		librg_data_free(&data);
	}

	void SharedInterface::BroadcastMessage(u32 messageId, std::function<void(DataStream& stream)> lambdaStream)
	{
		librg_data data;
		librg_data_init(&data);
		if (lambdaStream)
		{
			DataStream dataStream(&data);
			lambdaStream(dataStream);
		}

		librg_message_send_all(mNetworkContext, messageId, data.rawptr, librg_data_get_wpos(&data));
		librg_data_free(&data);
	}

	void SharedInterface::BroadcastMessageExcept(u32 messageId, Peer exceptPeer, std::function<void(DataStream& stream)> lambdaStream)
	{
		auto librgPeer = exceptPeer.GetLibrgPeer();
		assert(librgPeer != nullptr);

		librg_data data;
		librg_data_init(&data);
		if (lambdaStream)
		{
			DataStream dataStream(&data);
			lambdaStream(dataStream);
		}

		librg_message_send_except(mNetworkContext, messageId, librgPeer, data.rawptr, librg_data_get_wpos(&data));
		librg_data_free(&data);
	}

	void SharedInterface::RegisterDefaultEvents()
	{
		for (const auto eventId : defaultLibrgEvents)
			librg_event_add(mNetworkContext, eventId, OnAllEvents);
	}

	void SharedInterface::OnAllMessages(librg_message* msg)
	{
		assert(msg != nullptr && msg->ctx->user_data != nullptr);
		auto sharedInterfaceInstance = reinterpret_cast<SharedInterface*>(msg->ctx->user_data);
		auto registeredMessage = sharedInterfaceInstance->GetRegisteredMsg()[static_cast<unsigned int>(msg->type)];

		if (registeredMessage != nullptr)
		{
			Message wrappedMessage(msg);
			registeredMessage(wrappedMessage);
		}
	}

	void SharedInterface::OnAllEvents(librg_event* evnt)
	{
		assert(evnt != nullptr && evnt->ctx->user_data != nullptr);
		auto sharedInterfaceInstance = reinterpret_cast<SharedInterface*>(evnt->ctx->user_data);
		auto desiredEvent = sharedInterfaceInstance->GetEvents()[static_cast<unsigned int>(evnt->type)];
		
		if (desiredEvent != nullptr)
		{
			Event wrappedEvent(evnt);
			desiredEvent(wrappedEvent);
		}
	}

	u32 SharedInterface::GetMaxEntities()
	{
		return mNetworkContext->max_entities;
	}
}