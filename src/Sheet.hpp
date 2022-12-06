/******************************************************************/
/* Violet Engine                                                  */
/* (C) Devon Artmeier 2022                                        */
/******************************************************************/

#ifndef VIOLET_SHEET_HPP
#define VIOLET_SHEET_HPP

namespace Violet {

	/// <summary>
	/// Sheet
	/// </summary>
	class Sheet {
	public:
		/// <summary>
		/// Sheet destructor
		/// </summary>
		~Sheet();

		/// <summary>
		/// Draw a sprite
		/// </summary>
		/// <param name="texture">Texture</param>
		/// <param name="filter">Texture filter</param>
		/// <param name="frame">Frame ID</param>
		/// <param name="spriteParams">Sprite draw parameters</param>
		void Draw(std::shared_ptr<Texture> texture, TextureFilter filter, const int frame, SpriteParams spriteParams);

		/// <summary>
		/// Draw a sprite
		/// </summary>
		/// <param name="textures">Textures</param>
		/// <param name="frame">Frame ID</param>
		/// <param name="spriteParams">Sprite draw parameters</param>
		void Draw(std::initializer_list<TextureBind> textures, const int frame, SpriteParams spriteParams);

		// Friend classes
		friend class Engine;
		friend class Map;

	private:
		/// <summary>
		/// Sheet constructor
		/// </summary>
		/// <param name="fileName">File name</param>
		Sheet(std::string fileName);

		/// <summary>
		/// Sprite frame
		/// </summary>
		struct Frame {
			// Boundaries in texture
			Rect<float> bounds;
			// Origin point
			Vec2D<float> origin;
		};

		/// <summary>
		/// File name
		/// </summary>
		std::string fileName{ "" };

		/// <summary>
		/// Sprite frames
		/// </summary>
		std::vector<Frame> frames;

		/// <summary>
		/// Max sprite size
		/// </summary>
		Size2D<float> maxSpriteSize{ Size2D<float>(0, 0) };
	};

}

#endif // VIOLET_SHEET_HPP
