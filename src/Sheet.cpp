/******************************************************************/
/* Violet Engine                                                  */
/* (C) Devon Artmeier 2022                                        */
/******************************************************************/

#include "Violet.hpp"

namespace Violet {

	/// <summary>
	/// Sheet constructor
	/// </summary>
	/// <param name="fileName">File name</param>
	Sheet::Sheet(std::string fileName) {
		this->fileName = fileName;

		std::shared_ptr<BinaryFile> file = Engine::OpenBinaryFile(fileName, true);
		if (file->ReadString(7) != "VIOLSPR") {
			Engine::Error("File \"" + fileName + "\" is not a valid sprite sheet.");
		}
		U8 version = file->ReadUInt8();
		if (version != 1) {
			Engine::Error("Sprite sheet file \"" + fileName + "\" version (" + std::to_string(version) + ") is not supported.");
		}

		int count = file->ReadInt32();
		for (int i = 0; i < count; ++i) {
			frames.push_back({
				{
					file->ReadInt32(), file->ReadInt32(),
				    file->ReadInt32(), file->ReadInt32()
				},
				{
					file->ReadInt32(), file->ReadInt32()
				}
			});

			if (maxSpriteSize.w < frames[i].bounds.w) {
				maxSpriteSize.w = frames[i].bounds.w;
			}
			if (maxSpriteSize.h < frames[i].bounds.h) {
				maxSpriteSize.h = frames[i].bounds.h;
			}
		}

		Engine::DebugMessage("SHEET LOAD:          " + fileName);
	}

	/// <summary>
	/// Sheet destructor
	/// </summary>
	Sheet::~Sheet() {
		Engine::DebugMessage("SHEET DELETE:        " + fileName);
		frames.clear();
	}

	/// <summary>
	/// Draw a sprite
	/// </summary>
	/// <param name="frame">Frame ID</param>
	/// <param name="spriteParams">Sprite draw parameters</param>
	void Sheet::Draw(std::shared_ptr<Texture> texture, TextureFilter filter, const int frame, SpriteParams spriteParams) {
		Draw({ { texture, 0, filter } }, frame, spriteParams);
	}

	/// <summary>
	/// Draw a sprite
	/// </summary>
	/// <param name="textures">Textures</param>
	/// <param name="frame">Frame ID</param>
	/// <param name="spriteParams">Sprite draw parameters</param>
	void Sheet::Draw(std::initializer_list<TextureBind> textures, const int frame, SpriteParams spriteParams) {
		if (frame >= 0 && frame < frames.size()) {
			std::shared_ptr<std::vector<TextureBind>> textureBinds = std::make_shared<std::vector<TextureBind>>();
			for (int i = 0; i < textures.size(); ++i) {
				textureBinds->push_back(textures.begin()[i]);
			}

			SpriteData sprite = {
				{
					frames[frame].bounds.x,
					frames[frame].bounds.y,
					frames[frame].bounds.w,
					frames[frame].bounds.h,
				},
				spriteParams.layer,
				spriteParams.pos,
				frames[frame].origin,
				spriteParams.scale,
				spriteParams.angle,
				spriteParams.color,
				spriteParams.shader,
				spriteParams.userData };

			Graphics::AddSprite(textureBinds, sprite);
		}
	}

	/// <summary>
	/// Open sheet
	/// </summary>
	/// <param name="fileName">File name</param>
	/// <returns>Opened sheet</returns>
	std::shared_ptr<Sheet> Engine::OpenSheet(std::string fileName) {
		return std::shared_ptr<Sheet>(new Sheet(fileName));
	}

}
