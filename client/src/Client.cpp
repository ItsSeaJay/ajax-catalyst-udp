#include "Client.h"

AjaxCatalyst::Client::Client()
{}

AjaxCatalyst::Client::~Client()
{}

void AjaxCatalyst::Client::start()
{
	// Attempt to create a new window
	mWindow.create(sf::VideoMode(1024, 768), "AjaxCatalystClient");

	// Load the fonts
	if (mFont.loadFromFile("Assets/Fonts/Roboto/Roboto-Regular.ttf"))
	{
		mText.setFont(mFont);
	}
}

void AjaxCatalyst::Client::update(const float& delta)
{
	sf::Packet packet;

	switch (mState)
	{
	case AjaxCatalyst::Client::State::Disconnected:
		mText.setString("Disconnected.\nClick to connect.");
		break;
	case AjaxCatalyst::Client::State::Connecting:
		mText.setString("Connecting...");
		break;
	case AjaxCatalyst::Client::State::Connected:
		mText.setString("Connected.");
		break;
	default:
		break;
	}
}

void AjaxCatalyst::Client::pollEvents()
{
	sf::Event event;
	sf::FloatRect visibleArea;

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
		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Left &&
				mState == State::Disconnected)
			{
				// Attempt to connect to the server
				mState = connect();
			}
			break;
		case sf::Event::Resized:
			// Update the view to match the new size of the window
			visibleArea.width = float(event.size.width);
			visibleArea.height = float(event.size.height);

			mWindow.setView(sf::View(visibleArea));
			break;
		default:
			break;
		}
	}
}

void AjaxCatalyst::Client::draw()
{
	mWindow.clear();
		mWindow.draw(mText);
	mWindow.display();
}

void AjaxCatalyst::Client::stop()
{
	mSocket.unbind();
}

AjaxCatalyst::Client::State AjaxCatalyst::Client::connect()
{
	sf::Packet connectionPacket;
	sf::Packet serverResponse;
	sf::IpAddress address;
	unsigned short port;
	const unsigned short attempts = 5;

	mText.setString("Connecting...");

	if (mSocket.bind(sf::Socket::AnyPort) == sf::Socket::Done)
	{
		// Serialise and send the connection packet to the server
		connectionPacket << AjaxCatalyst::Protocol::ID;
		connectionPacket << static_cast<sf::Uint32>(Packet::Type::Connection);

		// Send multiple packets to account for loss
		for (int attempt = 0; attempt < attempts; ++attempt)
		{
			mSocket.send
			(
				connectionPacket,
				sf::IpAddress::LocalHost, // TODO: Make this configurable
				6567
			);
		}

		if (receive(mSocket, serverResponse, sf::milliseconds(100)) == sf::Socket::Done)
		{
			return State::Connected;
		}
	}

	// The connection attempt failed
	return State::Disconnected;
}

sf::Socket::Status AjaxCatalyst::Client::receive
(
	sf::UdpSocket& socket,
	sf::Packet& packet,
	const sf::Time& timeout
)
{
	sf::SocketSelector selector;
	sf::IpAddress address;
	unsigned short port;

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

const bool& AjaxCatalyst::Client::isOpen() const
{
	return mWindow.isOpen();
}
