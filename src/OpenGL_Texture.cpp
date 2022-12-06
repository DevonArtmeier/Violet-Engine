/******************************************************************/
/* Violet Engine                                                  */
/* (C) Devon Artmeier 2022                                        */
/******************************************************************/

#include "Violet.hpp"

namespace Violet {

	/// <summary>
	/// Texture constructor
	/// </summary>
	/// <param name="fileName">File name</param>
	/// <param name="wrap">Wrap mode</param>
	Texture::Texture(std::string fileName, TextureWrap wrap) {
		this->fileName = fileName;
		std::shared_ptr<Image> image = Engine::OpenImage(fileName);

		GLuint ids[2];
		glGenTextures(2, ids);
		this->idBilinear = static_cast<Ptr>(ids[0]);
		this->idNearest = static_cast<Ptr>(ids[1]);

		int glWrap;
		switch (wrap) {
		default:
		case TextureWrap::Repeat:
			glWrap = GL_REPEAT;
			break;
		case TextureWrap::Mirror:
			glWrap = GL_MIRRORED_REPEAT;
			break;
		case TextureWrap::Clamp:
			glWrap = GL_CLAMP_TO_EDGE;
			break;
		}

		SetActive(TextureFilter::Bilinear);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, glWrap);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, glWrap);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->size.w, image->size.h, 0, GL_RGBA, GL_FLOAT, (const void*)(image->pixels));
		glGenerateMipmap(GL_TEXTURE_2D);

		SetActive(TextureFilter::Nearest);
		glBindTexture(GL_TEXTURE_2D, ids[1]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, glWrap);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, glWrap);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->size.w, image->size.h, 0, GL_RGBA, GL_FLOAT, (const void*)(image->pixels));
		glGenerateMipmap(GL_TEXTURE_2D);

		size = image->size;

		Engine::DebugMessage("IMAGE -> TEXTURE:    " + fileName);
	}

	/// <summary>
	/// Texture destructor
	/// </summary>
	Texture::~Texture() {
		Engine::DebugMessage("TEXTURE DELETE:      " + fileName);

		GLuint ids[2] = {
			static_cast<GLuint>(this->idBilinear),
			static_cast<GLuint>(this->idNearest)
		};
		glDeleteTextures(2, ids);
	}

	/// <summary>
	/// Get texture size
	/// </summary>
	/// <returns>Texture size</returns>
	Size2D<int> Texture::GetSize() {
		return size;
	}

	/// <summary>
	/// Set active
	/// </summary>
	/// <param name="wrap">Filter</param>
	/// <param name="unit">Unit ID</param>
	void Texture::SetActive(TextureFilter filter, int unit) {
		if (active[unit].texture != this || active[unit].filter != filter) {
			glActiveTexture(GL_TEXTURE0 + unit);
			switch (filter) {
			case TextureFilter::Bilinear:
				glBindTexture(GL_TEXTURE_2D, static_cast<GLuint>(idBilinear));
				break;
			case TextureFilter::Nearest:
				glBindTexture(GL_TEXTURE_2D, static_cast<GLuint>(idNearest));
				break;
			}

			active[unit].texture = this;
			active[unit].filter = filter;
		}
	}

	/// <summary>
	/// Unset texture
	/// </summary>
	/// <param name="unit">Unit to unset</param>
	void Texture::Unset(int unit) {
		if (active[unit].texture) {
			glActiveTexture(GL_TEXTURE0 + unit);
			glBindTexture(GL_TEXTURE_2D, 0);
			active[unit].texture = nullptr;
		}
	}

	/// <summary>
	/// Unset textures
	/// </summary>
	void Texture::Unset() {
		for (int i = 0; i < 16; ++i) {
			Unset(i);
		}
	}

	/// <summary>
	/// Open texture
	/// </summary>
	/// <param name="fileName">File name</param>
	/// <param name="wrap">Wrap mode</param>
	/// <returns>Opened texture</returns>
	std::shared_ptr<Texture> Engine::OpenTexture(std::string fileName, TextureWrap wrap) {
		return std::shared_ptr<Texture>(new Texture(fileName, wrap));
	}

}
