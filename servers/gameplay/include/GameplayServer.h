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

			// Server events
			void start();
			void serve();
			void stop();

			const bool& isOnline() const;

		private:
			// Whether the server is connected to the internet
			// This starts off false because the port number might be invalid
			bool mOnline = false;
			
			// The port number this server is bound to
			const unsigned short& mPort;

			// The maximum amount of clients this server can handle
			const unsigned short& mCapacity = 8;

			// The socket used to listen for new connections
			sf::UdpSocket mSocket;
			sf::SocketSelector mSocketSelector;
	};
}

#endif