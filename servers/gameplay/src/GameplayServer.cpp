#include "GameplayServer.h"

AjaxCatalyst::GameplayServer::GameplayServer(const unsigned short& port)
: mPort(port)
{}

AjaxCatalyst::GameplayServer::~GameplayServer() {}

bool AjaxCatalyst::GameplayServer::start()
{
	// Notify the user that the server has started
	std::cout << "Started an AjaxCatalystGameplayServer on port "
	          << mPort
	          << "..."
	          << std::endl;

	if (mSocket.bind(mPort) == sf::Socket::Done)
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

		return true;
	}

	return false;
}

void AjaxCatalyst::GameplayServer::serve()
{
	while (mWindow.isOpen())
	{
		if (mSocketSelector.wait(sf::milliseconds(100)))
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
}

void AjaxCatalyst::GameplayServer::update()
{
	// Create all the timers necessary to handle volatile GUI render times
	sf::Clock clock;
	sf::Time lag = sf::Time::Zero;
	const sf::Time frameLimit = sf::seconds(1.0f / 60.0f); // 60 FPS limit

	while (mWindow.isOpen())
	{
		// Get how much time has elapsed since the server started
		sf::Time elapsedTime = clock.restart();

		// Accumulated lag depending on how long this GUI frame took to render
		lag += elapsedTime;

		// Perform UI functions until there is no lag remaining
		while (lag > frameLimit)
		{
			// We managed to render something in time!
			lag -= elapsedTime;

			pollEvents();
		}

		display();
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
	// Unbind the UDP port so that other programs can use it
	mSocket.unbind();
}