/******************************************************************/
/* Violet Engine                                                  */
/* (C) Devon Artmeier 2022                                        */
/******************************************************************/

#include "Violet.hpp"

namespace Violet {

	/// <summary>
	/// Sound source constructor
	/// </summary>
	/// <param name="fileName">File name</param>
	/// <param name="loop">Loop flag</param>
	SoundSource::SoundSource(std::string fileName, bool loop) {
		this->fileName = fileName;
		this->loop = loop;

		streamBuffer = new S16[SoundBufferLen / sizeof(S16)];
		if (!streamBuffer) {
			Engine::Error("Failed to create sound source stream buffer.");
		}
	}

	/// <summary>
	/// Sound source destructor
	/// </summary>
	SoundSource::~SoundSource() {
		if (streamBuffer) {
			delete[] streamBuffer;
		}
		Engine::DebugMessage("SOUND DELETE:        " + fileName);
	}

}
