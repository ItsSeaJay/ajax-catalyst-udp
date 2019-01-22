#include "GameplayServer.h"

AjaxCatalyst::GameplayServer::GameplayServer(const unsigned short& port)
: mPort(port)
{}

AjaxCatalyst::GameplayServer::~GameplayServer() {}

void AjaxCatalyst::GameplayServer::start()
{
	mLog.start();

	if (mSocket.bind(mPort) == sf::Socket::Done)
	{
		mLog << "Started an AjaxCatalystGameplayServer on port "
		     << mPort
		     << "...\n";
		
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

void AjaxCatalyst::GameplayServer::listen()
{
	mLog << "Begun listening to network traffic..."<< "\n";

	while (isOnline())
	{
		if (mSocketSelector.wait(sf::milliseconds(100)))
		{
			if (mSocketSelector.isReady(mSocket))
			{
				// Create containers to store the information of the
				// pending connection
				sf::Packet connectionPacket;
				sf::IpAddress address;
				unsigned short port;

				// React differently depending on how the packet is received
				switch (mSocket.receive(connectionPacket, address, port))
				{
					case sf::Socket::Done:
						// If the IP/Port combination is unique and
						// the server isn't yet full
						if (!connectionExists(address, port) &&
							mClients.size() < mCapacity)
						{
							Connection* client = new Connection(address, port);

							mClients.push_back(client);
						}
						break;
					default:
						mLog << "Error: Unhandled packet" << '\n';
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

	while (isOnline())
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
		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
			case sf::Keyboard::Escape:
				mWindow.close();
				break;
			default:
				break;
			}
			break;
		// This has to be last to ensure the variable is initialised
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

	// Prevent any more output to the server log
	mLog.stop();
}

bool AjaxCatalyst::GameplayServer::isOnline() const
{
	return mWindow.isOpen();
}

bool AjaxCatalyst::GameplayServer::connectionExists
(
	const sf::IpAddress& ip,
	const unsigned short& port
) const
{
	for (size_t i = 0; i < mClients.size(); i++)
	{
		if (mClients[i]->getIpAddress() == ip &&
			mClients[i]->getPort() == port)
		{
			return true;
		}
	}

	return false;
}

