/******************************************************************/
/* Violet Engine                                                  */
/* (C) Devon Artmeier 2022                                        */
/******************************************************************/

#include "Violet.hpp"

namespace Violet {

	/// <summary>
	/// Active textures
	/// </summary>
	Texture::Unit Texture::active[16] = { 0 };

	/// <summary>
	/// Draw texture as a sprite
	/// </summary>
	/// <param name="filter">Texture filter</param>
	/// <param name="bounds">Texture boundaries</param>
	/// <param name="spriteParams">Sprite draw parameters</param>
	void Texture::Draw(TextureFilter filter, SpriteParams spriteParams) {
		Draw(filter, { 0, 0, size.w, size.h }, spriteParams);
	}

	/// <summary>
	/// Draw texture as a sprite
	/// </summary>
	/// <param name="filter">Texture filter</param>
	/// <param name="bounds">Texture boundaries</param>
	/// <param name="spriteParams">Sprite draw parameters</param>
	void Texture::Draw(TextureFilter filter, Rect<float> bounds, SpriteParams spriteParams) {
		std::shared_ptr<std::vector<TextureBind>> textureBinds = std::make_shared<std::vector<TextureBind>>();
		textureBinds->push_back({ shared_from_this(), 0, filter });
		
		SpriteData sprite = {
			bounds,
			spriteParams.layer,
			spriteParams.pos,
			{ 0, 0 },
			spriteParams.scale,
			spriteParams.angle,
			spriteParams.color,
			spriteParams.shader,
			spriteParams.userData };

		Graphics::AddSprite(textureBinds, sprite);
	}

}
