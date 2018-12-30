#include "Connection.h"

AjaxCatalyst::Connection::Connection
(
	const sf::IpAddress& address,
	const unsigned short& port
)
: mAddress(address), mPort(port)
{}