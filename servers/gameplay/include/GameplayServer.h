#pragma once

#ifndef AJAX_CATALYST_GAMEPLAY_SERVER_H
#define AJAX_CATALYST_GAMEPLAY_SERVER_H

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <list>

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

			const sf::Socket::Status& receive
			(
				sf::UdpSocket& socket,
				sf::Packet& packet,
				sf::IpAddress& address,
				unsigned short& port,
				const sf::Time& timeout
			) const;
			
		private:
			// The port number this server is bound to
			const unsigned short mPort = 6567;

			// The maximum amount of clients this server can handle
			const unsigned short mCapacity = 32;

			// The log that the server will output to
			Log mLog;

			// The graphical user interface of the server
			sf::RenderWindow mWindow;

			// The socket used to listen for new connections
			sf::UdpSocket mSocket;
	
			// Respond to a given packet
			void respond(sf::Packet packet, const sf::IpAddress& address, const unsigned short& port);

			// Used to validate incoming packets
			bool valid(sf::Packet packet);
	};
}

#endif