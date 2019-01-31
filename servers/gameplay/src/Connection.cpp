#include "Connection.h"

AjaxCatalyst::Connection::Connection
(
	const sf::IpAddress& address,
	const unsigned short& port
)
: mAddress(address), mPort(port)
{}

const sf::IpAddress& AjaxCatalyst::Connection::getIpAddress() const
{
	return mAddress;
}

const unsigned short& AjaxCatalyst::Connection::getPort() const
{
	return mPort;
}
