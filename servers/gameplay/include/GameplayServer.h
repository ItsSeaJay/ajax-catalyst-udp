#pragma once

#ifndef AJAX_CATALYST_GAMEPLAY_SERVER_H
#define AJAX_CATALYST_GAMEPLAY_SERVER_H

#include <iostream>
#include <list>

#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"

#include "Connection.h"

namespace AjaxCatalyst
{
	class GameplayServer
	{
		public:
			GameplayServer(const unsigned short& port);
			~GameplayServer();

			void start();
			void run(const float& deltaTime);
			void pollEvents();
			void display();
			void stop();

			const bool& isOnline() const;

		private:
			// The graphical user interface of the server
			sf::RenderWindow mWindow;

			// Whether the server is connected to the internet
			// This starts off false because the port number might be invalid
			bool mOnline = false;
			
			// The port number this server is bound to
			const unsigned short& mPort;

			// The maximum amount of clients this server can handle
			const unsigned short& mCapacity = 32;

			// The socket used to listen for new connections
			sf::UdpSocket mSocket;
			
			// Multiplexer used to read from different sockets on the same thread
			sf::SocketSelector mSocketSelector;

			// All of the clients currently connected to the server
			std::list<Connection*> mClients;
	};
}

#endif