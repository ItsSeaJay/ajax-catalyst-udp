#include <iostream>

#include "SFML/System.hpp"
#include "GameplayServer.h"

int main(int argc, char** argv)
{
	// Use the second command line argument for the port number
	// If no such argument exists, use the default
	unsigned const short port = (argc > 1) ? atoi(argv[1]) : 6567;
	AjaxCatalyst::GameplayServer* server = new AjaxCatalyst::GameplayServer(port);

	// Create all the timers necessary to handle volatile GUI render times
	sf::Clock clock;
	sf::Time lag = sf::Time::Zero;
	const sf::Time frameLimit = sf::seconds(1.0f / 60.0f); // 60 FPS limit

	// Attempt to bind a socket to the given port number
	server->start();

	// If the socket is bound and the window is open, run the main loop
	while (server->isOnline())
	{
		// Get how much time has elapsed since the server started
		sf::Time elapsedTime = clock.restart();

		// Accumulate lag depending on how long this frame took to render
		lag += elapsedTime;

		// Perform server functions until there is no lag remaining
		while (lag > frameLimit)
		{
			// We managed to handle some game logic in time!
			lag -= frameLimit;

			// Run the server with the difference between frames as a parameter
			server->run(frameLimit.asSeconds());

			// Poll all the events from the servers window and handle them
			server->pollEvents();
		}

		// Draw the user interface
		server->display();
	}

	// Stop the server from running
	server->stop();

	// Deallocate the server pointer from memory
	delete server;
	server = nullptr;

	return EXIT_SUCCESS;
}