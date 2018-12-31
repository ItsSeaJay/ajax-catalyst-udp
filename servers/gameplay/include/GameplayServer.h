#pragma once

#ifndef AJAX_CATALYST_GAMEPLAY_SERVER_H
#define AJAX_CATALYST_GAMEPLAY_SERVER_H

#include <iostream>
#include <list>
#include <mutex>

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/Network.hpp"

#include "Connection.h"

namespace AjaxCatalyst
{
	class GameplayServer
	{
		public:
			GameplayServer(const unsigned short& port);
			~GameplayServer();

			bool start();
			void serve();
			void update();
			void pollEvents();
			void display();
			void stop();

		private:
			// The graphical user interface of the server
			sf::RenderWindow mWindow;

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