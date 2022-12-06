/******************************************************************/
/* Violet Engine                                                  */
/* (C) Devon Artmeier 2022                                        */
/******************************************************************/

#ifndef VIOLET_SOUND_MANAGER_HPP
#define VIOLET_SOUND_MANAGER_HPP

namespace Violet {

	// Sound buffer length
	constexpr auto SoundBufferLen = 4096;
	// Sound sample rate
	constexpr auto SoundSampleRate = 44100;

	/// <summary>
	/// Sound
	/// </summary>
	class Sound {
	public:
		// Friend classes
		friend class Engine;
		friend class Shell;

		/// <summary>
		/// Initialize sound data
		/// </summary>
		static void Initialize();

		/// <summary>
		/// Dispose of sound data
		/// </summary>
		static void Dispose();

		/// <summary>
		/// Play music
		/// </summary>
		/// <param name="fileName">File name</param>
		/// <param name="loop">Loop flag</param>
		/// <param name="curFade">Fade current song out flag</param>
		/// <param name="nextFade">Fade next song in flag</param>
		static void PlayMusic(std::string fileName, const bool loop = false, const bool curFade = true, const bool nextFade = false);

		/// <summary>
		/// Set new main music without interrupting stack
		/// </summary>
		/// <param name="fileName">File name</param>
		/// <param name="loop">Loop flag</param>
		/// <param name="curFade">Fade current song out flag (only if current song is the main music)</param>
		/// <param name="nextFade">Fade next song in flag (only if current song is the main music)</param>
		static void SetMainMusic(std::string fileName, const bool loop = false, const bool curFade = true, const bool nextFade = false);

		/// <summary>
		/// Stop music
		/// </summary>
		/// <param name="fadeOut">Fade out flag</param>
		static void StopMusic(const bool fadeOut = false);

		/// <summary>
		/// Push music to stack
		/// </summary>
		/// <param name="fileName">File name</param>
		/// <param name="loop">Loop flag</param>
		/// <param name="curFade">Fade current song out flag</param>
		/// <param name="nextFade">Fade next song in flag</param>
		static void PushMusic(std::string fileName, const bool loop = false, const bool curFade = true, const bool nextFade = false);

		/// <summary>
		/// Pop music from stack
		/// </summary>
		/// <param name="curFade">Fade current song out flag</param>
		/// <param name="nextFade">Fade next song in flag</param>
		static void PopMusic(const bool curFade = true, const bool nextFade = true);

		/// <summary>
		/// Play sound effect
		/// </summary>
		/// <param name="fileName">File name</param>
		static void PlaySFX(std::string fileName);

	private:
		/// <summary>
		/// Music command type
		/// </summary>
		enum class MusicCmdType {
			/// <summary>
			/// None
			/// </summary>
			None = 0,

			/// <summary>
			/// Play song
			/// </summary>
			Play,

			/// <summary>
			/// Set main song without interrupting stack
			/// </summary>
			SetMain,

			/// <summary>
			/// Push song
			/// </summary>
			Push,

			/// <summary>
			/// Pop song
			/// </summary>
			Pop,
		
			/// <summary>
			/// Stop music
			/// </summary>
			Stop
		};

		/// <summary>
		/// Music fade mode
		/// </summary>
		enum class MusicFadeMode {
			/// <summary>
			/// None
			/// </summary>
			None = 0,

			/// <summary>
			/// In
			/// </summary>
			In,

			/// <summary>
			/// Fade out
			/// </summary>
			Out
		};

		/// <summary>
		/// Music command
		/// </summary>
		struct MusicCmd {
			/// <summary>
			/// Type
			/// </summary>
			MusicCmdType type;

			/// <summary>
			/// Accompanying song source
			/// </summary>
			std::shared_ptr<SoundSource> sound;

			/// <summary>
			/// Fade current song out flag
			/// </summary>
			bool curFade{ false };

			/// <summary>
			/// Fade next song in flag
			/// </summary>
			bool nextFade{ false };
		};

		/// <summary>
		/// Update sound
		/// </summary>
		/// <param name="buffer">Output sound buffer</param>
		static void Update(S16* const buffer);

		/// <summary>
		/// Play sound
		/// </summary>
		/// <param name="fileName">File name</param>
		/// <param name="loop">Loop flag</param>
		/// <returns>Created sound source</returns>
		static std::shared_ptr<SoundSource> PlaySound(std::string fileName, const bool loop);

		/// <summary>
		/// Main music
		/// </summary>
		static std::shared_ptr<SoundSource> mainMusic;

		/// <summary>
		/// Music stack
		/// </summary>
		static std::unique_ptr<std::vector<std::shared_ptr<SoundSource>>> musicStack;

		/// <summary>
		/// Music commands
		/// </summary>
		static std::unique_ptr<std::vector<MusicCmd>> musicCmds;

		/// <summary>
		/// Music fade mode
		/// </summary>
		static MusicFadeMode musicFadeMode;

		/// <summary>
		/// Sound effect pool
		/// </summary>
		static std::unique_ptr<std::vector<std::shared_ptr<SoundSource>>> sfx;
	};

}

#endif // VIOLET_SOUND_MANAGER_HPP
