/******************************************************************/
/* Violet Engine                                                  */
/* (C) Devon Artmeier 2022                                        */
/******************************************************************/

#include "Violet.hpp"

namespace Violet {

	/// <summary>
	/// Main music
	/// </summary>
	std::shared_ptr<SoundSource> Sound::mainMusic{ nullptr };

	/// <summary>
	/// Music stack
	/// </summary>
	std::unique_ptr<std::vector<std::shared_ptr<SoundSource>>> Sound::musicStack;

	/// <summary>
	/// Music commands
	/// </summary>
	std::unique_ptr<std::vector<Sound::MusicCmd>> Sound::musicCmds;

	/// <summary>
	/// Music fade mode
	/// </summary>
	Sound::MusicFadeMode Sound::musicFadeMode{ MusicFadeMode::None };

	/// <summary>
	/// Sound pool
	/// </summary>
	std::unique_ptr<std::vector<std::shared_ptr<SoundSource>>> Sound::sfx;

	/// <summary>
	/// Initialize sound data
	/// </summary>
	void Sound::Initialize() {
		musicStack = std::make_unique<std::vector<std::shared_ptr<SoundSource>>>();
		musicCmds = std::make_unique<std::vector<Sound::MusicCmd>>();
		sfx = std::make_unique<std::vector<std::shared_ptr<SoundSource>>>();
	}

	/// <summary>
	/// Dispose of sound data
	/// </summary>
	void Sound::Dispose() {
		mainMusic = nullptr;
		musicStack->clear();
		musicStack = nullptr;
		musicCmds->clear();
		musicCmds = nullptr;
		sfx->clear();
		sfx = nullptr;
	}

	/// <summary>
	/// Update sound
	/// </summary>
	/// <param name="buffer">Output sound buffer</param>
	void Sound::Update(S16* const buffer) {
		if (musicCmds && musicStack && sfx) {
			memset(buffer, 0, SoundBufferLen);

			// Music
			MusicCmd musicCmd = { };
			if (musicCmds->size() > 0) {
				musicCmd = musicCmds->at(0);
			}

			std::shared_ptr<SoundSource> song = mainMusic;
			if (musicStack->size() > 0) {
				song = musicStack->at(musicStack->size() - 1);
			}

			bool playing = false;
			if (song) {
				playing = song->Stream();
				if (playing) {
					if (song->fadeIn) {
						if (song->volume < 1) {
							song->volume += 0.05f;
							if (song->volume >= 1) {
								song->volume = 1;
								song->fadeIn = false;
							}
							else {
								// Don't process music command until fully faded in
								musicCmd.type = MusicCmdType::None;
							}
						}
					}
					Shell::MixSound(song->streamBuffer, buffer, SoundBufferLen, song->volume);
				}
			}

			if (musicCmd.type != MusicCmdType::None) {
				if (musicCmd.type == MusicCmdType::SetMain && song != mainMusic) {
					// Don't interrupt stack if just setting a new main song
					mainMusic = musicCmd.sound;
					musicCmds->erase(musicCmds->begin());
				}
				else {
					if (musicCmd.curFade && playing && song->volume > 0 &&
						!(musicCmd.type == MusicCmdType::Pop && song == mainMusic)) {
						if (song->volume > 0) {
							song->volume -= 0.05f;
							if (song->volume <= 0) {
								song->volume = 0;
								playing = false;
							}
						}
					}
					else {
						playing = false;
					}

					bool checkFade = false;
					switch (musicCmd.type) {
					case MusicCmdType::Play:
						if (!playing) {
							mainMusic = musicCmd.sound;
							musicStack->clear();
							checkFade = true;
						}
						break;

					case MusicCmdType::SetMain:
						if (!playing) {
							mainMusic = musicCmd.sound;
							checkFade = true;
						}
						break;

					case MusicCmdType::Push:
						if (!playing) {
							musicStack->push_back(musicCmd.sound);
							checkFade = true;
						}
						break;

					case MusicCmdType::Pop:
						if (!playing) {
							if (musicStack->size() > 0) {
								musicStack->pop_back();
								if (musicStack->size() > 0) {
									musicCmd.sound = musicStack->at(musicStack->size() - 1);
								}
								else {
									musicCmd.sound = mainMusic;
								}
								checkFade = true;
							}
						}
						break;

					case MusicCmdType::Stop:
						if (!playing) {
							mainMusic = nullptr;
							musicStack->clear();
						}
						break;
					}

					if (!playing) {
						if (checkFade && musicCmd.sound) {
							if (musicCmd.nextFade) {
								musicCmd.sound->fadeIn = true;
								musicCmd.sound->volume = 0;
							}
							else {
								musicCmd.sound->volume = 1;
							}
						}
						musicCmds->erase(musicCmds->begin());
					}
				}
			}
			else if (!playing) {
				// Delete song if no longer playing
				if (song == mainMusic) {
					song = nullptr;
				}
				else if (musicStack->size() > 0) {
					musicCmds->push_back({ MusicCmdType::Pop, nullptr });
				}
			}

			// SFX
			int i = 0;
			while (i < sfx->size()) {
				S16* stream_buf = sfx->at(i)->streamBuffer;
				if (!sfx->at(i)->Stream()) {
					sfx->at(i) = nullptr;
					sfx->erase(sfx->begin() + i);
				}
				else {
					Shell::MixSound(stream_buf, buffer, SoundBufferLen, 1);
					++i;
				}
			}
		}
	}

	/// <summary>
	/// Play sound
	/// </summary>
	/// <param name="fileName">File name</param>
	/// <param name="loop">Loop flag</param>
	/// <returns>Created sound source</returns>
	std::shared_ptr<SoundSource> Sound::PlaySound(std::string fileName, const bool loop) {
		std::shared_ptr<SoundSource> source = nullptr;

		// Ogg
		OggVorbis_File* vorbis_file = static_cast<OggVorbis_File*>(malloc(sizeof(OggVorbis_File)));
		if (vorbis_file) {
			if (ov_fopen(fileName.c_str(), vorbis_file) < 0) {
				free(vorbis_file);
			}
			else {
				source = std::shared_ptr<SoundSourceOgg>(new SoundSourceOgg(fileName, vorbis_file, loop));
			}
		}

		if (!source) {
			// Failed
			Engine::Error("Failed to open sound file \"" + fileName + "\"");
			return nullptr;
		}
		return source;
	}

	/// <summary>
	/// Play music
	/// </summary>
	/// <param name="fileName">File name</param>
	/// <param name="loop">Loop flag</param>
	/// <param name="curFade">Fade current song out flag</param>
	/// <param name="nextFade">Fade next song in flag</param>
	void Sound::PlayMusic(std::string fileName, const bool loop, const bool curFade, const bool nextFade) {
		std::shared_ptr<SoundSource> sound = PlaySound(fileName, loop);
		musicCmds->push_back({ MusicCmdType::Play, sound, curFade, nextFade });
	}

	/// <summary>
	/// Set new main music without interrupting stack
	/// </summary>
	/// <param name="fileName">File name</param>
	/// <param name="loop">Loop flag</param>
	/// <param name="curFade">Fade current song out flag (only if current song is the main music)</param>
	/// <param name="nextFade">Fade next song in flag (only if current song is the main music)</param>
	void Sound::SetMainMusic(std::string fileName, const bool loop, const bool curFade, const bool nextFade) {
		std::shared_ptr<SoundSource> sound = PlaySound(fileName, loop);
		musicCmds->push_back({ MusicCmdType::SetMain, sound, curFade, nextFade });
	}

	/// <summary>
	/// Stop music
	/// </summary>
	/// <param name="fadeOut">Fade out flag</param>
	void Sound::StopMusic(const bool fadeOut) {
		musicCmds->push_back({ MusicCmdType::Stop, nullptr, fadeOut, false });
	}

	/// <summary>
	/// Push music to stack
	/// </summary>
	/// <param name="fileName">File name</param>
	/// <param name="loop">Loop flag</param>
	/// <param name="curFade">Fade current song out flag</param>
	/// <param name="nextFade">Fade next song in flag</param>
	void Sound::PushMusic(std::string fileName, const bool loop, const bool curFade, const bool nextFade) {
		std::shared_ptr<SoundSource> sound = PlaySound(fileName, loop);
		musicCmds->push_back({ MusicCmdType::Push, sound, curFade, nextFade });
	}

	/// <summary>
	/// Pop music from stack
	/// </summary>
	/// <param name="curFade">Fade current song out flag</param>
	/// <param name="nextFade">Fade next song in flag</param>
	void Sound::PopMusic(const bool curFade, const bool nextFade) {
		musicCmds->push_back({ MusicCmdType::Pop, nullptr, curFade, nextFade });
	}

	/// <summary>
	/// Play sound effect
	/// </summary>
	/// <param name="fileName">File name</param>
	void Sound::PlaySFX(std::string fileName) {
		std::shared_ptr<SoundSource> sound = PlaySound(fileName, false);
		sfx->push_back(sound);
	}

}
