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

		#define EVENT_ADD(X) librg_event_add(mNetworkContext, X, [](librg_event * evnt) { \
			Event wrappedEvent(evnt); \
			auto serverInstance = reinterpret_cast<Client*>(evnt->ctx->user_data); \
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

	void Client::Connect(const std::string& serverIp, int serverPort)
	{	
		assert(mNetworkContext != nullptr);
		librg_address addr = { serverPort, const_cast<char*>(serverIp.c_str())};
		librg_network_start(mNetworkContext, addr);
	}
}
