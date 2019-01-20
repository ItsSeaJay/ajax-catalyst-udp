#pragma once

#ifndef AJAX_CATALYST_PROTOCOL_LOG_H
#define AJAX_CATALYST_PROTOCOL_LOG_H

#include <iostream>
#include <string>

namespace AjaxCatalyst
{
	class Log
	{
	public:
		Log();
		~Log();

		Log operator<<(const std::string s)
		{
			std::cout << s;
		}

	private:
		// File name etc...
	};
}

#endif // AJAX_CATALYST_PROTOCOL_LOG_H