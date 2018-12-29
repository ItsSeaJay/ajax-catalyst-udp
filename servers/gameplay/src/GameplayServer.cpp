#include "GameplayServer.h"

AjaxCatalyst::GameplayServer::GameplayServer(const unsigned short& port)
: mPort(port)
{}

AjaxCatalyst::GameplayServer::~GameplayServer() {}

void AjaxCatalyst::GameplayServer::start()
{
	// Notify the user that the server has started
	std::cout << "Started an AjaxCatalystGameplayServer on port "
	          << mPort
	          << "..."
	          << std::endl;

	// Bind the member socket to the specified port
	if (mSocket.bind(mPort) == sf::Socket::Done)
	{
		// The port is free
		mOnline = true;
	}
}

const bool& AjaxCatalyst::GameplayServer::isOnline() const
{
	return mOnline;
}

void AjaxCatalyst::GameplayServer::serve()
{
	// Create containers to store the data of the new connection
	sf::Packet connectionPacket;
	sf::IpAddress address;
	unsigned short port;

	// Wait until a packet is received
	mSocket.receive(connectionPacket, address, port);

	// Display who just sent information
	std::cout << "A wild connection appeared!"
	          << std::endl;
	std::cout << "Address: "
	          << address
	          << std::endl;
	std::cout << "Port: "
	          << port
	          << std::endl;
}

void AjaxCatalyst::GameplayServer::stop()
{
	// Unbind the port number so that something else can use it
	mSocket.unbind();
}