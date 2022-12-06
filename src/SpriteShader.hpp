/******************************************************************/
/* Violet Engine                                                  */
/* (C) Devon Artmeier 2022                                        */
/******************************************************************/

#ifndef VIOLET_SPRITE_SHADER_HPP
#define VIOLET_SPRITE_SHADER_HPP

namespace Violet {

	/// <summary>
	/// Number of sprites that the vertex buffer can hold
	/// </summary>
	constexpr auto SpriteBufCount = 1024;

	/// <summary>
	/// Sprite shader
	/// </summary>
	class SpriteShader : public Shader {
	public:
		// Friend classes
		friend class Graphics;

		// <summary>
		/// Start sprite draw
		/// </summary>
		void StartSpriteDraw();

		/// <summary>
		/// Add sprite draw data
		/// </summary>
		/// <param name="textures">Sprite textures</param>
		/// <param name="sprite">Sprite data</param>
		void AddSprite(std::shared_ptr<std::vector<TextureBind>> textures, SpriteData& sprite);

		/// <summary>
		/// Flush sprites
		/// </summary>
		void FlushSprites();

	private:
		/// <summary>
		/// Sprite shader constructor
		/// </summary>
		SpriteShader();

		/// <summary>
		/// Get sprite shader vertex shader code
		/// </summary>
		/// <returns>Sprite shader vertex shader code</returns>
		static const char* GetVertexShader();

		/// <summary>
		/// Get sprite shader fragment shader code
		/// </summary>
		/// <returns>Sprite shader fragment shader code</returns>
		static const char* GetFragmentShader();

		// Vertex count
		int vertexCount{ 0 };
	};

}

#endif // VIOLET_SPRITE_SHADER_HPP
