#include "Client.h"

AjaxCatalyst::Client::Client()
{}

AjaxCatalyst::Client::~Client()
{}

void AjaxCatalyst::Client::start()
{
	mWindow.create(sf::VideoMode(1024, 768), "AjaxCatalyst");
}

void AjaxCatalyst::Client::update(const float& delta)
{
	
}

void AjaxCatalyst::Client::pollEvents()
{
	sf::Event event;

	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			mWindow.close();
			break;
		default:
			break;
		}
	}
}

void AjaxCatalyst::Client::draw()
{

}

void AjaxCatalyst::Client::stop()
{

}

const bool& AjaxCatalyst::Client::isOpen() const
{
	return mWindow.isOpen();
}
