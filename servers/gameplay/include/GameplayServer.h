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

#include "Connection.h"
#include "Log.h"

namespace AjaxCatalyst
{
	class GameplayServer
	{
		public:
			GameplayServer();
			~GameplayServer();

			void start();
			void update();
			void pollEvents();
			void display();
			void stop();

			bool isOnline() const;
			
		private:
			// The maximum amount of clients this server can handle
			const unsigned short mCapacity = 32;

			// The log that the server will output to
			Log mLog;

			// The graphical user interface of the server
			sf::RenderWindow mWindow;
	};
}

#endif