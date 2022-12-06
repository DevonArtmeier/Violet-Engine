/******************************************************************/
/* Violet Engine                                                  */
/* (C) Devon Artmeier 2022                                        */
/******************************************************************/

#include "Violet.hpp"

namespace Violet {

	/// <summary>
	/// Show error message
	/// </summary>
	/// <param name="msg">Error message</param>
	void Engine::Error(std::string msg) {
		throw std::runtime_error(msg.c_str());
	}

	/// <summary>
	/// Show debug message
	/// </summary>
	/// <param name="msg">Debug message</param>
	void Engine::DebugMessage(std::string msg) {
#ifdef VIOLET_DEBUG
		printf(("[Debug] " + msg + "\n").c_str());
#endif
	}

}
