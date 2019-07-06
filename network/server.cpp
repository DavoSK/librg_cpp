#include "server.h"

namespace network
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
		RegisterDefaultEvents();
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
	
	u32 Server::GetTotalRecivedData()
	{
		auto networkHost = mNetworkContext->network.host;
		assert(networkHost != nullptr);
		return networkHost->totalReceivedData;
	}

	u32 Server::GetTotalSentData()
	{
		mNetworkContext->network.connected_peers;
		auto networkHost = mNetworkContext->network.host;
		assert(networkHost != nullptr);
		return networkHost->totalSentData;
	}
};