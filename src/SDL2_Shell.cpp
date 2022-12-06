/******************************************************************/
/* Violet Engine                                                  */
/* (C) Devon Artmeier 2022                                        */
/******************************************************************/

#include "Violet.hpp"

namespace Violet {

	/// <summary>
	/// Sound callback
	/// </summary>
	/// <param name="userData">User data</param>
	/// <param name="buffer">Sound buffer</param>
	/// <param name="length">Sound buffer length</param>
	static void SoundCallback(void* const userData, U8* buffer, int length);

	/// <summary>
	/// Get display mode
	/// </summary>
	/// <returns>Display mode</returns>
	static SDL_DisplayMode GetDisplayMode();

	/// <summary>
	/// Window
	/// </summary>
	static SDL_Window* window{ nullptr };

	/// <summary>
	/// OpenGL context
	/// </summary>
	static SDL_GLContext context{ nullptr };

	/// <summary>
	/// Window size back up
	/// </summary>
	static Size2D<int> windowSizeBackup{ Size2D<int>(0, 0) };

	/// <summary>
	/// Initialize shell
	/// </summary>
	void Shell::Initialize() {
		// Initialize SDL
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMECONTROLLER) != 0) {
			Engine::Error("Failed to initialize SDL2.");
		}

		// Create window
#ifdef __APPLE__
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
#endif
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

		window = SDL_CreateWindow(Engine::GetAppName().c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			1280, 720, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
		if (!window) {
			Engine::Error("Failed to create window.");
		}
		context = SDL_GL_CreateContext(window);
		if (!context) {
			Engine::Error("Failed to create OpenGL context.");
		}
		if (SDL_GL_MakeCurrent(window, context) < 0) {
			Engine::Error("Failed to set current OpenGL context.");
		}

		if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
			Engine::Error("Failed to set up OpenGL loader.");
		}

		// Initialize sound
		SDL_AudioSpec audio_specs = {0};
		audio_specs.freq = SoundSampleRate;
		audio_specs.format = AUDIO_S16SYS;
		audio_specs.channels = 2;
		audio_specs.samples = SoundBufferLen / 4;
		audio_specs.callback = SoundCallback;
		audio_specs.userdata = UpdateSound;
		if (SDL_OpenAudio(&audio_specs, nullptr) < 0) {
			Engine::Error("Failed to initialize audio.");
		}
		SDL_PauseAudio(0);

		// Initialize ticks
		tickFreq = SDL_GetPerformanceFrequency() / 1000.0;
	}

	/// <summary>
	/// Update events
	/// </summary>
	/// <returns>True if running, false if not</returns>
	bool Shell::UpdateEvents() {
		// Update keyboard input
		const U8* keyboard = SDL_GetKeyboardState(nullptr);
		Input::buttons[static_cast<int>(Button::Left)] = keyboard[SDL_SCANCODE_LEFT];
		Input::buttons[static_cast<int>(Button::Right)] = keyboard[SDL_SCANCODE_RIGHT];
		Input::buttons[static_cast<int>(Button::Up)] = keyboard[SDL_SCANCODE_UP];
		Input::buttons[static_cast<int>(Button::Down)] = keyboard[SDL_SCANCODE_DOWN];

		// Event
		SDL_Event ev;
		while (SDL_PollEvent(&ev)) {
			switch (ev.type) {
			case SDL_QUIT:
				return false;

			case SDL_WINDOWEVENT:
				// Window close
				if (ev.window.event == SDL_WINDOWEVENT_CLOSE &&
					ev.window.windowID == SDL_GetWindowID(window))
					return false;
				break;

			case SDL_KEYDOWN:
				if (ev.key.keysym.scancode == SDL_SCANCODE_F1) {
					SetVSync(!vsync);
				}
				else if (ev.key.keysym.scancode == SDL_SCANCODE_F2) {
					if (screenMode == ScreenMode::Windowed) {
						SetScreenMode(ScreenMode::Fullscreen);
					}
					else if (screenMode == ScreenMode::Fullscreen) {
					//	SetScreenMode(ScreenMode::FullscreenBorderless);
					//}
					//else if (screenMode == ScreenMode::FullscreenBorderless) {
						SetScreenMode(ScreenMode::Windowed);
					}
				}
				else if (ev.key.keysym.scancode == SDL_SCANCODE_F3) {
					if (Graphics::viewResizeModeX == ViewResize::Expand) {
						Graphics::viewResizeModeX = ViewResize::Scale;
					}
					else {
						Graphics::viewResizeModeX = ViewResize::Expand;
					}
				}
				else if (ev.key.keysym.scancode == SDL_SCANCODE_F4) {
					if (Graphics::viewResizeModeY == ViewResize::Expand) {
						Graphics::viewResizeModeY = ViewResize::Scale;
					}
					else {
						Graphics::viewResizeModeY = ViewResize::Expand;
					}
				}
			}
		}

		return true;
	}

	/// <summary>
	/// Update graphics start
	/// </summary>
	void Shell::UpdateGraphicsStart() {
		SDL_DisplayMode mode = GetDisplayMode();
		if (mode.refresh_rate == 0) {
			mode.refresh_rate = 60;
		}
		EngineTimer::drawFPS = static_cast<float>(mode.refresh_rate);
	}

	/// <summary>
	/// Update graphics end
	/// </summary>
	void Shell::UpdateGraphicsEnd() {
		SDL_GL_SwapWindow(window);
	}

	/// <summary>
	/// Update sound
	/// </summary>
	/// <param name="buffer">Sound buffer</param>
	void Shell::UpdateSound(S16* buffer) {
		Sound::Update((S16*)buffer);
	}

	/// <summary>
	/// Stop shell
	/// </summary>
	void Shell::Stop() {
		SDL_PauseAudio(1);
	}

	/// <summary>
	/// Dispose of shell data
	/// </summary>
	void Shell::Dispose() {
		Stop();
		SDL_CloseAudio();
		SDL_GL_DeleteContext(context);
		SDL_DestroyWindow(window);
		SDL_Quit();
	}

	/// <summary>
	/// Get window size
	/// </summary>
	/// <returns>Window size</returns>
	Size2D<int> Shell::GetWindowSize() {
		int width, height;
		SDL_GetWindowSize(window, &width, &height);
		return { width, height };
	}

	/// <summary>
	/// Set window title
	/// </summary>
	/// <param name="title">Window title</param>
	void Shell::SetWindowTitle(std::string title) {
		SDL_SetWindowTitle(window, title.c_str());
	}

	/// <summary>
	/// Set screen mode
	/// </summary>
	/// <param name="newMode">Screen mode</param>
	void Shell::SetScreenMode(ScreenMode newMode) {
		// Back up window size
		if (screenMode == ScreenMode::Windowed) {
			windowSizeBackup = GetWindowSize();
		}

		switch (newMode) {
		case ScreenMode::Windowed:
			SDL_ShowCursor(1);
			SDL_SetWindowFullscreen(window, 0);
			if (screenMode != ScreenMode::Windowed) {
				SDL_SetWindowSize(window, windowSizeBackup.w, windowSizeBackup.h);
			}
			break;

		case ScreenMode::Fullscreen:
			SDL_DisplayMode displayMode = GetDisplayMode();
			SDL_ShowCursor(0);
			SDL_SetWindowSize(window, displayMode.w, displayMode.h);
			SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
			break;

		case ScreenMode::FullscreenBorderless:
			SDL_ShowCursor(0);
			SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
			break;
		}

		screenMode = newMode;
	}

	/// <summary>
	/// Set VSync flag
	/// </summary>
	/// <param name="enable">VSync enable flag</param>
	void Shell::SetVSync(const bool enable) {
		vsync = enable;
		SDL_GL_SetSwapInterval(vsync ? 1 : 0);
	}

	/// <summary>
	/// Get tick
	/// </summary>
	/// <returns>Tick</returns>
	double Shell::GetTick() {
		return SDL_GetPerformanceCounter() / tickFreq;
	}

	/// <summary>
	/// Mix sound buffer
	/// </summary>
	/// <param name="inBuffer">Input buffer</param>
	/// <param name="outBuffer">Output buffer</param>
	/// <param name="length">Buffer length</param>
	/// <param name="volume">Volume</param>
	void Shell::MixSound(S16* inBuffer, S16* outBuffer, const int length, const float volume) {
		SDL_MixAudio((U8*)outBuffer, (U8*)inBuffer, length, static_cast<int>(SDL_MIX_MAXVOLUME * volume));
	}

	/// <summary>
	/// Get display mode
	/// </summary>
	/// <returns>Display mode</returns>
	static SDL_DisplayMode GetDisplayMode() {
		SDL_DisplayMode mode = { 0 };
		SDL_GetCurrentDisplayMode(SDL_GetWindowDisplayIndex(window), &mode);
		return mode;
	}

	/// <summary>
	/// Sound callback
	/// </summary>
	/// <param name="userData">User data</param>
	/// <param name="buffer">Sound buffer</param>
	/// <param name="length">Sound buffer length</param>
	void SoundCallback(void* const userData, U8* buffer, int length) {
		((void(*)(S16*))(userData))((S16*)buffer);
	}

	/// <summary>
	/// Show message
	/// </summary>
	/// <param name="type">Message type</param>
	/// <param name="msg">Message</param>
	void Engine::Message(MessageType type, std::string msg) {
		int flags = 0;
		std::string title = GetAppName();

		switch (type) {
		default:
		case MessageType::Info:
			flags = SDL_MESSAGEBOX_INFORMATION;
			break;

		case MessageType::Warning:
			title += " - Warning";
			flags = SDL_MESSAGEBOX_WARNING;
			break;

		case MessageType::Error:
			title += " - Error";
			flags = SDL_MESSAGEBOX_ERROR;
			break;
		}

		SDL_ShowSimpleMessageBox(flags, GetAppName().c_str(), msg.c_str(), nullptr);
	}

}
