#pragma once

#ifndef AJAX_CATALYST_GRAPHICAL_USER_INTERFACE_H
#define AJAX_CATALYST_GRAPHICAL_USER_INTERFACE_H

#include <iostream>
#include <string>

#include "SFML/Graphics.hpp"

namespace AjaxCatalyst
{
	class GraphicalUserInterface
	{
	public:
		GraphicalUserInterface();
		~GraphicalUserInterface();

		void start();
		void run();
		void stop();
	
	private:
		sf::RenderWindow mWindow;
	};
}

#endif