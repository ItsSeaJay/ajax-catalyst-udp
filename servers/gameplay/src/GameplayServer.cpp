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
	if (mSocketSelector.wait())
	{
		if (mSocketSelector.isReady(mSocket))
		{
			sf::Packet connectionPacket;
			sf::IpAddress address;
			unsigned short port;

			switch(mSocket.receive(connectionPacket, address, port))
			{
				case sf::Socket::Done:
					std::cout << "Done" << std::endl;
					break;
				case sf::Socket::NotReady:
					std::cout << "NotReady" << std::endl;
					break;
				case sf::Socket::Partial:
					std::cout << "Partial" << std::endl;
					break;
				case sf::Socket::Disconnected:
					std::cout << "Disconnected" << std::endl;
					break;
				case sf::Socket::Error:
					std::cout << "Error" << std::endl;
					break;
				default:
					std::cout << "default" << std::endl;
					break;
			}
		}
	}
	
}

void AjaxCatalyst::GameplayServer::stop()
{
	// Unbind the port number so that something else can use it
	mSocket.unbind();
}