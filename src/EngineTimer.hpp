/******************************************************************/
/* Violet Engine                                                  */
/* (C) Devon Artmeier 2022                                        */
/******************************************************************/

#ifndef VIOLET_ENGINE_TIMER_HPP
#define VIOLET_ENGINE_TIMER_HPP

namespace Violet {

	/// <summary>
	/// Engine timer
	/// </summary>
	class EngineTimer {
	private:
		// Friend classes
		friend class Engine;
		friend class Shell;

		/// <summary>
		/// Start engine timer
		/// </summary>
		static void Start();

		/// <summary>
		/// Start engine timer update
		/// </summary>
		static void UpdateStart();

		/// <summary>
		/// End engine timer update
		/// </summary>
		static void UpdateEnd();

		/// <summary>
		/// Current tick
		/// </summary>
		static double currentTick;

		/// <summary>
		/// Update tick
		/// </summary>
		static double updateTick;

		/// <summary>
		/// Update frequency
		/// </summary>
		static float updateFreq;

		/// <summary>
		/// Update frames per second
		/// </summary>
		static float updateFPS;

		/// <summary>
		/// Update delta
		/// </summary>
		static float updateDelta;

		/// <summary>
		/// Fixed update tick
		/// </summary>
		static double fixedUpdateTick;

		/// <summary>
		/// Fixed update flag
		/// </summary>
		static bool fixedUpdate;

		/// <summary>
		/// Draw update tick
		/// </summary>
		static double drawUpdateTick;

		/// <summary>
		/// Draw update frequency
		/// </summary>
		static float drawUpdateFreq;

		/// <summary>
		/// Draw update frames per second
		/// </summary>
		static float drawUpdateFPS;

		/// <summary>
		/// Draw update delta
		/// </summary>
		static float drawUpdateDelta;

		/// <summary>
		/// Draw update frames per second
		/// </summary>
		static float drawFPS;

		/// <summary>
		/// Draw update flag
		/// </summary>
		static bool drawUpdate;

		/// <summary>
		/// Game frames per second
		/// </summary>
		static float gameFPS;
	};

}

#endif // VIOLET_ENGINE_TIMER_HPP
