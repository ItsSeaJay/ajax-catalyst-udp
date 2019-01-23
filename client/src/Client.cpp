#include "Client.h"

AjaxCatalyst::Client::Client()
{}

AjaxCatalyst::Client::~Client()
{}

void AjaxCatalyst::Client::start()
{
	// Attempt to create a new window
	mWindow.create(sf::VideoMode(1024, 768), "AjaxCatalystClient");

	// Attempt to create and set a font for the debug text
	sf::Font font;

	if (font.loadFromFile("Assets/Fonts/Roboto/Roboto-Regular.ttf"))
	{
		mDebugText.setFont(font);
	}
}

void AjaxCatalyst::Client::update(const float& delta)
{
	switch (mState)
	{
	case AjaxCatalyst::Client::State::Disconnected:
		mDebugText.setString("Disconnected.\nClick to connect.");
		break;
	case AjaxCatalyst::Client::State::Connecting:
		mDebugText.setString("Connecting...");
		break;
	case AjaxCatalyst::Client::State::Connected:
		mDebugText.setString("Connected.");
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
		mWindow.draw(mDebugText);
	mWindow.display();
}

void AjaxCatalyst::Client::stop()
{
	// Free game resources...
}

void AjaxCatalyst::Client::connect()
{

}

const bool& AjaxCatalyst::Client::isOpen() const
{
	return mWindow.isOpen();
}
