/******************************************************************/
/* Violet Engine                                                  */
/* (C) Devon Artmeier 2022                                        */
/******************************************************************/

#ifndef VIOLET_SHELL_HPP
#define VIOLET_SHELL_HPP

namespace Violet {

	/// <summary>
	/// Screen mode
	/// </summary>
	enum class ScreenMode {
		Windowed = 0,
		Fullscreen,
		FullscreenBorderless
	};

	/// <summary>
	/// Shell
	/// </summary>
	class Shell {
	private:
		// Friend classes
		friend class Engine;
		friend class EngineTimer;
		friend class Graphics;
		friend class Sound;

		/// <summary>
		/// Initialize shell
		/// </summary>
		static void Initialize();

		/// <summary>
		/// Update events
		/// </summary>
		/// <returns>True if running, false if not</returns>
		static bool UpdateEvents();

		/// <summary>
		/// Update graphics start
		/// </summary>
		static void UpdateGraphicsStart();

		/// <summary>
		/// Update graphics end
		/// </summary>
		static void UpdateGraphicsEnd();

		/// <summary>
		/// Update sound
		/// </summary>
		/// <param name="buffer">Sound buffer</param>
		static void UpdateSound(S16* buffer);

		/// <summary>
		/// Stop shell
		/// </summary>
		static void Stop();

		/// <summary>
		/// Dispose of shell data
		/// </summary>
		static void Dispose();

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

		/// <summary>
		/// Set screen mode
		/// </summary>
		/// <param name="newMode">Screen mode</param>
		static void SetScreenMode(ScreenMode newMode);

		/// <summary>
		/// Set VSync flag
		/// </summary>
		/// <param name="enable">VSync enable flag</param>
		static void SetVSync(const bool enable);

		/// <summary>
		/// Get tick
		/// </summary>
		/// <returns>Tick</returns>
		static double GetTick();

		/// <summary>
		/// Mix sound buffer
		/// </summary>
		/// <param name="inBuffer">Input buffer</param>
		/// <param name="outBuffer">Output buffer</param>
		/// <param name="length">Buffer length</param>
		/// <param name="volume">Volume</param>
		static void MixSound(S16* inBuffer, S16* outBuffer, const int length, const float volume);

		/// <summary>
		/// VSync flag
		/// </summary>
		static bool vsync;

		/// <summary>
		/// Screen mode
		/// </summary>
		static ScreenMode screenMode;

		/// <summary>
		/// Tick frequency
		/// </summary>
		static double tickFreq;
	};

}

#endif // VIOLET_SHELL_HPP
