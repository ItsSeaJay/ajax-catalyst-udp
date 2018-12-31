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
	mOnline = (mSocket.bind(mPort) == sf::Socket::Done);

	if(mOnline)
	{
		// Add the listening socket to the selector for later use
		mSocketSelector.add(mSocket);
	}
}

const bool& AjaxCatalyst::GameplayServer::isOnline() const
{
	return mOnline;
}

void AjaxCatalyst::GameplayServer::run()
{
	if (mSocketSelector.wait())
	{
		if (mSocketSelector.isReady(mSocket))
		{
			// Create containers to store the information of the pending connection
			sf::Packet connectionPacket;
			sf::IpAddress address;
			unsigned short port;

			// React differently depending on how the packet is received
			switch (mSocket.receive(connectionPacket, address, port))
			{
				case sf::Socket::Done:
					std::cout << "New connection attempt from "
						<< address
						<< ':'
						<< port
						<< std::endl; 
					break;
				default:
					std::cerr << "Error: Unhandled packet" << std::endl;
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