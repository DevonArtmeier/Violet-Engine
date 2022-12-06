/******************************************************************/
/* Violet Engine                                                  */
/* (C) Devon Artmeier 2022                                        */
/******************************************************************/

#ifndef VIOLET_MAP_HPP
#define VIOLET_MAP_HPP

namespace Violet {

	/// <summary>
	/// Map
	/// </summary>
	class Map {
	public:
		/// <summary>
		/// Map destructor
		/// </summary>
		virtual ~Map();

		/// <summary>
		/// Set texture for map
		/// </summary>
		/// <param name="id">Texture ID</param>
		/// <param name="texture">Texture data</param>
		void SetTexture(int id, std::shared_ptr<Texture> texture);

		/// <summary>
		/// Set sheet for map
		/// </summary>
		/// <param name="id">Sheet ID</param>
		/// <param name="sheet">Sheet data</param>
		void SetSheet(int id, std::shared_ptr<Sheet> sheet);

		/// <summary>
		/// Set scroll X position
		/// </summary>
		/// <param name="layer">Layer</param>
		/// <param name="x">Scroll X position</param>
		void SetScrollX(int layer, float x);

		/// <summary>
		/// Set scroll Y position
		/// </summary>
		/// <param name="layer">Layer</param>
		/// <param name="y">Scroll Y position</param>
		void SetScrollY(int layer, float y);

		/// <summary>
		/// Set scroll position
		/// </summary>
		/// <param name="layer">Layer</param>
		/// <param name="pos">Scroll position</param>
		void SetScroll(int layer, Vec2D<float> pos);

		/// <summary>
		/// Add to scroll X position
		/// </summary>
		/// <param name="layer">Layer</param>
		/// <param name="x">Scroll X offset</param>
		void AddScrollX(int layer, float x);

		/// <summary>
		/// Add to scroll Y position
		/// </summary>
		/// <param name="layer">Layer</param>
		/// <param name="y">Scroll Y offset</param>
		void AddScrollY(int layer, float y);

		/// <summary>
		/// Add to scroll position
		/// </summary>
		/// <param name="layer">Layer</param>
		/// <param name="offset">Scroll offset</param>
		void AddScroll(int layer, Vec2D<float> offset);

		/// <summary>
		/// Draw map
		/// </summary>
		void Draw();

		// Friend classes
		friend class Engine;
		friend class GraphicsManager;

	private:
		/// <summary>
		/// Tile
		/// </summary>
		struct Tile {
			/// <summary>
			/// Rotation mode
			/// </summary>
			enum class Rotate {
				None = 0,

				/// <summary>
				/// 90 degrees
				/// </summary>
				Deg90,

				/// <summary>
				/// 180 degrees
				/// </summary>
				Deg180,

				/// <summary>
				/// 270 degrees
				/// </summary>
				Deg270
			};

			/// <summary>
			/// Tile ID
			/// </summary>
			int id{ 0 };

			/// <summary>
			/// Sheet ID
			/// </summary>
			int sheet{ 0 };

			/// <summary>
			/// invisible flag
			/// </summary>
			bool invisible{ false };

			/// <summary>
			/// X flip
			/// </summary>
			bool flipX{ false };

			/// <summary>
			/// Y flip
			/// </summary>
			bool flipY{ false };

			/// <summary>
			/// Rotation
			/// </summary>
			Rotate rotate{ Rotate::None };
		};

		/// <summary>
		/// Layer
		/// </summary>
		struct Layer {
			/// <summary>
			/// Scroll offset
			/// </summary>
			Vec2D<float> scroll{ Vec2D<float>(0, 0) };

			/// <summary>
			/// Tile data
			/// </summary>
			Tile* tiles{ nullptr };
		};

		/// <summary>
		/// Map constructor
		/// </summary>
		/// <param name="fileName">File name</param>
		Map(std::string fileName);

		/// <summary>
		/// File name
		/// </summary>
		std::string fileName{ "" };

		/// <summary>
		/// Layers
		/// </summary>
		Layer layers[LayerCount];

		/// <summary>
		/// Textures
		/// </summary>
		std::unordered_map<int, std::shared_ptr<Texture>> textures;

		/// <summary>
		/// Sheets
		/// </summary>
		std::unordered_map<int, std::shared_ptr<Sheet>> sheets;

		/// <summary>
		/// Map size
		/// </summary>
		Size2D<int> mapSize = { 0, 0 };

		/// <summary>
		/// Grid size
		/// </summary>
		Size2D<int> gridSize = { 0, 0 };
	};

}

#endif // VIOLET_MAP_HPP
