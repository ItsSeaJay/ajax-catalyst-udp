#include "GameplayServer.h"

AjaxCatalyst::GameplayServer::GameplayServer(const unsigned short& port)
: mPort(port)
{}

AjaxCatalyst::GameplayServer::~GameplayServer() {}

void AjaxCatalyst::GameplayServer::start()
{
	mLog.start();

	// If the port is available
	if (mSocket.bind(mPort) == sf::Socket::Done)
	{
		mLog << "Started an AjaxCatalystGameplayServer on port "
		     << mPort
		     << "...\n";

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
	sf::Packet packet;
	Packet::Header header;
	sf::IpAddress address;
	unsigned short port;

	mLog << "Begun listening to network traffic..." << "\n";

	while (isOnline())
	{
		if (receive(mSocket, packet, address, port, sf::seconds(5.0f)) == sf::Socket::Done)
		{
			if (valid(packet))
			{
				respond(packet, address, port);
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
			if (event.key.code == sf::Keyboard::Escape)
			{
				mWindow.close();
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

void AjaxCatalyst::GameplayServer::respond
(
	sf::Packet packet,
	const sf::IpAddress& address,
	const unsigned short& port
)
{
	Packet::Header header;
	sf::Packet response;

	if (packet >> header.id >> header.rawType)
	{
		header.type = static_cast<Packet::Type>(header.rawType);

		switch (header.type)
		{
		case Packet::Type::Connection:
			response << Protocol::ID;
			response << static_cast<Packet::Type>(Packet::Type::ConnectionResult);

			mSocket.send(response, address, port);
			break;
		}
	}
}

bool AjaxCatalyst::GameplayServer::valid(sf::Packet packet)
{
	Packet::Header header;

	if (packet >> header.id >> header.rawType)
	{
		if (header.id == Protocol::ID)
		{
			return true;
		}
	}

	return false;
}

const sf::Socket::Status& AjaxCatalyst::GameplayServer::receive
(
	sf::UdpSocket& socket,
	sf::Packet& packet,
	sf::IpAddress& address,
	unsigned short& port,
	const sf::Time& timeout
)
const
{
	sf::SocketSelector selector;

	selector.add(socket);

	if (selector.wait(timeout))
	{
		return socket.receive(packet, address, port);
	}
	else
	{
		return sf::Socket::NotReady;
	}
}