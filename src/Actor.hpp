/******************************************************************/
/* Violet Engine                                                  */
/* (C) Devon Artmeier 2022                                        */
/******************************************************************/

#ifndef VIOLET_ACTOR_HPP
#define VIOLET_ACTOR_HPP

namespace Violet {

	/// <summary>
	/// Actor
	/// </summary>
	class Actor {
	public:
		/// <summary>
		/// Spawn actor
		/// </summary>
		/// <typeparam name="T">Actor type</typeparam>
		/// <returns>Spawned actor</returns>
		template<class T>
		static inline std::shared_ptr<T> Spawn() {
			std::shared_ptr<T> actor = std::make_shared<T>();
			Add(actor);
			return actor;
		}

		/// <summary>
		/// Dispose of actor
		/// </summary>
		void Dispose();

		/// <summary>
		/// Get string representation of actor
		/// </summary>
		/// <returns>String representation of actor</returns>
		virtual std::string ToString() = 0;

		// Friend classes
		friend class ActorManager;
		friend class Engine;

	private:
		/// <summary>
		/// Actor update mode
		/// </summary>
		enum class UpdateMode {
			/// <summary>
			/// Normal update mode
			/// </summary>
			Normal = 0,

			/// <summary>
			/// Fixed update mode
			/// </summary>
			Fixed,

			/// <summary>
			/// Draw mode
			/// </summary>
			Draw
		};

		/// <summary>
		/// Initialize actor pool
		/// </summary>
		static void InitPool();

		/// <summary>
		/// Dispose of actor pool
		/// </summary>
		static void DisposePool();

		/// <summary>
		/// Add actor to pool
		/// </summary>
		/// <param name="actor">Actor to add</param>
		static void Add(std::shared_ptr<Actor> actor);

		/// <summary>
		/// Update actors
		/// </summary>
		/// <param name="mode">Update mode</param>
		static void Update(UpdateMode mode);

		/// <summary>
		/// Dispose of all actors
		/// </summary>
		static void DisposeAll();

		/// <summary>
		/// Actor pool
		/// </summary>
		static std::unique_ptr<std::vector<std::shared_ptr<Actor>>> pool;

		/// <summary>
		/// On spawn event
		/// </summary>
		virtual void OnSpawn() = 0;

		/// <summary>
		/// On update event
		/// </summary>
		virtual void OnUpdate() = 0;

		/// <summary>
		/// On fixed update event
		/// </summary>
		virtual void OnFixedUpdate() = 0;

		/// <summary>
		/// On draw event
		/// </summary>
		virtual void OnDraw() = 0;

		/// <summary>
		/// On dispose event
		/// </summary>
		virtual void OnDispose() = 0;

		/// <summary>
		/// Disposed flag
		/// </summary>
		bool disposed{ false };
	};

}

#endif // VIOLET_ACTOR_HPP
