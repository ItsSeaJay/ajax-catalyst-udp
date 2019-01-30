#pragma once

#ifndef AJAX_CATALYST_PACKETS
#define AJAX_CATALYST_PACKETS

#include <cstdint>

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
			std::uint64_t id;
			std::uint32_t rawType;
			Type type;
		};
	};
}

#endif