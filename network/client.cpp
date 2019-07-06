#include "client.h"

namespace psychedelic::network
{
	void Client::Init(const ClientConfig& clientConfig)
	{
		mNetworkContext->mode = LIBRG_MODE_CLIENT;
		mNetworkContext->max_entities = clientConfig.maxEntities;
		mNetworkContext->tick_delay = clientConfig.tickDelay;
		mNetworkContext->world_size = clientConfig.worldSize;
		mNetworkContext->user_data = reinterpret_cast<void*>(this);

		librg_init(mNetworkContext);
		RegisterDefaultEvents();
	}

	void Client::Connect(const std::string& serverIp, int serverPort)
	{	
		librg_address addr = { serverPort, const_cast<char*>(serverIp.c_str())};
		librg_network_start(mNetworkContext, addr);
	}

	bool Client::IsConnected() const
	{
		assert(mNetworkContext != nullptr);
		return librg_is_connected(mNetworkContext);
	}
}
