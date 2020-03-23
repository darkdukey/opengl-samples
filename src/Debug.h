#pragma once

#include <iostream>
#include <string>

namespace NT {

	enum Level {
		debug, error, warning, info
	};

	struct Debug_base {
		Level log_level;
		static Debug_base& getInstance() {
			static Debug_base s_instance = Debug_base();
			return s_instance;
		}

		friend Debug_base& log(Level n)
		{
			Debug_base::getInstance().log_level = n;
			switch (n)
			{
			case NT::debug:
				std::cout << "Debug: ";
				break;
			case NT::error:
				std::cout << "Error: ";
				break;
			case NT::warning:
				std::cout << "Warning: ";
				break;
			case NT::info:
				std::cout << "Info: ";
				break;
			default:
				std::cout << "Debug: ";
				break;
			}
			return Debug_base::getInstance();
		}
	};

	struct Debug
	{
		bool alive;

		Debug() : alive(true) { }
		Debug(Debug && rhs) noexcept : alive(true) { rhs.alive = false; }
		Debug(Debug const &) = delete;
		~Debug() { if (alive) std::cout << std::endl; }

	};

	template <typename T>
	Debug operator<<(Debug && o, T const & x)
	{
		std::cout << x;
		return std::move(o);
	}

	template <typename T>
	Debug operator<<(Debug_base &, T const & x)
	{
		return std::move(Debug() << x);
	}
}


