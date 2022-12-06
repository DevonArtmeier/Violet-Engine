#ifndef VIOLET_TEST_APP_HPP
#define VIOLET_TEST_APP_HPP

#include <Violet.hpp>
using namespace Violet;

/// <summary>
/// Test application
/// </summary>
class TestApp : public App {
public:
	/// <summary>
	/// Application constructor
	/// </summary>
	TestApp() : App("Test Application") { }

private:
	/// <summary>
	/// On start event
	/// </summary>
	void OnStart();

	/// <summary>
	/// On update start event
	/// </summary>
	void OnUpdateStart();

	/// <summary>
	/// On update end event
	/// </summary>
	void OnUpdateEnd();

	/// <summary>
	/// On fixed update start event
	/// </summary>
	void OnFixedUpdateStart();

	/// <summary>
	/// On fixed update end event
	/// </summary>
	void OnFixedUpdateEnd();

	/// <summary>
	/// On draw start event
	/// </summary>
	void OnDrawStart();

	/// <summary>
	/// On draw end event
	/// </summary>
	void OnDrawEnd();

	/// <summary>
	/// On close event
	/// </summary>
	void OnClose();

	/// <summary>
	/// GHZ background sheet
	/// </summary>
	std::shared_ptr<Sheet> ghzBGSheet{ nullptr };

	/// <summary>
	/// Sprite sheet
	/// </summary>
	std::shared_ptr<Sheet> sprSheet{ nullptr };

	/// <summary>
	/// Map sheet
	/// </summary>
	std::shared_ptr<Sheet> mapSheet{ nullptr };

	/// <summary>
	/// GHZ background texture
	/// </summary>
	std::shared_ptr<Texture> ghzBGTexture{ nullptr };

	/// <summary>
	/// Sprite texture
	/// </summary>
	std::shared_ptr<Texture> texture{ nullptr };

	/// <summary>
	/// Sprite texture 2
	/// </summary>
	std::shared_ptr<Texture> texture2{ nullptr };

	/// <summary>
	/// Map texture
	/// </summary>
	std::shared_ptr<Texture> mapTexture{ nullptr };

	/// <summary>
	/// Map
	/// </summary>
	std::shared_ptr<Map> map{ nullptr };

};

#endif // VIOLET_TEST_APP_HPP
