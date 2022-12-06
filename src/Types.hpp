/******************************************************************/
/* Violet Engine                                                  */
/* (C) Devon Artmeier 2022                                        */
/******************************************************************/

#ifndef VIOLET_TYPES_HPP
#define VIOLET_TYPES_HPP

namespace Violet {

	/// <summary>
	/// Signed 8-bit integer
	/// </summary>
	typedef char S8;

	/// <summary>
	/// Unsigned 8-bit integer
	/// </summary>
	typedef unsigned char U8;

	/// <summary>
	/// Signed 16-bit integer
	/// </summary>
	typedef short S16;

	/// <summary>
	/// Unsigned 16-bit integer
	/// </summary>
	typedef unsigned short U16;

	/// <summary>
	/// Signed 32-bit integer
	/// </summary>
	typedef int S32;

	/// <summary>
	/// Unsigned 32-bit integer
	/// </summary>
	typedef unsigned int U32;

	/// <summary>
	/// Signed 64-bit integer
	/// </summary>
	typedef long long S64;

	/// <summary>
	/// Unsigned 64-bit integer
	/// </summary>
	typedef unsigned long long U64;

#ifdef VIOLET_64_BIT
	/// <summary>
	/// Pointer
	/// </summary>
	typedef U64 Ptr;
#else
	/// <summary>
	/// Pointer
	/// </summary>
	typedef U32 Ptr;
#endif

	/// <summary>
	/// Texture filter
	/// </summary>
	enum class TextureFilter {
		Nearest = 0,
		Bilinear
	};

	/// <summary>
	/// Texture wrap modes
	/// </summary>
	enum class TextureWrap {
		Repeat = 0,
		Mirror,
		Clamp
	};

	/// <summary>
	/// 1-dimensional vector
	/// </summary>
	template <typename T>
	struct Vec1D {
		/// <summary>
		/// 2-dimensional vector constructor
		/// </summary>
		Vec1D() {
			this->x = 0;
		}

		/// <summary>
		/// 1-dimensional vector constructor
		/// </summary>
		/// <param name="x">X coordinate</param>
		template<typename TX>
		Vec1D(TX x) {
			this->x = static_cast<T>(x);
		}

		/// <summary>
		/// X coordinate
		/// </summary>
		T x;
	};

	/// <summary>
	/// 2-dimensional vector
	/// </summary>
	template <typename T>
	struct Vec2D {
		/// <summary>
		/// 2-dimensional vector constructor
		/// </summary>
		Vec2D() {
			this->x = 0;
			this->y = 0;
		}

		/// <summary>
		/// 2-dimensional vector constructor
		/// </summary>
		/// <param name="x">X coordinate</param>
		/// <param name="y">Y coordinate</param>
		template<typename TX, typename TY>
		Vec2D(TX x, TY y) {
			this->x = static_cast<T>(x);
			this->y = static_cast<T>(y);
		}

		/// <summary>
		/// X coordinate
		/// </summary>
		T x;

		/// <summary>
		/// Y coordinate
		/// </summary>
		T y;
	};

	/// <summary>
	/// 3-dimensional vector
	/// </summary>
	template <typename T>
	struct Vec3D {
		/// <summary>
		/// 3-dimensional vector constructor
		/// </summary>
		Vec3D() {
			this->x = 0;
			this->y = 0;
			this->z = 0;
		}

		/// <summary>
		/// 3-dimensional vector constructor
		/// </summary>
		/// <param name="x">X coordinate</param>
		/// <param name="y">Y coordinate</param>
		/// <param name="z">Z coordinate</param>
		template<typename TX, typename TY, typename TZ>
		Vec3D(TX x, TY y, TZ z) {
			this->x = static_cast<T>(x);
			this->y = static_cast<T>(y);
			this->z = static_cast<T>(z);
		}

		/// <summary>
		/// X coordinate
		/// </summary>
		T x;

		/// <summary>
		/// Y coordinate
		/// </summary>
		T y;

		/// <summary>
		/// Z coordinate
		/// </summary>
		T z;
	};

	/// <summary>
	/// 4-dimensional vector
	/// </summary>
	template <typename T>
	struct Vec4D {
		/// <summary>
		/// 4-dimensional vector constructor
		/// </summary>
		Vec4D() {
			this->x = 0;
			this->y = 0;
			this->z = 0;
			this->w = 0;
		}

		/// <summary>
		/// 4-dimensional vector constructor
		/// </summary>
		/// <param name="x">X coordinate</param>
		/// <param name="y">Y coordinate</param>
		/// <param name="z">Z coordinate</param>
		/// <param name="w">W coordinate</param>
		template<typename TX, typename TY, typename TZ, typename TW>
		Vec4D(TX x, TY y, TZ z, TW w) {
			this->x = static_cast<T>(x);
			this->y = static_cast<T>(y);
			this->z = static_cast<T>(z);
			this->w = static_cast<T>(w);
		}

		/// <summary>
		/// X coordinate
		/// </summary>
		T x;

		/// <summary>
		/// Y coordinate
		/// </summary>
		T y;

		/// <summary>
		/// Z coordinate
		/// </summary>
		T z;

		/// <summary>
		/// W coordinate
		/// </summary>
		T w;
	};

	/// <summary>
	/// 2-dimensional size
	/// </summary>
	template <typename T>
	struct Size2D {
		/// <summary>
		/// 2-dimensional size constructor
		/// </summary>
		Size2D() {
			this->w = 0;
			this->h = 0;
		}

		/// <summary>
		/// 2-dimensional size constructor
		/// </summary>
		/// <param name="w">Width</param>
		/// <param name="h">Height</param>
		template<typename TW, typename TH>
		Size2D(TW w, TH h) {
			this->w = static_cast<T>(w);
			this->h = static_cast<T>(h);
		}

		/// <summary>
		/// Width
		/// </summary>
		T w;

		/// <summary>
		/// Height
		/// </summary>
		T h;
	};

	/// <summary>
	/// 3-dimensional size
	/// </summary>
	template <typename T>
	struct Size3D {
		/// <summary>
		/// 3-dimensional size constructor
		/// </summary>
		Size3D() {
			this->w = 0;
			this->h = 0;
			this->d = 0;
		}
		/// <summary>
		/// 3-dimensional size constructor
		/// </summary>
		/// <param name="w">Width</param>
		/// <param name="h">Height</param>
		/// <param name="d">Depth</param>
		template<typename TW, typename TH, typename TD>
		Size3D(TW w, TH h, TD d) {
			this->w = static_cast<T>(w);
			this->h = static_cast<T>(h);
			this->d = static_cast<T>(d);
		}

		/// <summary>
		/// Width
		/// </summary>
		T w;

		/// <summary>
		/// Height
		/// </summary>
		T h;

		/// <summary>
		/// Depth
		/// </summary>
		T d;
	};

	/// <summary>
	/// Rectangle
	/// </summary>
	template <typename T>
	struct Rect {
		/// <summary>
		/// Rectangle constructor
		/// </summary>
		Rect() {
			this->x = 0;
			this->y = 0;
			this->w = 0;
			this->h = 0;
		}

		/// <summary>
		/// Rectangle constructor
		/// </summary>
		/// <param name="x">X coordinate</param>
		/// <param name="y">Y coordinate</param>
		/// <param name="w">Width</param>
		/// <param name="h">Height</param>
		template<typename TX, typename TY, typename TW, typename TH>
		Rect(TX x, TY y, TW w, TH h) {
			this->x = static_cast<T>(x);
			this->y = static_cast<T>(y);
			this->w = static_cast<T>(w);
			this->h = static_cast<T>(h);
		}

		/// <summary>
		/// X coordinate
		/// </summary>
		T x;

		/// <summary>
		/// Y coordinate
		/// </summary>
		T y;

		/// <summary>
		/// Width
		/// </summary>
		T w;

		/// <summary>
		/// Height
		/// </summary>
		T h;
	};

	/// <summary>
	/// RGB color
	/// </summary>
	template <typename T>
	struct ColorRGB {
		/// <summary>
		/// RGB color constructor
		/// </summary>
		ColorRGB() {
			this->r = 0;
			this->g = 0;
			this->b = 0;
		}

		/// <summary>
		/// RGB color constructor
		/// </summary>
		/// <param name="r">Red</param>
		/// <param name="g">Green</param>
		/// <param name="b">Blue</param>
		template<typename TR, typename TG, typename TB>
		ColorRGB(TR r, TG g, TB b) {
			this->r = static_cast<T>(r);
			this->g = static_cast<T>(g);
			this->b = static_cast<T>(b);
		}

		/// <summary>
		/// Red
		/// </summary>
		T r;

		/// <summary>
		/// Green
		/// </summary>
		T g;

		/// <summary>
		/// Blue
		/// </summary>
		T b;
	};

	/// <summary>
	/// RGBA color
	/// </summary>
	template <typename T>
	struct ColorRGBA {
		/// <summary>
		/// RGBA color constructor
		/// </summary>
		ColorRGBA() {
			this->r = 0;
			this->g = 0;
			this->b = 0;
			this->a = 0;
		}

		/// <summary>
		/// RGBA color constructor
		/// </summary>
		/// <param name="r">Red</param>
		/// <param name="g">Green</param>
		/// <param name="b">Blue</param>
		/// <param name="a">Alpha</param>
		template<typename TR, typename TG, typename TB, typename TA>
		ColorRGBA(TR r, TG g, TB b, TA a) {
			this->r = static_cast<T>(r);
			this->g = static_cast<T>(g);
			this->b = static_cast<T>(b);
			this->a = static_cast<T>(a);
		}

		/// <summary>
		/// Red
		/// </summary>
		T r;

		/// <summary>
		/// Green
		/// </summary>
		T g;

		/// <summary>
		/// Blue
		/// </summary>
		T b;

		/// <summary>
		/// Alpha
		/// </summary>
		T a;
	};

	/// <summary>
	/// 1-dimensional vector matrix
	/// </summary>
	template <typename T>
	using Matrix2x2 = glm::mat<2, 2, T, glm::packed_highp>;

	/// <summary>
	/// 2x2 matrix
	/// </summary>
	template <typename T>
	using Matrix2x2 = glm::mat<2, 2, T, glm::packed_highp>;

	/// <summary>
	/// 3x3 matrix
	/// </summary>
	template <typename T>
	using Matrix3x3 = glm::mat<3, 3, T, glm::packed_highp>;

	/// <summary>
	/// 4x4 matrix
	/// </summary>
	template <typename T>
	using Matrix4x4 = glm::mat<4, 4, T, glm::packed_highp>;

	/// <summary>
	/// 2x3 matrix
	/// </summary>
	template <typename T>
	using Matrix2x3 = glm::mat<2, 3, T, glm::packed_highp>;

	/// <summary>
	/// 3x2 matrix
	/// </summary>
	template <typename T>
	using Matrix3x2 = glm::mat<3, 2, T, glm::packed_highp>;

	/// <summary>
	/// 2x4 matrix
	/// </summary>
	template <typename T>
	using Matrix2x4 = glm::mat<2, 4, T, glm::packed_highp>;

	/// <summary>
	/// 4x2 matrix
	/// </summary>
	template <typename T>
	using Matrix4x2 = glm::mat<4, 2, T, glm::packed_highp>;

	/// <summary>
	/// 2x4 matrix
	/// </summary>
	template <typename T>
	using Matrix3x4 = glm::mat<3, 4, T, glm::packed_highp>;

	/// <summary>
	/// 4x2 matrix
	/// </summary>
	template <typename T>
	using Matrix4x3 = glm::mat<4, 3, T, glm::packed_highp>;

}

#endif // VIOLET_TYPES_HPP 
