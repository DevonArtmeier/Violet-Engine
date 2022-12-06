/******************************************************************/
/* Violet Engine                                                  */
/* (C) Devon Artmeier 2022                                        */
/******************************************************************/

#include "Violet.hpp"

namespace Violet {

	/// <summary>
	/// Ogg sound source constructor
	/// </summary>
	/// <param name="fileName">File name</param>
	/// <param name="file">File handler</param>
	/// <param name="loop">Loop flag</param>
	SoundSourceOgg::SoundSourceOgg(std::string fileName, OggVorbis_File* const file, const bool loop) :
		SoundSource(fileName, loop) {
		this->file = file;

		vorbis_comment* comments = ov_comment(file, -1);
		char* token;
		char* nextToken = nullptr;
		U64 loopLength = 0;

		for (int i = 0; i < comments->comments; ++i) {
			token = strtok_s(comments->user_comments[i], "=", &nextToken);

			if (nextToken) {
				if (strcmp(token, "LOOPSTART") == 0) {
					loopStart = atoi(nextToken);
				}
				else if (strcmp(token, "LOOPEND") == 0) {
					loopEnd = atoi(nextToken);
				}
				else if (strcmp(token, "LOOPLENGTH") == 0) {
					loopLength = atoi(nextToken);
				}
			}
		}

		if (loopLength > 0 && loopEnd == 0) {
			loopEnd = loopStart + loopLength;
		}

		Engine::DebugMessage("SOUND PLAY (OGG):    " + fileName + ", LOOP = " + std::to_string(loop));
	}

	/// <summary>
	/// Ogg sound source destructor
	/// </summary>
	SoundSourceOgg::~SoundSourceOgg() {
		ov_clear(file);
		free(file);
	}

	/// <summary>
	/// Stream audio data
	/// </summary>
	/// <returns>True if active, false if not</returns>
	bool SoundSourceOgg::Stream() {
		char* bufPos = (char*)streamBuffer;
		long lenLeft = SoundBufferLen;

		while (lenLeft > 0) {
			if (loop && loopEnd > 0) {
				long loop_left = static_cast<long>((loopEnd - curPos) * 4);
				if (lenLeft > loop_left) {
					lenLeft = loop_left;
				}
			}

			long read = ov_read(file, bufPos, Math::Min(SoundBufferLen, lenLeft), 0, 2, 1, nullptr);
			if (read < 0) {
				return false;
			}

			lenLeft -= read;
			bufPos += read;
			curPos += read / 4;

			if (loop && (read == 0 || (loopEnd > 0 && curPos >= loopEnd))) {
				ov_pcm_seek(file, loopStart);
				curPos = loopStart;
			}
			else if (!loop && read == 0) {
				return false;
			}
		}

		return true;
	}

}
