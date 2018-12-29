#include <iostream>

#include "GameplayServer.h"

int main(int argc, char** argv)
{
	unsigned const short port = 6567;
	AjaxCatalyst::GameplayServer* server = new AjaxCatalyst::GameplayServer(port);

	server->start();

	// Run the main loop
	do
	{
		server->serve();
	} while (server->isOnline());

	// Deallocate the server from memory
	delete server;
	server = nullptr;

	return EXIT_SUCCESS;
}