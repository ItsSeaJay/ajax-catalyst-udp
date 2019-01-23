#pragma once

#ifndef AJAX_CATALYST_CLIENT_H
#define AJAX_CATALYST_CLIENT_H

#include <iostream>

#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"

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

		// Server interaction
		void connect();

		// Determines whether the game is open or not
		const bool& isOpen() const;

	private:
		enum class State {
			Disconnected,
			Connecting,
			Connected
		};
		State mState = State::Disconnected;

		sf::RenderWindow mWindow;
		sf::Font mFont;
		sf::Text mText;
		sf::UdpSocket mSocket;
	};
}

#endif