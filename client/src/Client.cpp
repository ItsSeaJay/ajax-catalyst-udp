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

	// Add the socket to the selector
	mSocketSelector.add(mSocket);
}

void AjaxCatalyst::Client::update(const float& delta)
{
	switch (mState)
	{
	case AjaxCatalyst::Client::State::Disconnected:
		mText.setString("Disconnected.\nClick to connect.");

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			connect();
		}
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

void AjaxCatalyst::Client::connect()
{
	sf::Packet connectionPacket;
	sf::Packet connectionChallengeResponse;

	mState = State::Connecting;

	if (mSocket.bind(sf::Socket::AnyPort) == sf::Socket::Done)
	{
		sf::Uint64 protocolID = 0xf0381ce1a55b6bc4;

		connectionPacket << protocolID;

		mSocket.send
		(
			connectionPacket,
			sf::IpAddress::LocalHost,
			6567
		);
	}
}

const bool& AjaxCatalyst::Client::isOpen() const
{
	return mWindow.isOpen();
}
