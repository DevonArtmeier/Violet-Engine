/******************************************************************/
/* Violet Engine                                                  */
/* (C) Devon Artmeier 2022                                        */
/******************************************************************/

#ifndef VIOLET_ENGINE_HPP
#define VIOLET_ENGINE_HPP

namespace Violet {

	/// <summary>
	/// Engine
	/// </summary>
	class Engine {
	public:
		/// <summary>
		/// Run engine
		/// </summary>
		static void Run();

		/***************/
		/* APPLICATION */
		/***************/

		/// <summary>
		/// Set application name
		/// </summary>
		/// <param name="name">Application name</param>
		static void SetAppName(std::string name);

		/// <summary>
		/// Get application name
		/// </summary>
		/// <returns>Application name</returns>
		static std::string GetAppName();

		/********/
		/* FILE */
		/********/

		/// <summary>
		/// Open binary file for reading
		/// </summary>
		/// <param name="fileName">File name</param>
		/// <param name="read">Read flag</param>
		/// <returns>Binary file handler</returns>
		static std::shared_ptr<BinaryFile> OpenBinaryFile(std::string fileName, const bool read);

		/************/
		/* GRAPHICS */
		/************/

		/// <summary>
		/// Open image
		/// </summary>
		/// <param name="fileName">File name</param>
		/// <returns>Opened image</returns>
		static std::shared_ptr<Image> OpenImage(std::string fileName);

		/// <summary>
		/// Open texture
		/// </summary>
		/// <param name="fileName">File name</param>
		/// <param name="wrap">Wrap mode</param>
		/// <returns>Opened texture</returns>
		static std::shared_ptr<Texture> OpenTexture(std::string fileName, TextureWrap wrap = TextureWrap::Repeat);

		/// <summary>
		/// Open sheet
		/// </summary>
		/// <param name="fileName">File name</param>
		/// <returns>Opened sheet</returns>
		static std::shared_ptr<Sheet> OpenSheet(std::string fileName);

		/// <summary>
		/// Load map
		/// </summary>
		/// <param name="fileName">File name</param>
		static std::shared_ptr<Map> OpenMap(std::string fileName);

		/**********/
		/* MATRIX */
		/**********/

		/// <summary>
		/// Get default ortho projection matrix
		/// </summary>
		/// <returns>Default ortho projection matrix</returns>
		static Matrix4x4<float> GetDefaultOrthoMat();

		/***********/
		/* MESSAGE */
		/***********/

		/// <summary>
		/// Show error message
		/// </summary>
		/// <param name="msg">Error message</param>
		static void Error(std::string msg);

		/// <summary>
		/// Show debug message
		/// </summary>
		/// <param name="msg">Debug message</param>
		static void DebugMessage(std::string msg);

		/// <summary>
		/// Show message
		/// </summary>
		/// <param name="type">Message type</param>
		/// <param name="msg">Message</param>
		static void Message(MessageType type, std::string msg);

		/*********/
		/* SCENE */
		/*********/

		/// <summary>
		/// Set scene
		/// </summary>
		/// <typeparam name="T">Scene type</typeparam>
		template<class T>
		static inline void SetScene() {
			nextScene = std::shared_ptr<T>(new T());
		}

		/*********/
		/* SHELL */
		/*********/

		/// <summary>
		/// Get window size
		/// </summary>
		/// <returns>Window size</returns>
		static Size2D<int> GetWindowSize();

		/// <summary>
		/// Set window title
		/// </summary>
		/// <param name="title">Window title</param>
		static void SetWindowTitle(std::string title);

		/**********/
		/* TIMING */
		/**********/

		/// <summary>
		/// Get ticks elapsed
		/// </summary>
		/// <returns>Ticks elapsed</returns>
		static double GetTicks();

		/// <summary>
		/// Get Unix time
		/// </summary>
		/// <returns>TUnix time</returns>
		static S64 GetUnixTime();

		/// <summary>
		/// Get VSync flag
		/// </summary>
		/// <returns>VSync enable flag></returns>
		static bool GetVSync();

		/// <summary>
		/// Set VSync flag
		/// </summary>
		/// <param name="enable">VSync enable flag</param>
		static void SetVSync(const bool enable);

		/// <summary>
		/// Get update delta
		/// </summary>
		/// <returns>Update delta</returns>
		static float GetUpdateDelta();

		/// <summary>
		/// Get draw update delta
		/// </summary>
		/// <returns>Draw update delta</returns>
		static float GetDrawUpdateDelta();

		/// <summary>
		/// Get game frames per second
		/// </summary>
		/// <returns>Frames per second</returns>
		static float GetGameFPS();

		/// <summary>
		/// Get update frames per second
		/// </summary>
		/// <returns>Update frames per second</returns>
		static float GetUpdateFPS();

		/// <summary>
		/// Get draw frames per second
		/// </summary>
		/// <returns>Draw frames per second</returns>
		static float GetDrawFPS();

		/// <summary>
		/// Set game frames per second
		/// </summary>
		/// <param name="fps">Frames per second</param>
		static void SetGameFPS(const float fps);

		/// <summary>
		/// Create timer
		/// </summary>
		/// <returns>Created timer</returns>
		static std::shared_ptr<Timer> CreateTimer();

		// Friend classes
		friend class Actor;
		friend class App;
		friend class GraphicsManager;
		friend class Map;
		friend class Sheet;
		friend class Shell;
		friend class Texture;

	private:
		/// <summary>
		/// Close engine
		/// </summary>
		static void Close();

		/// <summary>
		/// Host application
		/// </summary>
		static std::shared_ptr<App> app;

		/// <summary>
		/// Current scene
		/// </summary>
		static std::shared_ptr<Scene> scene;

		/// <summary>
		/// Next scene
		/// </summary>
		static std::shared_ptr<Scene> nextScene;

		/// <summary>
		/// Start tick
		/// </summary>
		static double startTick;
	};

}

#endif // VIOLET_ENGINE_HPP
