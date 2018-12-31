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
	if (server->start())
	{
		std::thread servingThread(&AjaxCatalyst::GameplayServer::serve, server);
		std::thread updateThread(&AjaxCatalyst::GameplayServer::update, server);

		servingThread.join();
		updateThread.join();
	}

	// Stop the server from running
	server->stop();

	// Deallocate the server pointer from memory
	delete server;
	server = nullptr;

	return EXIT_SUCCESS;
}