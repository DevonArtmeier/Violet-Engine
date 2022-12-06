/******************************************************************/
/* Violet Engine                                                  */
/* (C) Devon Artmeier 2022                                        */
/******************************************************************/

#include "Violet.hpp"

namespace Violet {

	/// <summary>
	/// Current layer type
	/// </summary>
	LayerType Graphics::curLayerType{ LayerType::UpdateStart };

	/// <summary>
	/// Background color
	/// </summary>
	ColorRGB<float> Graphics::bgColor{ ColorRGB<float>(0.0f, 0.0f, 0.0f) };

	/// <summary>
	/// View size
	/// </summary>
	Size2D<int> Graphics::viewSize{ Size2D<int>(448, 256) };

	/// <summary>
	/// Horizontal view resize mode
	/// </summary>
	ViewResize Graphics::viewResizeModeX{ ViewResize::Expand };

	/// <summary>
	/// Vertical view resize mode
	/// </summary>
	ViewResize Graphics::viewResizeModeY{ ViewResize::Scale };

	/// <summary>
	/// Default sprite shader
	/// </summary>
	std::shared_ptr<SpriteShader> Graphics::spriteShader{ nullptr };

	/// <summary>
	/// Sprite queue
	/// </summary>
	std::unique_ptr<SpriteQueueShaderMap> Graphics::sprites[TotalLayerCount];

	/// <summary>
	/// Initialize graphics manager
	/// </summary>
	void Graphics::Initialize() {
		for (int i = 0; i < TotalLayerCount; ++i) {
			sprites[i] = std::make_unique<SpriteQueueShaderMap>();
		}
		spriteShader = std::shared_ptr<SpriteShader>(new SpriteShader());
		InitAPI();
	}

	/// <summary>
	/// Dispose of graphics data
	/// </summary>
	void Graphics::Dispose() {
		DisposeAPI();
		for (int i = 0; i < TotalLayerCount; ++i) {
			sprites[i]->clear();
			sprites[i] = nullptr;
		}
		spriteShader = nullptr;
	}

	/// <summary>
	/// Add sprite for drawing
	/// </summary>
	/// <param name="textures">Sprite textures</param>
	/// <param name="sprite">Sprite data</param>
	void Graphics::AddSprite(std::shared_ptr<std::vector<TextureBind>> textures, SpriteData& sprite) {
		// Get layer
		int layer = (sprite.layer * static_cast<int>(LayerType::Count)) + static_cast<int>(curLayerType);

		// Get sprite maps for this shader
		if (!sprite.shader) {
			sprite.shader = spriteShader;
		}
		if (sprites[layer]->find(sprite.shader) == sprites[layer]->end()) {
			sprites[layer]->insert_or_assign(sprite.shader, SpriteQueueTextureMap());
		}
		SpriteQueueTextureMap spriteMaps = sprites[layer]->at(sprite.shader);

		// Find sprite map for this particular binding of textures
		for (SpriteQueueTexturePair spriteMap : spriteMaps) {
			int foundCount = 0;

			for (int i = 0; i < textures->size(); ++i) {
				TextureBind spriteBind = textures->begin()[i];
				bool found = false;

				for (int j = 0; j < spriteMap.first->size(); ++j) {
					TextureBind mapBind = spriteMap.first->at(j);
					if (spriteBind.texture == mapBind.texture &&
						spriteBind.unit == mapBind.unit &&
						spriteBind.filter == mapBind.filter) {
						++foundCount;
						found = true;
						break;
					}
				}

				if (!found && spriteBind.texture == nullptr) {
					++foundCount;
				}
			}

			if (foundCount == Math::Max(textures->size(), spriteMap.first->size())) {
				spriteMaps[spriteMap.first]->push_back(sprite);
				sprites[layer]->insert_or_assign(sprite.shader, spriteMaps);
				return;
			}
		}

		// Create new sprite map for this binding of textures
		spriteMaps[textures] = std::make_shared<std::vector<SpriteData>>();
		spriteMaps[textures]->push_back(sprite);
		sprites[layer]->insert_or_assign(sprite.shader, spriteMaps);

	}

	/// <summary>
	/// Draw sprites
	/// </summary>
	void Graphics::DrawSprites() {
		// Iterate through each layer
		for (int layer = 0; layer < TotalLayerCount; ++layer) {
			// Iterate through each shader
			for (SpriteQueueShaderPair spriteMaps : *(sprites[layer])) {
				std::shared_ptr<Shader> shader = spriteMaps.first;
				shader->SetActive();

				// Iterate through each texture binding
				for (SpriteQueueTexturePair spriteMap : spriteMaps.second) {
					// Unset unused units
					for (int i = 0; i < 16; ++i) {
						bool found = false;
						for (int j = 0; j < spriteMap.first->size(); ++j) {
							if (spriteMap.first->at(j).unit == i) {
								found = true;
								break;
							}
							if (!found) {
								Texture::Unset(i);
							}
						}
					}

					// Set active units
					for (int i = 0; i < spriteMap.first->size(); ++i) {
						TextureBind bind = spriteMap.first->at(i);
						bind.texture->SetActive(bind.filter, bind.unit);
					}

					// Draw sprites
					shader->StartSpriteDraw();
					for (int i = 0; i < spriteMap.second->size(); ++i) {
						shader->AddSprite(spriteMap.first, spriteMap.second->at(i));
					}
					shader->FlushSprites();
					spriteMap.second->clear();
				}

				spriteMaps.second.clear();
			}
			sprites[layer]->clear();
		}
	}

	/// <summary>
	/// Set background color
	/// </summary>
	/// <param name="bgColor">Background color</param>
	void Graphics::SetBGColor(ColorRGB<float> bgColor) {
		bgColor = bgColor;
	}

	/// <summary>
	/// Set view resize mode
	/// </summary>
	/// <param name="x">Horizontal resize mode</param>
	/// <param name="y">Vertical resize mode</param>
	void Graphics::SetViewReizeMode(ViewResize x, ViewResize y) {
		viewResizeModeX = x;
		viewResizeModeY = y;
	}

	/// <summary>
	/// Set base view size
	/// </summary>
	/// <param name="size">Base view size</param>
	void Graphics::SetBaseViewSize(Size2D<int> size) {
		viewSize = size;
	}

	/// <summary>
	/// Get view size
	/// </summary>
	/// <returns>View size</returns>
	Size2D<int> Graphics::GetViewSize() {
		Size2D<int> winSize = Shell::GetWindowSize();
		Size2D<int> outViewSize;

		switch (viewResizeModeX) {
		case ViewResize::Scale:
		default:
			outViewSize.w = viewSize.w;
			break;

		case ViewResize::Expand:
			if (viewResizeModeY == ViewResize::Expand) {
				outViewSize.w = winSize.w;
			}
			else {
				outViewSize.w = static_cast<int>(viewSize.h * (static_cast<float>(winSize.w) / winSize.h));
			}
			break;
		}

		switch (viewResizeModeY) {
		case ViewResize::Scale:
		default:
			outViewSize.h = viewSize.h;
			break;

		case ViewResize::Expand:
			if (viewResizeModeX == ViewResize::Expand) {
				outViewSize.h = winSize.h;
			}
			else {
				outViewSize.h = static_cast<int>(viewSize.w * (static_cast<float>(winSize.h) / winSize.w));
			}
			break;
		}

		return outViewSize;
	}

}