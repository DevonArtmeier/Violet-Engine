/******************************************************************/
/* Violet Engine                                                  */
/* (C) Devon Artmeier 2022                                        */
/******************************************************************/

#ifndef VIOLET_IMAGE_HPP
#define VIOLET_IMAGE_HPP

namespace Violet {

	/// <summary>
	/// Image
	/// </summary>
	class Image {
	public:
		/// <summary>
		/// Image destructor
		/// </summary>
		~Image();

		/// <summary>
		/// Get pixel data
		/// </summary>
		/// <returns>Pixel data</returns>
		std::shared_ptr<ColorRGBA<float>[]> GetPixels();

		/// <summary>
		/// Get image size
		/// </summary>
		/// <returns>Image size</returns>
		Size2D<int> GetSize();

		// Friend classes
		friend class Engine;
		friend class Texture;

	private:
		/// <summary>
		/// Image constructor
		/// </summary>
		/// <param name="fileName">File name</param>
		Image(std::string fileName);

		/// <summary>
		/// Open a PNG file
		/// </summary>
		/// <returns>True if successful, false if not</returns>
		bool OpenPNG();

		/// <summary>
		/// File name
		/// </summary>
		std::string fileName{ "" };

		/// <summary>
		/// Pixel data
		/// </summary>
		ColorRGBA<float>* pixels{ nullptr };

		/// <summary>
		/// Image size
		/// </summary>
		Size2D<int> size;
	};

}

#endif /* VIOLET_IMAGE_HPP */
