#include <iostream>

#include "SFML/System.hpp"
#include "GameplayServer.h"

int main(int argc, char** argv)
{
	// Use the second command line argument for the port number
	// If no such argument exists, use the default
	unsigned const short port = (argc > 1) ? atoi(argv[1]) : 6567;
	AjaxCatalyst::GameplayServer* server = new AjaxCatalyst::GameplayServer(port);

	// Attempt to bind a socket to the given port number
	server->start();

	// If the socket is bound, run the main loop
	while (server->isOnline())
	{
		server->run();
	}

	// Stop the server from running
	server->stop();

	// Deallocate the server pointer from memory
	delete server;
	server = nullptr;

	return EXIT_SUCCESS;
}