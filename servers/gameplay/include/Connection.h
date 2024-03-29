#pragma once

#ifndef AJAX_CATALYST_CONNECTION_H
#define AJAX_CATALYST_CONNECTION_H

#include "SFML/Network.hpp"

namespace AjaxCatalyst
{
	class Connection
	{
	public:
		Connection
		(
			const sf::IpAddress& address,
			const unsigned short& port
		);

		const sf::IpAddress& getIpAddress() const;
		const unsigned short& getPort() const;
		sf::UdpSocket mSocket;

	private:
		sf::IpAddress mAddress;
		const unsigned short mPort;
		sf::Uint64 mSalt;
	};
}

#endif