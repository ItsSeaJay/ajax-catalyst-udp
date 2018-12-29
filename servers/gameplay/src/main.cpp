#include <iostream>

#include "GameplayServer.h"

int main(int argc, char** argv)
{
	// Use the second command line argument for the port number
	unsigned const short port = (argc > 1) ? atoi(argv[1]) : 6567;
	AjaxCatalyst::GameplayServer* server = new AjaxCatalyst::GameplayServer(port);

	// Attempts to bind a socket to the given port number
	server->start();

	// If the socket is bound,
	// run the main loop
	while (server->isOnline())
	{
		server->serve();
	}

	// Deallocate the server from memory
	delete server;
	server = nullptr;

	return EXIT_SUCCESS;
}