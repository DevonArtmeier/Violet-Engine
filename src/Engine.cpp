/******************************************************************/
/* Violet Engine                                                  */
/* (C) Devon Artmeier 2022                                        */
/******************************************************************/

#include "Violet.hpp"

namespace Violet {

	/// <summary>
	/// Host application
	/// </summary>
	std::shared_ptr<App> Engine::app{ nullptr };

	/// <summary>
	/// Current scene
	/// </summary>
	std::shared_ptr<Scene> Engine::scene{ nullptr };

	/// <summary>
	/// Next scene
	/// </summary>
	std::shared_ptr<Scene> Engine::nextScene{ nullptr };

	/// <summary>
	/// Start tick
	/// </summary>
	double Engine::startTick{ 0 };

	/// <summary>
	/// Run engine
	/// </summary>
	void Engine::Run() {
		try
		{
			// Initialize
			Shell::Initialize();
			Graphics::Initialize();
			Sound::Initialize();
			startTick = Shell::GetTick();
			SetVSync(GetVSync());
			EngineTimer::Start();
			Actor::InitPool();

			// Start
			DebugMessage("APPLICATION START:   " + GetAppName());
			app->OnStart();
			SetScene<StartupScene>();

			// Update loop
			bool running = true;
			while (running) {
				Input::NewFrame();

				// Update start
				if (!Shell::UpdateEvents()) {
					running = false;
				}
				EngineTimer::UpdateStart();

				// Scene start
				if (nextScene) {
					scene = nextScene;
					nextScene = nullptr;
					DebugMessage("SCENE START:         " + scene->ToString());
					scene->OnStart();
				}

				// Update
				Graphics::curLayerType = LayerType::UpdateStart;
				app->OnUpdateStart();
				scene->OnUpdateStart();

				Graphics::curLayerType = LayerType::Actor;
				Actor::Update(Actor::UpdateMode::Normal);

				Graphics::curLayerType = LayerType::UpdateEnd;
				scene->OnUpdateEnd();
				app->OnUpdateEnd();

				// Fixed update
				if (EngineTimer::fixedUpdate) {
					Graphics::curLayerType = LayerType::UpdateStart;
					app->OnFixedUpdateStart();
					scene->OnFixedUpdateStart();

					Graphics::curLayerType = LayerType::Actor;
					Actor::Update(Actor::UpdateMode::Fixed);

					Graphics::curLayerType = LayerType::UpdateEnd;
					scene->OnFixedUpdateEnd();
					app->OnFixedUpdateEnd();
				}

				// Draw update
				if (EngineTimer::drawUpdate) {
					Graphics::curLayerType = LayerType::UpdateStart;
					app->OnDrawStart();
					scene->OnDrawStart();

					Graphics::curLayerType = LayerType::Actor;
					Actor::Update(Actor::UpdateMode::Draw);

					Graphics::curLayerType = LayerType::UpdateEnd;
					scene->OnDrawEnd();
					app->OnDrawEnd();

					Shell::UpdateGraphicsStart();
					Graphics::Update();
					Graphics::DrawSprites();
					Shell::UpdateGraphicsEnd();
				}

				// Scene end
				if (nextScene) {
					DebugMessage("SCENE EXIT:          " + scene->ToString());
					scene->OnExit();
					scene = nullptr;
					Actor::DisposeAll();
				}

				// Update end
				EngineTimer::UpdateEnd();
			}
		}
		catch (const std::exception& e) {
			Message(MessageType::Error, e.what());
		}

		// Close
		try {
			Actor::DisposeAll();
			if (scene) {
				DebugMessage("SCENE EXIT:          " + scene->ToString());
				scene->OnExit();
			}
			app->OnClose();
		}
		catch (const std::exception& e) {
			Message(MessageType::Error, e.what());
		}
		DebugMessage("APPLICATION END:     " + GetAppName());
		Close();
	}


	/// <summary>
	/// Close engine
	/// </summary>
	void Engine::Close() {
		app = nullptr;
		Shell::Dispose();
		Texture::Unset();
		VertexBuffer::Unset();
		Shader::Unset();
		Graphics::Dispose();
		Sound::Dispose();
		Actor::DisposePool();
		scene = nullptr;
		nextScene = nullptr;
	}

}
