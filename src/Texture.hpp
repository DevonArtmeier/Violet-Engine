/******************************************************************/
/* Violet Engine                                                  */
/* (C) Devon Artmeier 2022                                        */
/******************************************************************/

#ifndef VIOLET_TEXTURE_HPP
#define VIOLET_TEXTURE_HPP

namespace Violet {

	/// <summary>
	/// Texture
	/// </summary>
	class Texture : public std::enable_shared_from_this<Texture> {
	public:
		// Friend classes
		friend class Engine;
		friend class Graphics;

		/// <summary>
		/// Texture destructor
		/// </summary>
		~Texture();

		/// <summary>
		/// Get texture size
		/// </summary>
		/// <returns>Texture size</returns>
		Size2D<int> GetSize();

		/// <summary>
		/// Draw texture as a sprite
		/// </summary>
		/// <param name="filter">Texture filter</param>
		/// <param name="bounds">Texture boundaries</param>
		/// <param name="spriteParams">Sprite draw parameters</param>
		void Draw(TextureFilter filter, SpriteParams spriteParams);

		/// <summary>
		/// Draw texture as a sprite
		/// </summary>
		/// <param name="filter">Texture filter</param>
		/// <param name="bounds">Texture boundaries</param>
		/// <param name="spriteParams">Sprite draw parameters</param>
		void Draw(TextureFilter filter, Rect<float> bounds, SpriteParams spriteParams);

	private:
		/// <summary>
		/// Texture unit
		/// </summary>
		struct Unit {
			/// <summary>
			/// Texture
			/// </summary>
			Texture* texture;

			/// <summary>
			/// Filter
			/// </summary>
			TextureFilter filter;
		};

		/// <summary>
		/// Texture constructor
		/// </summary>
		/// <param name="fileName">File name</param>
		/// <param name="wrap">Wrap mode</param>
		Texture(std::string fileName, TextureWrap wrap);

		/// <summary>
		/// Set active
		/// </summary>
		/// <param name="wrap">Filter</param>
		/// <param name="unit">Unit ID</param>
		void SetActive(TextureFilter filter, int unit = 0);

		/// <summary>
		/// Unset texture
		/// </summary>
		/// <param name="unit">Unit to unset</param>
		static void Unset(int unit);

		/// <summary>
		/// Unset textures
		/// </summary>
		static void Unset();

		/// <summary>
		/// Bilinear texture ID
		/// </summary>
		Ptr idBilinear{ 0 };

		/// <summary>
		/// Nearest neighbor texture ID
		/// </summary>
		Ptr idNearest{ 0 };

		/// <summary>
		/// File name
		/// </summary>
		std::string fileName{ "" };

		/// <summary>
		/// Texture size
		/// </summary>
		Size2D<int> size;

		/// <summary>
		/// Active textures
		/// </summary>
		static Unit active[16];

	};

}

#endif /* VIOLET_TEXTURE_HPP */
