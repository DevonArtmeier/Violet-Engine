/******************************************************************/
/* Violet Engine                                                  */
/* (C) Devon Artmeier 2022                                        */
/******************************************************************/

#include "Violet.hpp"

namespace Violet {

	/// <summary>
	/// VSync flag
	/// </summary>
	bool Shell::vsync{ true };

	/// <summary>
	/// Screen mode
	/// </summary>
	ScreenMode Shell::screenMode{ ScreenMode::Windowed };

	/// <summary>
	/// Tick frequency
	/// </summary>
	double Shell::tickFreq{ 0 };

	/// <summary>
	/// Get window size
	/// </summary>
	/// <returns>Window size</returns>
	Size2D<int> Engine::GetWindowSize() {
		return Shell::GetWindowSize();
	}

	/// <summary>
	/// Set window title
	/// </summary>
	/// <param name="title">Window title</param>
	void Engine::SetWindowTitle(std::string title) {
		Shell::SetWindowTitle(title);
	}

}
