/******************************************************************/
/* Violet Engine                                                  */
/* (C) Devon Artmeier 2022                                        */
/******************************************************************/

#include "Violet.hpp"
#include <ctime>

namespace Violet {

	/// <summary>
	/// Get ticks elapsed
	/// </summary>
	/// <returns>Ticks elapsed</returns>
	double Engine::GetTicks() {
		return Shell::GetTick() - startTick;
	}

	/// <summary>
	/// Get Unix time
	/// </summary>
	/// <returns>Unix time</returns>
	S64 Engine::GetUnixTime() {
		return static_cast<S64>(time(nullptr));
	}

	/// <summary>
	/// Get VSync flag
	/// </summary>
	/// <returns>VSync flag></returns>
	bool Engine::GetVSync() {
		return Shell::vsync;
	}

	/// <summary>
	/// Set VSync flag
	/// </summary>
	/// <param name="enable">VSync flag</param>
	void Engine::SetVSync(const bool enable) {
		Shell::SetVSync(enable);
	}

}
