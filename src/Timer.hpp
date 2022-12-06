/******************************************************************/
/* Violet Engine                                                  */
/* (C) Devon Artmeier 2022                                        */
/******************************************************************/

#ifndef VIOLET_TIMER_HPP
#define VIOLET_TIMER_HPP

namespace Violet {

	/// <summary>
	/// Timer
	/// </summary>
	class Timer {
	public:
		/// <summary>
		/// Start timer
		/// </summary>
		void Start();

		/// <summary>
		/// Stop timer
		/// </summary>
		void Stop();

		/// <summary>
		/// Get centiseconds elapsed
		/// </summary>
		/// <returns>Centiseconds elapsed</returns>
		U64 GetCentiseconds();

		/// <summary>
		/// Get seconds elapsed
		/// </summary>
		/// <returns>Seconds elapsed</returns>
		U64 GetSeconds();

		/// <summary>
		/// Get minutes elapsed
		/// </summary>
		/// <returns>Minutes elapsed</returns>
		U64 GetMinutes();

		/// <summary>
		/// Get hours elapsed
		/// </summary>
		/// <returns>Hours elapsed</returns>
		U64 GetHours();

		/// <summary>
		/// Get string representation of timer
		/// </summary>
		/// <param name="format">Format</param>
		/// <returns>String representation of timer</returns>
		std::string ToString(std::string format);

		// Friend classes
		friend class Engine;

	private:
		/// <summary>
		/// Timer constructor
		/// </summary>
		Timer() { }

		/// <summary>
		/// Start tick
		/// </summary>
		double startTick{ 0 };

		/// <summary>
		/// End tick
		/// </summary>
		double endTick{ 0 };

		/// <summary>
		/// Stopped flag
		/// </summary>
		bool stopped{ true };
	};

}

#endif // VIOLET_TIMER_HPP
