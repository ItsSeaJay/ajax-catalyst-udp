#include <thread>

#include "SFML/System.hpp"

#include "GameplayServer.h"
#include "Listener.h"

int main(int argc, char** argv)
{
	// Use the second command line argument for the port number
	// If no such argument exists, use the default
	unsigned const short port = (argc > 1) ? atoi(argv[1]) : 6567;
	AjaxCatalyst::GameplayServer* server = new AjaxCatalyst::GameplayServer();

	// If the socket is bound and the window is open, run the main loop
	server->start();

	if (server->isOnline())
	{
		// First, we start updating the server's interface
		server->update();
	}

	// Stop the server from running
	server->stop();

	// Deallocate the server pointer from memory
	delete server;
	server = nullptr;

	return EXIT_SUCCESS;
}