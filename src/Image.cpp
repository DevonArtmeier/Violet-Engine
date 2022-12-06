/******************************************************************/
/* Violet Engine                                                  */
/* (C) Devon Artmeier 2022                                        */
/******************************************************************/

#include "Violet.hpp"
#include <png.h>

namespace Violet {

	/// <summary>
	/// Image constructor
	/// </summary>
	/// <param name="fileName">File name</param>
	Image::Image(std::string fileName) {
		this->fileName = fileName;

		if (!OpenPNG()) {
			Engine::Error("\"" + fileName + "\" is not a valid image file");
		}
	}

	/// <summary>
	/// Image destructor
	/// </summary>
	Image::~Image() {
		Engine::DebugMessage("IMAGE DELETE:        " + fileName);
		if (pixels) {
			delete[] pixels;
		}
	}

	/// <summary>
	/// Get pixel data
	/// </summary>
	/// <returns>Pixel data</returns>
	std::shared_ptr<ColorRGBA<float>[]> Image::GetPixels() {
		return std::shared_ptr<ColorRGBA<float>[]>(pixels);
	}

	/// <summary>
	/// Get image size
	/// </summary>
	/// <returns>Image size</returns>
	Size2D<int> Image::GetSize() {
		return size;
	}

	/// <summary>
	/// Open a PNG file
	/// </summary>
	/// <param name="fileName">File name</param>
	/// <returns>True if successful, false if not</returns>
	bool Image::OpenPNG() {
		FILE* fp = nullptr;
		png_bytep* rowPointers = nullptr;

		// Open file
		fopen_s(&fp, fileName.c_str(), "rb");
		if (!fp) {
			Engine::Error("Failed to open \"" + fileName + "\"");
			return false;
		}

		// Get PNG info
		png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
		if (!png) {
			fclose(fp);
			Engine::Error("Error creating PNG read structure for file \"" + fileName + "\"");
			return false;
		}
		png_infop info = png_create_info_struct(png);
		if (!info) {
			fclose(fp);
			png_destroy_read_struct(&png, nullptr, nullptr);
			return false;
		}
		if (setjmp(png_jmpbuf(png))) {
			if (rowPointers) {
				for (int y = 0; y < size.h; ++y) {
					if (rowPointers[y]) {
						delete[] rowPointers[y];
					}
				}
				delete[] rowPointers;
			}
			fclose(fp);
			png_destroy_read_struct(&png, &info, nullptr);
			Engine::Error("Error reading PNG file \"" + fileName + "\"");
			return false;
		}

		png_init_io(png, fp);
		png_read_info(png, info);
		size = { static_cast<int>(png_get_image_width(png, info)), static_cast<int>(png_get_image_height(png, info)) };
		png_byte colorType = png_get_color_type(png, info);
		png_byte bitDepth = png_get_bit_depth(png, info);

		// Convert to 8-bit RGBA
		if (bitDepth == 16) {
			png_set_strip_16(png);
		}
		if (colorType == PNG_COLOR_TYPE_PALETTE) {
			png_set_palette_to_rgb(png);
		}
		if (colorType == PNG_COLOR_TYPE_GRAY && bitDepth < 8) {
			png_set_expand_gray_1_2_4_to_8(png);
		}
		if (png_get_valid(png, info, PNG_INFO_tRNS)) {
			png_set_tRNS_to_alpha(png);
		}
		if (colorType == PNG_COLOR_TYPE_RGB ||
			colorType == PNG_COLOR_TYPE_GRAY ||
			colorType == PNG_COLOR_TYPE_PALETTE) {
			png_set_filler(png, 0xFF, PNG_FILLER_AFTER);
		}
		if (colorType == PNG_COLOR_TYPE_GRAY ||
			colorType == PNG_COLOR_TYPE_GRAY_ALPHA) {
			png_set_gray_to_rgb(png);
		}
		png_read_update_info(png, info);

		// Read pixel data
		rowPointers = new png_bytep[sizeof(png_bytep) * size.h];
		for (int y = 0; y < size.h; ++y) {
			rowPointers[y] = new png_byte[png_get_rowbytes(png, info)];
		}
		png_read_image(png, rowPointers);

		// Convert to floats and clean up
		pixels = new ColorRGBA<float>[size.w * size.h];
		int i = 0;
		for (int y = 0; y < size.h; ++y) {
			png_bytep row = rowPointers[y];
			for (int x = 0; x < size.w; ++x) {
				pixels[i++] = {
					(*(row++)) / 255.0f,
					(*(row++)) / 255.0f,
					(*(row++)) / 255.0f,
					(*(row++)) / 255.0f
				};
			}
			delete[] rowPointers[y];
		}
		delete[] rowPointers;
		fclose(fp);
		png_destroy_read_struct(&png, &info, nullptr);

		Engine::DebugMessage("IMAGE LOAD (PNG):    " + fileName);
		return true;
	}

	/// <summary>
	/// Open image
	/// </summary>
	/// <param name="fileName">File name</param>
	/// <returns>Opened image</returns>
	std::shared_ptr<Image> Engine::OpenImage(std::string fileName) {
		return std::shared_ptr<Image>(new Image(fileName));
	}

}
