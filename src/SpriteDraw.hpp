/******************************************************************/
/* Violet Engine                                                  */
/* (C) Devon Artmeier 2022                                        */
/******************************************************************/

#ifndef VIOLET_SPRITE_DRAW_HPP
#define VIOLET_SPRITE_DRAW_HPP

namespace Violet {

	/// <summary>
	/// Texture bind
	/// </summary>
	struct TextureBind {
		/// <summary>
		/// Texture
		/// </summary>
		std::shared_ptr<Texture> texture;

		/// <summary>
		/// Texture unit
		/// </summary>
		int unit;

		/// <summary>
		/// Texture filter
		/// </summary>
		TextureFilter filter;
	};

	/// <summary>
	/// Sprite draw params
	/// </summary>
	struct SpriteParams {
		/// <summary>
		/// Sprite draw parameters constructor
		/// </summary>
		/// <param name="layer">Layer</param>
		/// <param name="pos">Position</param>
		SpriteParams(int layer, Vec2D<float> pos) {
			this->layer = layer;
			this->pos = pos;
			this->scale = { 1.0f, 1.0f };
			this->angle = 0;
			this->color = { 1.0f, 1.0f, 1.0f, 1.0f };
			this->shader = nullptr;
			this->userData = nullptr;
		}

		/// <summary>
		/// Sprite draw parameters constructor
		/// </summary>
		/// <param name="layer">Layer</param>
		/// <param name="pos">Position</param>
		/// <param name="scale">Scale</param>
		/// <param name="angle">Angle</param>
		SpriteParams(int layer, Vec2D<float> pos, Vec2D<float> scale, float angle) {
			this->layer = layer;
			this->pos = pos;
			this->scale = scale;
			this->angle = angle;
			this->color = { 1.0f, 1.0f, 1.0f, 1.0f };
			this->shader = nullptr;
			this->userData = nullptr;
		}

		/// <summary>
		/// Sprite draw parameters constructor
		/// </summary>
		/// <param name="layer">Layer</param>
		/// <param name="pos">Position</param>
		/// <param name="scale">Scale</param>
		/// <param name="angle">Angle</param>
		/// <param name="alpha">Alpha</param>
		SpriteParams(int layer, Vec2D<float> pos, Vec2D<float> scale, float angle, float alpha) {
			this->layer = layer;
			this->pos = pos;
			this->scale = scale;
			this->angle = angle;
			this->color = { 1, 1, 1, alpha };
			this->shader = nullptr;
			this->userData = nullptr;
		}

		/// <summary>
		/// Sprite draw parameters constructor
		/// </summary>
		/// <param name="texture">Texture</param>
		/// <param name="filter">Texture filter</param>
		/// <param name="layer">Layer</param>
		/// <param name="pos">Position</param>
		/// <param name="scale">Scale</param>
		/// <param name="angle">Angle</param>
		/// <param name="color">Color</param>
		SpriteParams(int layer, Vec2D<float> pos, Vec2D<float> scale, float angle, ColorRGBA<float> color) {
			this->layer = layer;
			this->pos = pos;
			this->scale = scale;
			this->angle = angle;
			this->color = color;
			this->shader = nullptr;
			this->userData = nullptr;
		}

		/// <summary>
		/// Sprite draw parameters constructor
		/// </summary>
		/// <param name="texture">Texture</param>
		/// <param name="filter">Texture filter</param>
		/// <param name="layer">Layer</param>
		/// <param name="pos">Position</param>
		/// <param name="scale">Scale</param>
		/// <param name="angle">Angle</param>
		/// <param name="color">Color</param>
		/// <param name="shader">Shader</param>
		/// <param name="userData">Shader user data</param>
		SpriteParams(int layer, Vec2D<float> pos, Vec2D<float> scale, float angle, ColorRGBA<float> color, std::shared_ptr<Shader> shader, void* userData) {
			this->layer = layer;
			this->pos = pos;
			this->scale = scale;
			this->angle = angle;
			this->color = color;
			this->shader = shader;
			this->userData = userData;
		}

		/// <summary>
		/// Layer
		/// </summary>
		int layer;

		/// <summary>
		/// Position
		/// </summary>
		Vec2D<float> pos;

		/// <summary>
		/// Scale
		/// </summary>
		Vec2D<float> scale;

		/// <summary>
		/// Angle
		/// </summary>
		float angle;

		/// <summary>
		/// Color
		/// </summary>
		ColorRGBA<float> color;

		/// <summary>
		/// Shader
		/// </summary>
		std::shared_ptr<Shader> shader;

		/// <summary>
		/// Shader user data
		/// </summary>
		void* userData;
	};

	/// <summary>
	/// Sprite data
	/// </summary>
	struct SpriteData {
		/// <summary>
		/// Texture boundaries
		/// </summary>
		Rect<float> bounds;

		/// <summary>
		/// Layer
		/// </summary>
		int layer;

		/// <summary>
		/// Position
		/// </summary>
		Vec2D<float> pos;

		/// <summary>
		/// Origin
		/// </summary>
		Vec2D<float> origin;

		/// <summary>
		/// Scale
		/// </summary>
		Vec2D<float> scale;

		/// <summary>
		/// Angle
		/// </summary>
		float angle;

		/// <summary>
		/// Color
		/// </summary>
		ColorRGBA<float> color;

		/// <summary>
		/// Shader
		/// </summary>
		std::shared_ptr<Shader> shader;

		/// <summary>
		/// Shader user data
		/// </summary>
		void* userData;
	};

}

#endif // VIOLET_SPRITE_DRAW_HPP
