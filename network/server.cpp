#include "server.h"

namespace psychedelic::network
{
	void Server::Init(const ServerConfig& serverConfig)
	{
		mNetworkContext->mode			 = LIBRG_MODE_SERVER;
		mNetworkContext->max_entities	 = serverConfig.maxEntities;
		mNetworkContext->max_connections = serverConfig.maxConnections;
		mNetworkContext->tick_delay		 = serverConfig.tickDelay;
		mNetworkContext->world_size		 = serverConfig.worldSize;
		mNetworkContext->user_data		 = reinterpret_cast<void*>(this);
		
		librg_init(mNetworkContext);

		#define EVENT_ADD(X) librg_event_add(mNetworkContext, X, [](librg_event * evnt) { \
			Event wrappedEvent(evnt); \
			auto serverInstance = reinterpret_cast<Server*>(evnt->ctx->user_data); \
			if (serverInstance && serverInstance->GetEvents()[X]) \
				serverInstance->GetEvents()[X](wrappedEvent); \
		});

		EVENT_ADD(LIBRG_CONNECTION_ACCEPT);
		EVENT_ADD(LIBRG_CONNECTION_REQUEST);
		EVENT_ADD(LIBRG_CONNECTION_DISCONNECT);
		
		EVENT_ADD(LIBRG_CLIENT_STREAMER_UPDATE);
		EVENT_ADD(LIBRG_CLIENT_STREAMER_ADD);
		EVENT_ADD(LIBRG_CLIENT_STREAMER_REMOVE);

		EVENT_ADD(LIBRG_ENTITY_UPDATE);
		EVENT_ADD(LIBRG_ENTITY_CREATE);
		EVENT_ADD(LIBRG_ENTITY_REMOVE);
	}

	void Server::Start(const std::string& serverIp, int serverPort)
	{
		assert(mNetworkContext != nullptr);
		librg_address addr = { (i32)serverPort, const_cast<char*>(serverIp.c_str()) };
		librg_network_start(mNetworkContext, addr);
	}

	void Server::SetDefaultClientType(u32 clientType)
	{
		librg_option_set(LIBRG_DEFAULT_CLIENT_TYPE, clientType);
	}

	void Server::SetDefaultStreamRange(u32 streamRange)
	{
		librg_option_set(LIBRG_DEFAULT_STREAM_RANGE, streamRange);
	}

	Entity Server::EntityCreate(u32 entityType)
	{
		assert(mNetworkContext != nullptr);
		return { mNetworkContext, librg_entity_create(mNetworkContext, entityType) };
	}

	void Server::EntityDestroy(Entity entityToDestroy)
	{
		assert(mNetworkContext != nullptr);
		librg_entity_destroy(mNetworkContext, entityToDestroy.GetID());
	}

	u64 Server::GetMaxConnections()
	{
		assert(mNetworkContext != nullptr);
		return mNetworkContext->max_connections;
	}
};