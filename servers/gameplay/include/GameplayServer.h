// Only allow this file to be included once
#pragma once

#ifndef AJAX_CATALYST_GAMEPLAY_SERVER_H
#define AJAX_CATALYST_GAMEPLAY_SERVER_H

#include <iostream>
#include <list>

#include "SFML/Network.hpp"

namespace AjaxCatalyst
{
	class GameplayServer
	{
		public:
			GameplayServer(const unsigned short& port);
			~GameplayServer();

			void start();
			void serve();

			const bool& isOnline() const;

		private:
			// Whether the server is connected to the internet
			// This starts off false because the port number might be invalid
			bool mOnline = false;
			const unsigned short& mPort;
			const unsigned short& mCapacity = 32;

			sf::UdpSocket mSocket;
	};
}

#endif