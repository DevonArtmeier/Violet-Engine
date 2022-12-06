/******************************************************************/
/* Violet Engine                                                  */
/* (C) Devon Artmeier 2022                                        */
/******************************************************************/

#ifndef VIOLET_GRAPHICS_HPP
#define VIOLET_GRAPHICS_HPP

namespace Violet {

	/// <summary>
	/// View resize mode
	/// </summary>
	enum class ViewResize {
		/// <summary>
		/// Scale
		/// </summary>
		Scale = 0,

		/// <summary>
		/// Expand
		/// </summary>
		Expand
	};

	/// <summary>
	/// Sprite queue
	/// </summary>
	typedef std::shared_ptr<std::vector<SpriteData>> SpriteQueue;

	/// <summary>
	/// Sprite queue texture map
	/// </summary>
	typedef std::unordered_map<std::shared_ptr<std::vector<TextureBind>>, SpriteQueue> SpriteQueueTextureMap;

	/// <summary>
	/// Sprite queue shader map
	/// </summary>
	typedef std::unordered_map<std::shared_ptr<Shader>, SpriteQueueTextureMap> SpriteQueueShaderMap;

	/// <summary>
	/// Sprite queue texture pair
	/// </summary>
	typedef std::pair<std::shared_ptr<std::vector<TextureBind>>, SpriteQueue> SpriteQueueTexturePair;

	/// <summary>
	/// Sprite queue shader pair
	/// </summary>
	typedef std::pair<std::shared_ptr<Shader>, SpriteQueueTextureMap> SpriteQueueShaderPair;

	/// <summary>
	/// Layer count
	/// </summary>
	constexpr int LayerCount = 256;

	/// <summary>
	/// Layer type
	/// </summary>
	enum class LayerType {
		/// <summary>
		/// Update start
		/// </summary>
		UpdateStart,

		/// <summary>
		/// Map
		/// </summary>
		Map,

		/// <summary>
		/// Actor
		/// </summary>
		Actor,

		/// <summary>
		/// Update end
		/// </summary>
		UpdateEnd,

		/// <summary>
		/// Type count
		/// </summary>
		Count
	};

	/// <summary>
	/// Total layer count
	/// </summary>
	constexpr int TotalLayerCount = LayerCount * static_cast<int>(LayerType::Count);

	/// <summary>
	/// Graphics
	/// </summary>
	class Graphics {
	public:
		// Friend classes
		friend class Actor;
		friend class Engine;
		friend class Map;
		friend class Sheet;
		friend class Shell;
		friend class Texture;

		/// <summary>
		/// Set background color
		/// </summary>
		/// <param name="bgColor">Background color</param>
		static void SetBGColor(ColorRGB<float> bgColor);

		/// <summary>
		/// Set view resize mode
		/// </summary>
		/// <param name="x">Horizontal resize mode</param>
		/// <param name="y">Vertical resize mode</param>
		static void SetViewReizeMode(ViewResize x, ViewResize y);

		/// <summary>
		/// Set base view size
		/// </summary>
		/// <param name="size">Base view size</param>
		static void SetBaseViewSize(Size2D<int> size);

		/// <summary>
		/// Get view size
		/// </summary>
		/// <returns>View size</returns>
		static Size2D<int> GetViewSize();

	private:
		/// <summary>
		/// Initialize graphics
		/// </summary>
		static void Initialize();

		/// <summary>
		/// Initialize graphics API
		/// </summary>
		static void InitAPI();

		/// <summary>
		/// Dispose of graphics data
		/// </summary>
		static void Dispose();

		/// <summary>
		/// Dispose of graphics API data
		/// </summary>
		static void DisposeAPI();

		/// <summary>
		/// Update graphics
		/// </summary>
		static void Update();

		/// <summary>
		/// Add sprite for drawing
		/// </summary>
		/// <param name="textures">Sprite textures</param>
		/// <param name="sprite">Sprite data</param>
		static void AddSprite(std::shared_ptr<std::vector<TextureBind>> textures, SpriteData& sprite);

		/// <summary>
		/// Draw sprites
		/// </summary>
		static void DrawSprites();

		/// <summary>
		/// Current layer type
		/// </summary>
		static LayerType curLayerType;

		/// <summary>
		/// Background color
		/// </summary>
		static ColorRGB<float> bgColor;

		/// <summary>
		/// View size
		/// </summary>
		static Size2D<int> viewSize;

		/// <summary>
		/// Horizontal view resize mode
		/// </summary>
		static ViewResize viewResizeModeX;

		/// <summary>
		/// Vertical view resize mode
		/// </summary>
		static ViewResize viewResizeModeY;

		/// <summary>
		/// Default sprite shader
		/// </summary>
		static std::shared_ptr<SpriteShader> spriteShader;
		
		/// <summary>
		/// Sprite queue
		/// </summary>
		static std::unique_ptr<SpriteQueueShaderMap> sprites[TotalLayerCount];
	};

}

#endif // VIOLET_GRAPHICS_HPP
