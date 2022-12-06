/******************************************************************/
/* Violet Engine                                                  */
/* (C) Devon Artmeier 2022                                        */
/******************************************************************/

#ifndef VIOLET_SOUND_SOURCE_HPP
#define VIOLET_SOUND_SOURCE_HPP

namespace Violet {

	/// <summary>
	/// Sound source
	/// </summary>
	class SoundSource {
	public:
		/// <summary>
		/// Sound source destructor
		/// </summary>
		virtual ~SoundSource();

		/// <summary>
		/// Stream audio data
		/// </summary>
		/// <returns>True if active, false if not</returns>
		virtual bool Stream() = 0;

		// Friend classes
		friend class Engine;
		friend class Sound;

	protected:
		/// <summary>
		/// Sound source constructor
		/// </summary>
		/// <param name="fileName">File name</param>
		/// <param name="loop">Loop flag</param>
		SoundSource(std::string fileName, const bool loop);

		/// <summary>
		/// File name
		/// </summary>
		std::string fileName{ "" };

		// Stream buffer
		S16* streamBuffer{ nullptr };
		// Current position
		U64 curPos{ 0 };

		// Loop start
		U64 loopStart{ 0 };
		// Loop end
		U64 loopEnd{ 0 };

		// Pause state
		bool paused{ false };
		// Loop flag
		bool loop{ false };
		// Fade in flag
		bool fadeIn{ false };

		// Current volume
		float volume{ 1 };
	};

}

#endif // VIOLET_SOUND_SOURCE_HPP
