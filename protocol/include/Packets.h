#pragma once

#ifndef AJAX_CATALYST_PACKETS
#define AJAX_CATALYST_PACKETS

namespace AjaxCatalyst
{
	enum class PacketType
	{
		Connection,
		ConnectionChallenge,
		ConnectionChallengeResponse
	};
}

#endif