#include <iostream>

#include "Client.h"
#include "SFML/Network.hpp"

int main(int argc, char** argv)
{
	sf::UdpSocket socket;
	AjaxCatalyst::Client* client = new AjaxCatalyst::Client();

	if (socket.bind(sf::Socket::AnyPort) == sf::Socket::Done)
	{
		sf::Packet packet;
		sf::IpAddress address = "localhost";
		const unsigned short port = 6567;
		std::string message;

		std::cout << "Started a client on port "
		          << socket.getLocalPort()
		          << std::endl;

		packet << message;

		socket.send(packet, address, port);
	}
	else
	{
		std::cerr << "Failed to bind socket.";

		return EXIT_FAILURE;
	}

	// Deallocate the memory for the client
	delete client;
	client = nullptr;

	return EXIT_SUCCESS;
}