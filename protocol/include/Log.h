#pragma once

#ifndef AJAX_CATALYST_PROTOCOL_LOG_H
#define AJAX_CATALYST_PROTOCOL_LOG_H

#include <ctime>
#include <chrono>
#include <iostream>
#include <fstream>
#include <string>

namespace AjaxCatalyst
{
	class Log
	{
	public:
		Log();
		~Log();

		void start();
		void stop();

		Log& operator<<(std::ostream& output)
		{
			// Output the given information to the console
			std::cout << output;
		}

	private:
		// File name etc...
	};
}

#endif // AJAX_CATALYST_PROTOCOL_LOG_H