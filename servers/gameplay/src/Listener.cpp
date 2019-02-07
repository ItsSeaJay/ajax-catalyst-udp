#include "Listener.h"

AjaxCatalyst::Listener::Listener(const unsigned short& port)
	: mPort(port)
{}

void AjaxCatalyst::Listener::start()
{
	mSocket.bind(mPort);
}

void AjaxCatalyst::Listener::stop()
{
	mSocket.unbind();
}

const sf::Socket::Status& AjaxCatalyst::Listener::receive
(
	sf::Packet& packet,
	sf::IpAddress& address,
	unsigned short& port,
	const sf::Time& timeout
)
const
{
	sf::SocketSelector selector;

	return sf::Socket::NotReady;
}