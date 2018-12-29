#pragma once // Only include this file once

#ifndef ACGS_SERVER_H
#define ACGS_SERVER_H

#include <iostream>

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
			bool mOnline = true;
			const unsigned short& mPort;
	};
}

#endif