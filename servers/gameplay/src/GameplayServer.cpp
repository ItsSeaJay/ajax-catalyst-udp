#include "GameplayServer.h"

AjaxCatalyst::GameplayServer::GameplayServer() {}

AjaxCatalyst::GameplayServer::~GameplayServer() {}

void AjaxCatalyst::GameplayServer::start()
{
	mLog.start();
	
	// Create the graphical user interface
	mWindow.create
	(
		sf::VideoMode(1024, 768), // Resolution
		"AjaxCatalystGameplayServer", // Title
		sf::Style::Default
	);
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
	// Prevent any more output to the server log
	mLog.stop();
}

bool AjaxCatalyst::GameplayServer::isOnline() const
{
	return mWindow.isOpen();
}
