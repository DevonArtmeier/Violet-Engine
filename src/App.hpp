/******************************************************************/
/* Violet Engine                                                  */
/* (C) Devon Artmeier 2022                                        */
/******************************************************************/

#ifndef VIOLET_APP_HPP
#define VIOLET_APP_HPP

namespace Violet {

	/// <summary>
	/// Application
	/// </summary>
	class App : public std::enable_shared_from_this<App> {
	public:
		/// <summary>
		/// Application constructor
		/// </summary>
		/// <param name="name">Application name</param>
		App(std::string name);

		/// <summary>
		/// Run application
		/// </summary>
		void Run();

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
		/// On close event
		/// </summary>
		virtual void OnClose() = 0;

		/// <summary>
		/// Application name
		/// </summary>
		std::string name{ "" };
	};

}

#endif // VIOLET_APP_HPP
