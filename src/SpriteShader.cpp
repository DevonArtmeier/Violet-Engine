/******************************************************************/
/* Violet Engine                                                  */
/* (C) Devon Artmeier 2022                                        */
/******************************************************************/

#include "Violet.hpp"

namespace Violet {

	/// <summary>
	/// Sprite vertex data
	/// </summary>
	struct SpriteVertex {
		Vec2D<float> pos;
		ColorRGBA<float> color;
		Vec2D<float> texCoord;
	};

	/// <summary>
	/// Sprite shader constructor
	/// </summary>
	SpriteShader::SpriteShader() : Shader(sizeof(SpriteVertex), SpriteBufCount * 6, GetVertexShader(), GetFragmentShader()) {
		vertexBuffer->AddAttribute(VertexBuffer::AttribType::Float, 2);
		vertexBuffer->AddAttribute(VertexBuffer::AttribType::Float, 4);
		vertexBuffer->AddAttribute(VertexBuffer::AttribType::Float, 2);

		AddVariable("projection");
	}

	/// <summary>
	/// Start sprite draw
	/// </summary>
	void SpriteShader::StartSpriteDraw() {
		SetMatrix4x4("projection", Engine::GetDefaultOrthoMat());
	}

	/// <summary>
	/// Add sprite draw data
	/// </summary>
	/// <param name="textures">Sprite textures</param>
	/// <param name="sprite">Sprite data</param>
	void SpriteShader::AddSprite(std::shared_ptr<std::vector<TextureBind>> textures, SpriteData& sprite) {
		float texWidth = 1;
		float texHeight = 1;
		for (int i = 0; i < textures->size(); ++i) {
			if (textures->at(i).unit == 0) {
				Size2D<int> size = textures->at(i).texture->GetSize();
				texWidth = static_cast<float>(size.w);
				texHeight = static_cast<float>(size.h);
			}
		}

		SpriteVertex* vertexData = (SpriteVertex*)(vertexBuffer->GetDataBuffer()) + vertexCount;

		Matrix4x4<float> transformMat = Math::Transform2DMat(sprite.pos, sprite.scale, sprite.angle);
		glm::vec4 posTransform0 = transformMat * glm::vec4(-sprite.origin.x, -sprite.origin.y, 0, 1);
		glm::vec4 posTransform1 = transformMat * glm::vec4(-sprite.origin.x, -sprite.origin.y + sprite.bounds.h, 0, 1);
		glm::vec4 posTransform2 = transformMat * glm::vec4(-sprite.origin.x + sprite.bounds.w, -sprite.origin.y, 0, 1);
		glm::vec4 posTransform3 = transformMat * glm::vec4(-sprite.origin.x + sprite.bounds.w, -sprite.origin.y + sprite.bounds.h, 0, 1);

		vertexData[0].pos = { posTransform0.x, posTransform0.y };
		vertexData[0].color = sprite.color;
		vertexData[0].texCoord = {
			static_cast<float>(sprite.bounds.x / texWidth),
			static_cast<float>(sprite.bounds.y / texHeight)
		};

		vertexData[1].pos = { posTransform1.x, posTransform1.y };
		vertexData[1].color = sprite.color;
		vertexData[1].texCoord = {
			static_cast<float>(sprite.bounds.x / texWidth),
			static_cast<float>((sprite.bounds.y + sprite.bounds.h) / texHeight)
		};

		vertexData[2].pos = { posTransform2.x, posTransform2.y };
		vertexData[2].color = sprite.color;
		vertexData[2].texCoord = {
			static_cast<float>((sprite.bounds.x + sprite.bounds.w) / texWidth),
			static_cast<float>(sprite.bounds.y / texHeight)
		};

		vertexData[4].pos = { posTransform3.x, posTransform3.y };
		vertexData[4].color = sprite.color;
		vertexData[4].texCoord = {
			static_cast<float>((sprite.bounds.x + sprite.bounds.w) / texWidth),
			static_cast<float>((sprite.bounds.y + sprite.bounds.h) / texHeight)
		};

		vertexData[3] = vertexData[1];
		vertexData[5] = vertexData[2];

		vertexCount += 6;
		if (vertexCount >= SpriteBufCount * 6) {
			FlushSprites();
		}
	}

	/// <summary>
	/// Flush sprites
	/// </summary>
	void SpriteShader::FlushSprites() {
		if (vertexCount) {
			vertexBuffer->SetActive();
			vertexBuffer->RefreshData();
			vertexBuffer->Draw(vertexCount);
			vertexCount = 0;
		}
	}

}
