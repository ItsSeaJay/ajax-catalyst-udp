#pragma once

#ifndef AJAX_CATALYST_PACKETS
#define AJAX_CATALYST_PACKETS

#include <cstdint>

#include "Protocol.h"

namespace AjaxCatalyst
{
	class Packet
	{
	public:
		enum class Type
		{
			Connection,
			ConnectionChallenge,
			ConnectionChallengeResponse,
			ConnectionResult
		};

		struct Header
		{
			std::uint64_t id = Protocol::ID;
			std::uint32_t rawType;
			Type type;
		};
	};
}

#endif