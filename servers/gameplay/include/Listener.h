#pragma once

#ifndef AJAX_CATALYST_LISTENER
#define AJAX_CATALYST_LISTENER

#include "SFML/Network.hpp"

#include "Packet.h"
#include "Protocol.h"

namespace AjaxCatalyst
{
	class Listener
	{
	public:
		Listener(const unsigned short& port);

		void start();
		void stop();

		const sf::Socket::Status& receive
		(
			sf::UdpSocket& socket,
			sf::Packet& packet,
			sf::IpAddress& address,
			unsigned short& port,
			const sf::Time& timeout
		)
		const;

	private:
		const unsigned short mPort;

		sf::UdpSocket mSocket;
	};
}

#endif

