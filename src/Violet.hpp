/******************************************************************/
/* Violet Engine                                                  */
/* (C) Devon Artmeier 2022                                        */
/******************************************************************/

#ifndef VIOLET_HPP
#define VIOLET_HPP

namespace Violet {
	/// <summary>
	/// Actor
	/// </summary>
	class Actor;

	/// <summary>
	/// Application
	/// </summary>
	class App;

	/// <summary>
	/// Binary file
	/// </summary>
	class BinaryFile;

	/// <summary>
	/// Engine
	/// </summary>
	class Engine;

	/// <summary>
	/// Engine timer
	/// </summary>
	class EngineTimer;

	/// <summary>
	/// Graphics
	/// </summary>
	class Graphics;

	/// <summary>
	/// Map
	/// </summary>
	class Map;

	/// <summary>
	/// Scene
	/// </summary>
	class Scene;

	/// <summary>
	/// Shader
	/// </summary>
	class Shader;

	/// <summary>
	/// Shell
	/// </summary>
	class Shell;

	/// <summary>
	/// Sound
	/// </summary>
	class Sound;

	/// <summary>
	/// Sound source
	/// </summary>
	class SoundSource;

	/// <summary>
	/// Sheet
	/// </summary>
	class Sheet;

	/// <summary>
	/// Sprite shader
	/// </summary>
	class SpriteShader;

	/// <summary>
	/// Timer
	/// </summary>
	class Timer;

	/// <summary>
	/// Vertex buffer
	/// </summary>
	class VertexBuffer;
}

#ifdef VIOLET_SHELL_SDL2
#include <SDL.h>
#endif
#ifdef VIOLET_GRAPHICS_OPENGL
#include <glad/glad.h>
#endif
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <cstdio>
#include <initializer_list>
#include <memory>
#include <string>
#include <sstream>
#include <stdexcept>
#include <type_traits>
#include <unordered_map>
#include <vector>

#include "Types.hpp"
#include "Math.hpp"
#include "Message.hpp"
#include "BinaryFile.hpp"
#include "Timer.hpp"
#include "Input.hpp"
#include "Image.hpp"
#include "SpriteDraw.hpp"
#include "Texture.hpp"
#include "VertexBuffer.hpp"
#include "Shader.hpp"
#include "SpriteShader.hpp"
#include "Sheet.hpp"
#include "Graphics.hpp"
#include "SoundSource.hpp"
#include "SoundSourceOgg.hpp"
#include "Sound.hpp"
#include "Map.hpp"
#include "Actor.hpp"
#include "App.hpp"
#include "Shell.hpp"
#include "EngineTimer.hpp"
#include "Scene.hpp"
#include "Engine.hpp"

#endif // VIOLET_HPP
