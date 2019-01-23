#pragma once

#ifndef AJAX_CATALYST_CLIENT_H
#define AJAX_CATALYST_CLIENT_H

#include <iostream>

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

namespace AjaxCatalyst
{
	class Client
	{
	public:
		Client();
		~Client();

		// Game events
		void start();
		void update(const float& delta);
		void pollEvents();
		void draw();
		void stop();

		const bool& isOpen() const;

	private:
		sf::RenderWindow mWindow;
	};
}

#endif