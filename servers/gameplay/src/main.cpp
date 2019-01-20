#include <thread>

#include "SFML/System.hpp"
#include "GameplayServer.h"

int main(int argc, char** argv)
{
	// Use the second command line argument for the port number
	// If no such argument exists, use the default
	unsigned const short port = (argc > 1) ? atoi(argv[1]) : 6567;
	AjaxCatalyst::GameplayServer* server = new AjaxCatalyst::GameplayServer(port);

	// If the socket is bound and the window is open, run the main loop
	server->start();

	if (server->isOnline())
	{
		// Create a new, standard thread for network listening
		std::thread listeningThread(&AjaxCatalyst::GameplayServer::listen, server);

		// First, we start updating the server's interface
		server->update();
		// Then we start listening for network traffic afterward.
		// If we start the thread first, it will block the interface from 
		// updating, meaning that the application will become unresponsive.
		listeningThread.join();
	}

	// Stop the server from running
	server->stop();

	// Deallocate the server pointer from memory
	delete server;
	server = nullptr;

	return EXIT_SUCCESS;
}