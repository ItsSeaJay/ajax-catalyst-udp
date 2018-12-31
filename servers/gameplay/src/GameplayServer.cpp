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

	if (mOnline)
	{
		// Add the listening socket to the selector for later use
		mSocketSelector.add(mSocket);

		// Create the graphical user interface
		mWindow.create
		(
			sf::VideoMode(1024, 768), // Resolution
			"AjaxCatalystGameplayServer", // Title
			sf::Style::Default
		);
	}
}

const bool& AjaxCatalyst::GameplayServer::isOnline() const
{
	return mOnline;
}

void AjaxCatalyst::GameplayServer::run(const float& deltaTime)
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
		// 	switch (mSocket.receive(connectionPacket, address, port))
		// 	{
		// 		case sf::Socket::Done:
		// 			std::cout << "New connection attempt from "
		// 				<< address
		// 				<< ':'
		// 				<< port
		// 				<< std::endl; 
		// 			break;
		// 		default:
		// 			std::cerr << "Error: Unhandled packet" << std::endl;
		// 			break;
		// 	}
		// }
	}
	
}

void AjaxCatalyst::GameplayServer::pollEvents()
{
	sf::Event event;

	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			mWindow.close();
			mOnline = false;
			break;
		case sf::Event::Resized:
			// Update the view to the new size of the window
			sf::FloatRect visibleArea(0, 0, float(event.size.width), float(event.size.height));
			mWindow.setView(sf::View(visibleArea));
			break;
		}
	}
}

void AjaxCatalyst::GameplayServer::display()
{
	mWindow.clear();

	// Draw GUI here...

	mWindow.display();
}

void AjaxCatalyst::GameplayServer::stop()
{
	// Unbind the port number so that something else can use it
	mSocket.unbind();
}