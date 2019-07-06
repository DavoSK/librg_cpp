#pragma once
#include "librg/librg.h"
#include "peer.h"
#include "msg.h"
#include "entity.h"
#include "event.h"
#include <functional>

namespace psychedelic::network
{
	constexpr int defaultLibrgEvents[] = {
		LIBRG_CONNECTION_ACCEPT,
		LIBRG_CONNECTION_REQUEST,
		LIBRG_CONNECTION_DISCONNECT,

		LIBRG_CLIENT_STREAMER_UPDATE,
		LIBRG_CLIENT_STREAMER_ADD,
		LIBRG_CLIENT_STREAMER_REMOVE,

		LIBRG_ENTITY_UPDATE,
		LIBRG_ENTITY_CREATE,
		LIBRG_ENTITY_REMOVE
	};

	class SharedInterface
	{
	public:
		SharedInterface() : mNetworkContext(new librg_ctx)
		{
			zpl_zero_item(mNetworkContext);
		}

		~SharedInterface()
		{
			if (mNetworkContext)
				delete mNetworkContext;
		}

		void Tick();
		void Stop();
		Entity FindEntity(Peer entityPeer);
		Entity FetchEntity(u32 entityId);
		void EachEntity(std::function<void(const Entity&)> lambda, i32 entityType = -1);

		auto GetEvents() { return mEvents; }
		auto GetRegisteredMsg() { return mRegisteredMessages; }

		void SendMessageTo(u32 messageId, Peer destinationPeer, std::function<void(DataStream& stream)> lambdaStream);
		void BroadcastMessage(u32 messageId, std::function<void(DataStream& stream)> lambdaStream);
		void BroadcastMessageExcept(u32 messageId, Peer expectPeer, std::function<void(DataStream& stream)> lambdaStream);
		void RegisterMessage(u32 messageId, std::function<void(const Message&)> message);

		void OnConnect(std::function<void(const Event&)> onConnect);
		void OnDisconnect(std::function<void(const Event&)> onDisconnect);
		void OnRequest(std::function<void(const Event&)> onRequest);

		void OnClientStreamerUpdate(std::function<void(const Event&)> onClientStreamerUpdate);
		void OnClientStreamerAdd(std::function<void(const Event&)> onClientStreamerCreate);
		void OnClientStreamerRemove(std::function<void(const Event&)> onClientStreamerRemove);

		void OnEntityUpdate(std::function<void(const Event&)> onEntityUpdate);
		void OnEntityCreate(std::function<void(const Event&)> onEntityCreate);
		void OnEntityRemove(std::function<void(const Event&)> onEntityRemove);

		u32 GetMaxEntities();
		librg_ctx* GetContext() { assert(mNetworkContext != nullptr); return mNetworkContext; }
	protected:
		librg_ctx* mNetworkContext;
		void RegisterDefaultEvents();
		static void OnAllMessages(librg_message* msg);
		static void OnAllEvents(librg_event* evnt);

		std::unordered_map<u32, std::function<void(const Event&)>> mEvents;
		std::unordered_map<u32, std::function<void(const Message&)>> mRegisteredMessages;
	};
}