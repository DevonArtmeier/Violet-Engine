#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "App.hpp"

class TestActor : public Actor {
public:
	/// <summary>
	/// Get string representation of test actor
	/// </summary>
	/// <returns>String representation of test actor</returns>
	std::string ToString() {
		return "Test Actor";
	}

private:
	/// <summary>
	/// On spawn event
	/// </summary>
	void OnSpawn() {

	}

	/// <summary>
	/// On update event
	/// </summary>
	void OnUpdate() {

	}

	/// <summary>
	/// On fixed update event
	/// </summary>
	void OnFixedUpdate() {

	}

	/// <summary>
	/// On draw event
	/// </summary>
	void OnDraw() {

	}

	/// <summary>
	/// On dispose event
	/// </summary>
	void OnDispose() {

	}
};

/// <summary>
/// On start event
/// </summary>
void TestApp::OnStart() {
	Graphics::SetBGColor({ 0.0f, 144 / 255.0f, 252 / 255.0f });

	ghzBGTexture = Engine::OpenTexture("Data/GHZ.png");
	texture = Engine::OpenTexture("Data/Sprite1.png");
	texture2 = Engine::OpenTexture("Data/Sprite2.png");
	mapTexture = Engine::OpenTexture("Data/Map.png");

	ghzBGSheet = Engine::OpenSheet("Data/GHZ.spr");
	sprSheet = Engine::OpenSheet("Data/Sprite.spr");
	mapSheet = Engine::OpenSheet("Data/Map.spr");

	map = Engine::OpenMap("Data/Map.map");
	map->SetTexture(0, mapTexture);
	map->SetSheet(0, mapSheet);

	Actor::Spawn<TestActor>();
	Sound::PlayMusic("Data/HappyWhenItRains.ogg", true);
}

/// <summary>
/// On update start event
/// </summary>
void TestApp::OnUpdateStart() {
	if (Input::CheckButtonPress(Button::Left)) {
		map->AddScrollX(0, -1 * Engine::GetUpdateDelta());
	}
	else if (Input::CheckButtonPress(Button::Right)) {
		map->AddScrollX(0, 1 * Engine::GetUpdateDelta());
	}

	if (Input::CheckButtonPress(Button::Up)) {
		map->AddScrollY(0, -1 * Engine::GetUpdateDelta());
	}
	else if (Input::CheckButtonPress(Button::Down)) {
		map->AddScrollY(0, 1 * Engine::GetUpdateDelta());
	}
}

/// <summary>
/// On update end event
/// </summary>
void TestApp::OnUpdateEnd() {

}

/// <summary>
/// On fixed update start event
/// </summary>
void TestApp::OnFixedUpdateStart() {
	Engine::SetWindowTitle(Engine::GetAppName() + " - " +
		"Game: " + std::to_string(static_cast<int>(Math::Round(Engine::GetGameFPS()))) + " FPS | " +
		"Update: " + std::to_string(static_cast<int>(Math::Round(Engine::GetUpdateFPS()))) + " FPS | " +
		"Draw: " + std::to_string(static_cast<int>(Math::Round(Engine::GetDrawFPS()))) + " FPS");
}

/// <summary>
/// On fixed update end event
/// </summary>
void TestApp::OnFixedUpdateEnd() {

}

/// <summary>
/// On draw start event
/// </summary>
void TestApp::OnDrawStart() {
	Size2D<int> viewSize = Graphics::GetViewSize();

	static float clouds1X = 0;
	static float clouds2X = 0;
	static float clouds3X = 0;
	static float cameraBG = 0;
	float cameraBG1 = 0.375f * cameraBG;
	float cameraBG2 = 0.5f * cameraBG;

	int y = 0;
	Rect<int> test = { clouds1X + cameraBG1, y, viewSize.w, 32 };

	map->Draw();

	// Clouds
	ghzBGTexture->Draw(TextureFilter::Nearest, { clouds1X + cameraBG1, y, viewSize.w, 32 }, SpriteParams(0, { 0, y }));
	y += 32;
	ghzBGTexture->Draw(TextureFilter::Nearest, { clouds2X + cameraBG1, y, viewSize.w, 16 }, SpriteParams(0, { 0, y }));
	y += 16;
	ghzBGTexture->Draw(TextureFilter::Nearest, { clouds3X + cameraBG1, y, viewSize.w, 16 }, SpriteParams(0, { 0, y }));

	// Mountains
	y += 16;
	ghzBGTexture->Draw(TextureFilter::Nearest, { cameraBG1, y, viewSize.w, 48 }, SpriteParams(0, { 0, y }));

	// Hills and waterfalls
	y += 48;
	ghzBGTexture->Draw(TextureFilter::Nearest, { cameraBG2, y, viewSize.w, 40 }, SpriteParams(0, { 0, y }));

	// Water
	float x = cameraBG2;
	float xDelta = (cameraBG2 - cameraBG) / 104;
	for (float y2 = 152; y2 < ghzBGTexture->GetSize().h; ++y2) {
		ghzBGTexture->Draw(TextureFilter::Nearest, { x, y2, viewSize.w, 1 }, SpriteParams(0, { 0, y2 }));
		x -= xDelta;
	}

	cameraBG += 2 * Engine::GetDrawUpdateDelta();
	clouds1X += 1 * Engine::GetDrawUpdateDelta();
	clouds2X += 0.75f * Engine::GetDrawUpdateDelta();
	clouds3X += 0.5f * Engine::GetDrawUpdateDelta();

	static float angle = 0;
	float intensity = 32 + (((Math::SinDeg(angle * 7) + 1) / 2) * 32);

	static ColorRGBA<float> colors[] =
	{
		{ 1, 0, 0, 0.75 },
		{ 1, 0.5, 0, 0.75 },
		{ 1, 1, 0, 0.75 },
		{ 0, 1, 0, 0.75 },
		{ 0, 1, 1, 0.75 },
		{ 0, 0, 1, 0.75 },
		{ 0.5, 0, 1, 0.75 },
		{ 1, 0, 1, 0.75 },
	};

	float count = 8;
	for (float i = 0; i < count; ++i) {
		std::shared_ptr<Texture> tex = ((((int)i) & 1) == 0) ? texture : texture2;

		sprSheet->Draw(tex, TextureFilter::Bilinear, 0, SpriteParams(1,
			{
				(viewSize.w / 2) + (Math::CosDeg((angle + ((i / count) * 360)) * 3) * intensity),
				(viewSize.h / 2) + (Math::SinDeg((angle + ((i / count) * 360)) * 2) * intensity)
			},
			{ 0.33, 0.33 }, angle + 90 + ((i / count) * 360), colors[static_cast<int>(i)]));
	}
	angle += Engine::GetDrawUpdateDelta();
}

/// <summary>
/// On draw end event
/// </summary>
void TestApp::OnDrawEnd() {

}

/// <summary>
/// On close event
/// </summary>
void TestApp::OnClose() {

}

/// <summary>
/// Main function
/// </summary>
int main() {
	{
		std::make_shared<TestApp>()->Run();
	}

	if (_CrtDumpMemoryLeaks()) {
		printf("Memory leaks!\n");
	}

	return 0;
}