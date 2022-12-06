/******************************************************************/
/* Violet Engine                                                  */
/* (C) Devon Artmeier 2022                                        */
/******************************************************************/

#include "Violet.hpp"

namespace Violet {

	/// <summary>
	/// Start timer
	/// </summary>
	void Timer::Start() {
		stopped = false;
		startTick = Engine::GetTicks();
	}

	/// <summary>
	/// Stop timer
	/// </summary>
	void Timer::Stop() {
		stopped = true;
		endTick = Engine::GetTicks();
	}

	/// <summary>
	/// Get centiseconds elapsed
	/// </summary>
	/// <returns>Centiseconds elapsed</returns>
	U64 Timer::GetCentiseconds() {
		double elapsed;
		if (stopped) {
			elapsed = endTick - startTick;
		}
		else {
			elapsed = Engine::GetTicks() - startTick;
		}
		return static_cast<U64>(Math::Round(elapsed / (1000.0 / 100)));
	}

	/// <summary>
	/// Get seconds elapsed
	/// </summary>
	/// <returns>Seconds elapsed</returns>
	U64 Timer::GetSeconds() {
		return GetCentiseconds() / 100;
	}

	/// <summary>
	/// Get minutes elapsed
	/// </summary>
	/// <returns>Minutes elapsed</returns>
	U64 Timer::GetMinutes() {
		return GetCentiseconds() / 6000;
	}

	/// <summary>
	/// Get hours elapsed
	/// </summary>
	/// <returns>Hours elapsed</returns>
	U64 Timer::GetHours() {
		return GetMinutes() / 360000;
	}

	/// <summary>
	/// Get string representation of timer
	/// </summary>
	/// <param name="format">Format</param>
	/// <returns>String representation of timer</returns>
	std::string Timer::ToString(std::string format) {
		U64 centiseconds = GetCentiseconds();
		U64 seconds = centiseconds / 100;
		U64 minutes = seconds / 60;
		U64 hours = minutes / 60;
		U64 days = hours / 24;

		std::stringstream stream;
		stream.fill('0');
		bool token = false;
		bool limit = false;
		for (char chr : format) {
			if (token) {
				if (chr >= '1' && chr <= '9') {
					// Width
					stream.width(static_cast<std::streamsize>(chr - '0'));
				}
				else {
					switch (chr) {
					case 'C':
						// Centiseconds
						if (limit) {
							stream << centiseconds % 100;
						}
						else {
							stream << centiseconds;
						}
						token = false;
						limit = false;
						break;

					case 'S':
						// Seconds
						if (limit) {
							stream << seconds % 60;
						}
						else {
							stream << seconds;
						}
						token = false;
						limit = false;
						break;

					case 'M':
						// Minutes
						if (limit) {
							stream << minutes % 60;
						}
						else {
							stream << minutes;
						}
						token = false;
						limit = false;
						break;

					case 'H':
						// Hours
						if (limit) {
							stream << hours % 24;
						}
						else {
							stream << hours;
						}
						token = false;
						limit = false;
						break;

					case 'D':
						// Days
						stream << days;
						token = false;
						limit = false;
						break;

					case 'L':
						// Place limit on token
						limit = true;
						break;

					default:
						Engine::Error("Invalid token character '" + std::to_string(chr) + "' in timer string format \"" + format + "\"");
					}
				}
			}
			else {
				if (chr == '%') {
					// Token
					token = true;
				}
				else {
					// Character
					stream << chr;
				}
			}
		}
		
		return std::string(stream.str());
	}

	/// <summary>
	/// Create timer
	/// </summary>
	/// <returns>Created timer</returns>
	std::shared_ptr<Timer> Engine::CreateTimer() {
		return std::shared_ptr<Timer>(new Timer());
	}

}
