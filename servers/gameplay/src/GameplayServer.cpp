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
	// Listen for incoming clients
}