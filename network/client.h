#pragma once
#include "shared_interface.h"

namespace psychedelic::network
{
	struct ClientConfig
	{
		u32 maxEntities;
		f64 tickDelay;
		zpl_vec3 worldSize;
	};

	class Client : public SharedInterface
	{
	public:
		void Init(const ClientConfig& clientConfig);
		void Connect(const std::string& serverIp, int serverPort);
	};
};