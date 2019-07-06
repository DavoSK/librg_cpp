#pragma once
#include "shared_interface.h"

namespace psychedelic::network
{
	struct ServerConfig
	{
		u32 maxEntities;
		u16 maxConnections;
		f64 tickDelay;
		zpl_vec3 worldSize;
	};

	class Server : public SharedInterface
	{
	public:
		void Init(const ServerConfig& serverConfig);
		
		void SetDefaultClientType(u32 clientType);
		void SetDefaultStreamRange(u32 streamRange);
		u64 GetMaxConnections();

		void Start(const std::string& serverIp, int serverPort);
		Entity EntityCreate(u32 entityType);
		void EntityDestroy(Entity entityToDestory);
	};
};