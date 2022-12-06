/******************************************************************/
/* Violet Engine                                                  */
/* (C) Devon Artmeier 2022                                        */
/******************************************************************/

#ifndef VIOLET_SOUND_SOURCE_OGG_HPP
#define VIOLET_SOUND_SOURCE_OGG_HPP

#include <vorbis/vorbisfile.h>

namespace Violet {

	/// <summary>
	/// Ogg sound source
	/// </summary>
	class SoundSourceOgg : public SoundSource {
	public:
		/// <summary>
		/// Ogg sound source destructor
		/// </summary>
		~SoundSourceOgg();

		/// <summary>
		/// Stream audio data
		/// </summary>
		/// <returns>True if active, false if not</returns>
		bool Stream();

		// Friend classes
		friend class Engine;
		friend class Sound;

	private:
		/// <summary>
		/// Ogg sound source constructor
		/// </summary>
		/// <param name="fileName">File name</param>
		/// <param name="file">File handler</param>
		/// <param name="loop">Loop flag</param>
		SoundSourceOgg(std::string fileName, OggVorbis_File* const file, const bool loop);

		// File handler
		OggVorbis_File* file{ nullptr };
	};

}

#endif // VIOLET_SOUND_SOURCE_OGG_HPP
