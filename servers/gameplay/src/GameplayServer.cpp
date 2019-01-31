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
					Packet::Header header;

					// Attempt to deserialize the connection packet
					if (connectionPacket >> header.id >> header.rawType)
					{
						// Convert the raw type into a usable enum
						header.type = static_cast<Packet::Type>(header.rawType);

						// If the deserialized packet is valid
						if (header.id == AjaxCatalyst::Protocol::ID &&
							header.type == Packet::Type::Connection)
						{
							mLog << "Incoming connection from "
								<< address
								<< ':'
								<< port
								<< '\n';

							// Add that client to the collection
							mClients.push_back(client);

							// Reply to the request
							sf::Packet connectionResultPacket;

							connectionResultPacket << Protocol::ID;
							connectionResultPacket << static_cast<sf::Uint32>(Packet::Type::ConnectionResult);

							mSocket.send(connectionResultPacket, address, port);

							mLog << "Connection result returned to sender!"
								<< "\n";
						}
						else
						{
							mLog << "Error: Invalid data"
								<< '\n';

							mLog << header.id << ' ' << header.rawType << '\n';
						}
					}
					else
					{
						mLog << "Error: Failed to deserialize packet"
							<< '\n';
					}
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

	// Remove all connections from the collection
	for (size_t client = 0; client < mClients.size(); ++client)
	{
		delete mClients[client];
		mClients[client] = nullptr;
	}

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
		// Connections are considered unique based on the
		// address and port combination
		if (mClients[i]->getIpAddress() == ip &&
			mClients[i]->getPort() == port)
		{
			return true;
		}
	}

	return false;
}

