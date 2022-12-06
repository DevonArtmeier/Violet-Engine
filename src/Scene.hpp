/******************************************************************/
/* Violet Engine                                                  */
/* (C) Devon Artmeier 2022                                        */
/******************************************************************/
/* This file is subject to the terms and conditions defined in    */
/* file "LICENSE.txt", which is part of this source code package. */
/******************************************************************/

#ifndef VIOLET_SCENE_HPP
#define VIOLET_SCENE_HPP

namespace Violet {

	/// <summary>
	/// Scene
	/// </summary>
	class Scene {
	public:
		/// <summary>
		/// Get string representation of scene
		/// </summary>
		/// <returns>String representation of scene</returns>
		virtual std::string ToString() = 0;

		// Friend classes
		friend class Engine;

	private:
		/// <summary>
		/// On start event
		/// </summary>
		virtual void OnStart() = 0;

		/// <summary>
		/// On update start event
		/// </summary>
		virtual void OnUpdateStart() = 0;

		/// <summary>
		/// On update end event
		/// </summary>
		virtual void OnUpdateEnd() = 0;

		/// <summary>
		/// On fixed update start event
		/// </summary>
		virtual void OnFixedUpdateStart() = 0;

		/// <summary>
		/// On fixed update end event
		/// </summary>
		virtual void OnFixedUpdateEnd() = 0;

		/// <summary>
		/// On draw start event
		/// </summary>
		virtual void OnDrawStart() = 0;

		/// <summary>
		/// On draw end event
		/// </summary>
		virtual void OnDrawEnd() = 0;

		/// <summary>
		/// On exit event
		/// </summary>
		virtual void OnExit() = 0;
	};

	/// <summary>
	/// Startup scene
	/// </summary>
	class StartupScene : public Scene {
	public:
		/// <summary>
		/// Get string representation of startup scene
		/// </summary>
		/// <returns>String representation of startup scene</returns>
		std::string ToString();

		// Friend classes
		friend class Engine;

	private:
		/// <summary>
		/// Scene constructor
		/// </summary>
		StartupScene() { }

		/// <summary>
		/// On start event
		/// </summary>
		void OnStart();

		/// <summary>
		/// On update start event
		/// </summary>
		void OnUpdateStart();

		/// <summary>
		/// On update end event
		/// </summary>
		void OnUpdateEnd();

		/// <summary>
		/// On fixed update start event
		/// </summary>
		void OnFixedUpdateStart();

		/// <summary>
		/// On fixed update end event
		/// </summary>
		void OnFixedUpdateEnd();

		/// <summary>
		/// On draw start event
		/// </summary>
		void OnDrawStart();

		/// <summary>
		/// On draw end event
		/// </summary>
		void OnDrawEnd();

		/// <summary>
		/// On exit event
		/// </summary>
		void OnExit();
	};

}

#endif // VIOLET_SCENE_HPP
