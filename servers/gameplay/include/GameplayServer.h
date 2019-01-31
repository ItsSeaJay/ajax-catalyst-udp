#pragma once

#ifndef AJAX_CATALYST_GAMEPLAY_SERVER_H
#define AJAX_CATALYST_GAMEPLAY_SERVER_H

#include <iostream>
#include <list>
#include <mutex>

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/Network.hpp"

#include "Packet.h"
#include "Protocol.h"
#include "Connection.h"
#include "Log.h"

namespace AjaxCatalyst
{
	class GameplayServer
	{
		public:
			GameplayServer(const unsigned short& port);
			~GameplayServer();

			void start();
			void listen();
			void update();
			void pollEvents();
			void display();
			void stop();

			bool isOnline() const;
			bool connectionExists(const sf::IpAddress& ip, const unsigned short& port) const;

		private:
			// The log that the server will output to
			Log mLog;

			// The graphical user interface of the server
			sf::RenderWindow mWindow;

			// The port number this server is bound to
			const unsigned short& mPort = 6567;

			// The maximum amount of clients this server can handle
			const unsigned short& mCapacity = 32;

			// The socket used to listen for new connections
			sf::UdpSocket mSocket;

			// All of the clients currently connected to the server
			std::vector<Connection*> mClients;
	};
}

#endif