#pragma once

#ifndef AJAX_CATALYST_PROTOCOL_LOG_H
#define AJAX_CATALYST_PROTOCOL_LOG_H

#include <ctime>
#include <iostream>
#include <fstream>
#include <mutex>
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

		// This overload allows for the logger class to be used like std::cout
		template <typename T>
		Log& operator<<(const T& output)
		{
			mMutex.lock();
				std::cout << output;
				mFile << output;
			mMutex.unlock();
		}

	private:
		const std::string mFilename = "log.txt";
		
		std::ofstream mFile;
		std::mutex mMutex;
	};
}

#endif // AJAX_CATALYST_PROTOCOL_LOG_H