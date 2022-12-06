/******************************************************************/
/* Violet Engine                                                  */
/* (C) Devon Artmeier 2022                                        */
/******************************************************************/

#include "Violet.hpp"

namespace Violet {

	/// <summary>
	/// Current tick
	/// </summary>
	double EngineTimer::currentTick{ 0 };

	/// <summary>
	/// Update tick
	/// </summary>
	double EngineTimer::updateTick{ 0 };

	/// <summary>
	/// Update frequency
	/// </summary>
	float EngineTimer::updateFreq{ 0 };

	/// <summary>
	/// Update frames per second
	/// </summary>
	float EngineTimer::updateFPS{ 0 };

	/// <summary>
	/// Update delta
	/// </summary>
	float EngineTimer::updateDelta{ 0 };

	/// <summary>
	/// Fixed update tick
	/// </summary>
	double EngineTimer::fixedUpdateTick{ 0 };

	/// <summary>
	/// Fixed update flag
	/// </summary>
	bool EngineTimer::fixedUpdate{ false };

	/// <summary>
	/// Draw update tick
	/// </summary>
	double EngineTimer::drawUpdateTick{ 0 };

	/// <summary>
	/// Draw update frequency
	/// </summary>
	float EngineTimer::drawUpdateFreq{ 0 };

	/// <summary>
	/// Draw update frames per second
	/// </summary>
	float EngineTimer::drawUpdateFPS{ 0 };

	/// <summary>
	/// Draw update delta
	/// </summary>
	float EngineTimer::drawUpdateDelta{ 0 };

	/// <summary>
	/// Draw update frames per second
	/// </summary>
	float EngineTimer::drawFPS{ 60 };

	/// <summary>
	/// Draw update flag
	/// </summary>
	bool EngineTimer::drawUpdate{ false };

	/// <summary>
	/// Game frames per second
	/// </summary>
	float EngineTimer::gameFPS{ 60 };

	/// <summary>
	/// Start engine timer
	/// </summary>
	void EngineTimer::Start() {
		updateTick = Engine::GetTicks();
		fixedUpdateTick = updateTick;
		drawUpdateTick = updateTick;
	}

	/// <summary>
	/// Start engine timer update
	/// </summary>
	void EngineTimer::UpdateStart() {
		currentTick = Engine::GetTicks();
		fixedUpdate = (currentTick - fixedUpdateTick) >= 1000 / gameFPS;

		drawUpdate = false;
		if (!Engine::GetVSync()) {
			if ((currentTick - drawUpdateTick) >= 1000 / drawFPS) {
				drawUpdate = true;
			}
		}
		else {
			drawUpdate = true;
		}
	}

	/// <summary>
	/// End engine timer update
	/// </summary>
	void EngineTimer::UpdateEnd() {
		updateFreq = static_cast<float>(currentTick - updateTick);
		updateFPS = 1000 / updateFreq;
		updateDelta = updateFreq * (gameFPS / 1000);
		updateTick = currentTick;

		if (fixedUpdate) {
			fixedUpdateTick = currentTick;
		}

		if (drawUpdate) {
			drawUpdateFreq = static_cast<float>(currentTick - drawUpdateTick);
			drawUpdateDelta = drawUpdateFreq * (gameFPS / 1000);
			drawUpdateTick = currentTick;
		}

	}

	/// <summary>
	/// Get update delta
	/// </summary>
	/// <returns>Update delta</returns>
	float Engine::GetUpdateDelta() {
		return EngineTimer::updateDelta;
	}

	/// <summary>
	/// Get draw update delta
	/// </summary>
	/// <returns>Draw update delta</returns>
	float Engine::GetDrawUpdateDelta() {
		return EngineTimer::drawUpdateDelta;
	}

	/// <summary>
	/// Get game frames per second
	/// </summary>
	/// <returns>Frames per second</returns>
	float Engine::GetGameFPS() {
		return EngineTimer::gameFPS;
	}

	/// <summary>
	/// Get update frames per second
	/// </summary>
	/// <returns>Update frames per second</returns>
	float Engine::GetUpdateFPS() {
		return EngineTimer::updateFPS;
	}

	/// <summary>
	/// Get draw frames per second
	/// </summary>
	/// <returns>Draw frames per second</returns>
	float Engine::GetDrawFPS() {
		return EngineTimer::drawFPS;
	}

	/// <summary>
	/// Set game frames per second
	/// </summary>
	/// <param name="fps">Frames per second</param>
	void Engine::SetGameFPS(const float fps) {
		if (fps <= 0) {
			Error("Invalid FPS value \"" + std::to_string(fps) + "\".");
		}
		EngineTimer::gameFPS = fps;
	}

}
