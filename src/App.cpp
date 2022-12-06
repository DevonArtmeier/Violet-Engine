/******************************************************************/
/* Violet Engine                                                  */
/* (C) Devon Artmeier 2022                                        */
/******************************************************************/

#include "Violet.hpp"

namespace Violet {

	/// <summary>
	/// Application constructor
	/// </summary>
	/// <param name="name">Application name</param>
	App::App(std::string name) {
		this->name = name;
	}

	/// <summary>
	/// Run application
	/// </summary>
	void App::Run() {
		Engine::app = shared_from_this();
		Engine::Run();
	}

	/// <summary>
	/// Set application name
	/// </summary>
	/// <param name="name">Application name</param>
	void Engine::SetAppName(std::string name) {
		app->name = name;
	}

	/// <summary>
	/// Get application name
	/// </summary>
	/// <returns>Application name</returns>
	std::string Engine::GetAppName() {
		return app->name;
	}

}
