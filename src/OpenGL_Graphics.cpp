/******************************************************************/
/* Violet Engine                                                  */
/* (C) Devon Artmeier 2022                                        */
/******************************************************************/

#include "Violet.hpp"

namespace Violet {

	/// <summary>
	/// Initialize graphics API
	/// </summary>
	void Graphics::InitAPI() {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	/// <summary>
	/// Dispose of graphics API data
	/// </summary>
	void Graphics::DisposeAPI() {
		glUseProgram(0);
	}

	/// <summary>
	/// Update graphics manager
	/// </summary>
	void Graphics::Update() {
		Size2D<int> windowSize = Engine::GetWindowSize();
		glViewport(0, 0, windowSize.w, windowSize.h);
		glClearColor(bgColor.r, bgColor.g, bgColor.b, 1);
		glClear(GL_COLOR_BUFFER_BIT);
	}

}
