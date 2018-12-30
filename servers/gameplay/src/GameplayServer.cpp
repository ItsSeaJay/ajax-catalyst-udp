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

		// Add the listening socket to the selector for later use
		mSocketSelector.add(mSocket);
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

	// Wait until any socket receives data
	if (mSocketSelector.wait())
	{
		if (mSocketSelector.isReady(mSocket))
		{
			std::cout << "ready";
		}
	}
	
}

void AjaxCatalyst::GameplayServer::stop()
{
	// Unbind the port number so that something else can use it
	mSocket.unbind();
}