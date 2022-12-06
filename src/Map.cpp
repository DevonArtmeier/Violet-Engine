/******************************************************************/
/* Violet Engine                                                  */
/* (C) Devon Artmeier 2022                                        */
/******************************************************************/

#include "Violet.hpp"

namespace Violet {

	/// <summary>
	/// Map constructor
	/// </summary>
	/// <param name="fileName">File name</param>
	Map::Map(std::string fileName) {
		this->fileName = fileName;

		std::shared_ptr<BinaryFile> file = Engine::OpenBinaryFile(fileName, true);
		if (file->ReadString(7) != "VIOLMAP") {
			Engine::Error("File \"" + fileName + "\" is not a valid map.");
		}
		U8 version = file->ReadUInt8();
		if (version != 1) {
			Engine::Error("Map file \"" + fileName + "\" version (" + std::to_string(version) + ") is not supported.");
		}

		mapSize.w = file->ReadUInt16();
		mapSize.h = file->ReadUInt16();
		gridSize.w = file->ReadUInt16();
		gridSize.h = file->ReadUInt16();

		int layerCount = file->ReadUInt8();
		for (int i = 0; i < layerCount; ++i) {
			int layerID = file->ReadUInt8();
			layers[layerID].tiles = new Tile[mapSize.w * mapSize.h];

			int j = 0;
			for (int y = 0; y < mapSize.h; ++y) {
				for (int x = 0; x < mapSize.w; ++x) {
					int id = file->ReadUInt16();
					int sheet = file->ReadUInt8();
					int flags = file->ReadUInt8();

					layers[layerID].tiles[j++] = {
						id,
						sheet,
						(flags & 16) != 0,
						(flags & 4) != 0,
						(flags & 8) != 0,
						static_cast<Tile::Rotate>(flags & 3)
					};
				}
			}
		}

		Engine::DebugMessage("MAP LOAD:            " + fileName);
	}

	/// <summary>
	/// Map destructor
	/// </summary>
	Map::~Map() {
		Engine::DebugMessage("MAP DELETE:          " + fileName);
		for (int i = 0; i < LayerCount; ++i) {
			if (layers[i].tiles) {
				delete layers[i].tiles;
			}
		}
	}

	/// <summary>
	/// Set texture for map
	/// </summary>
	/// <param name="id">Texture ID</param>
	/// <param name="texture">Texture data</param>
	void Map::SetTexture(int id, std::shared_ptr<Texture> texture) {
		textures[id] = texture;
	}

	/// <summary>
	/// Set sheet for map
	/// </summary>
	/// <param name="id">Sheet ID</param>
	/// <param name="sheet">Sheet data</param>
	void Map::SetSheet(int id, std::shared_ptr<Sheet> sheet) {
		sheets[id] = sheet;
	}

	/// <summary>
	/// Set scroll X position
	/// </summary>
	/// <param name="layer">Layer</param>
	/// <param name="x">Scroll X position</param>
	void Map::SetScrollX(int layer, float x) {
		if (layer >= 0 && layer < LayerCount) {
			layers[layer].scroll.x = x;
		}
	}

	/// <summary>
	/// Set scroll Y position
	/// </summary>
	/// <param name="layer">Layer</param>
	/// <param name="y">Scroll Y position</param>
	void Map::SetScrollY(int layer, float y) {
		if (layer >= 0 && layer < LayerCount) {
			layers[layer].scroll.y = y;
		}
	}

	/// <summary>
	/// Set scroll position
	/// </summary>
	/// <param name="layer">Layer</param>
	/// <param name="pos">Scroll position</param>
	void Map::SetScroll(int layer, Vec2D<float> pos) {
		if (layer >= 0 && layer < LayerCount) {
			layers[layer].scroll = pos;
		}
	}

	/// <summary>
	/// Add to scroll X position
	/// </summary>
	/// <param name="layer">Layer</param>
	/// <param name="x">Scroll X offset</param>
	void Map::AddScrollX(int layer, float x) {
		if (layer >= 0 && layer < LayerCount) {
			layers[layer].scroll.x += x;
		}
	}

	/// <summary>
	/// Add to scroll Y position
	/// </summary>
	/// <param name="layer">Layer</param>
	/// <param name="y">Scroll Y offset</param>
	void Map::AddScrollY(int layer, float y) {
		if (layer >= 0 && layer < LayerCount) {
			layers[layer].scroll.y += y;
		}
	}

	/// <summary>
	/// Add to scroll position
	/// </summary>
	/// <param name="layer">Layer</param>
	/// <param name="offset">Scroll offset</param>
	void Map::AddScroll(int layer, Vec2D<float> offset) {
		if (layer >= 0 && layer < LayerCount) {
			layers[layer].scroll.x += offset.x;
			layers[layer].scroll.y += offset.y;
		}
	}

	/// <summary>
	/// Draw map
	/// </summary>
	void Map::Draw() {
		LayerType layerType = Graphics::curLayerType;
		Graphics::curLayerType = LayerType::Map;

		Size2D<int> viewSize = Graphics::GetViewSize();
		
		// Make sure that the largest tile remains drawn, even if partially offscreen
		float drawBackX = 0;
		float drawBackY = 0;
		int mapBackX = 0;
		int mapBackY = 0;

		Size2D<float> maxSpriteSize = { 0, 0 };
		for (std::pair<int, std::shared_ptr<Sheet>> sheet : sheets) {
			if (maxSpriteSize.w > sheet.second->maxSpriteSize.w) {
				maxSpriteSize.w = sheet.second->maxSpriteSize.w;
			}
			if (maxSpriteSize.h > sheet.second->maxSpriteSize.h) {
				maxSpriteSize.h = sheet.second->maxSpriteSize.h;
			}
		}
		if (maxSpriteSize.w > gridSize.w) {
			drawBackX = Math::Ceil(maxSpriteSize.w / gridSize.w) * gridSize.w;
			mapBackX = static_cast<int>(drawBackX / gridSize.w);
		}
		if (maxSpriteSize.h > gridSize.h) {
			drawBackY = Math::AlignCeil(maxSpriteSize.h, gridSize.h);
			mapBackY = static_cast<int>(drawBackY / gridSize.h);
		}

		for (int i = 0; i < LayerCount; ++i) {
			if (layers[i].tiles) {
				int initMapX = static_cast<int>(Math::Floor(layers[i].scroll.x / gridSize.w)) - mapBackX;
				float initDrawX = (Math::Floor(layers[i].scroll.x / gridSize.w) * gridSize.w) - layers[i].scroll.x - drawBackX;

				int mapY = static_cast<int>(Math::Floor(layers[i].scroll.y / gridSize.h)) - mapBackY;
				float drawY = (Math::Floor(layers[i].scroll.y / gridSize.h) * gridSize.h) - layers[i].scroll.y - drawBackY;

				while (drawY < viewSize.h) {
					int mapX = initMapX;
					float drawX = initDrawX;

					while (drawX < viewSize.w) {
						if (mapX >= 0 && mapX < mapSize.w && mapY >= 0 && mapY < mapSize.h) {
							Tile tile = layers[i].tiles[mapX + (mapY * mapSize.w)];

							if (!tile.invisible && textures.find(tile.sheet) != textures.end() && sheets.find(tile.sheet) != sheets.end()) {
								std::shared_ptr<Sheet> sheet = sheets[tile.sheet];
								sheet->Draw(textures[tile.sheet], TextureFilter::Nearest, tile.id,
									SpriteParams(i,
										{
											drawX + sheet->frames[tile.id].origin.x,
											drawY + sheet->frames[tile.id].origin.y
										}
								));
							}
						}
						++mapX;
						drawX += gridSize.w;
					}

					++mapY;
					drawY += gridSize.h;
				}
			}
		}

		Graphics::curLayerType = layerType;
	}

	/// <summary>
	/// Load map
	/// </summary>
	/// <param name="fileName">File name</param>
	std::shared_ptr<Map> Engine::OpenMap(std::string fileName) {
		return std::shared_ptr<Map>(new Map(fileName));
	}

}
