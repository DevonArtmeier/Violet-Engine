/******************************************************************/
/* Violet Engine                                                  */
/* (C) Devon Artmeier 2022                                        */
/******************************************************************/

#ifndef VIOLET_MATH_HPP
#define VIOLET_MATH_HPP

namespace Violet {

	/// <summary>
	/// Pi
	/// </summary>
	constexpr float Pi = 3.14159265359f;

	/// <summary>
	/// Math
	/// </summary>
	class Math {
	public:
		/// <summary>
		/// Get the minimum of 2 values
		/// </summary>
		/// <param name="a">Value 1</param>
		/// <param name="b">Value 2</param>
		/// <returns>The minimum of the 2 values</returns>
		template<typename T1, typename T2>
		static auto Min(T1 a, T2 b) {
			return (a > b) ? b : a;
		}

		/// <summary>
		/// Get the maximum of 2 values
		/// </summary>
		/// <param name="a">Value 1</param>
		/// <param name="b">Value 2</param>
		/// <returns>The maximum of the 2 values</returns>
		template<typename T1, typename T2>
		static auto Max(T1 a, T2 b) {
			return (a < b) ? b : a;
		}

		/// <summary>
		/// Get the absolute value of a value
		/// </summary>
		/// <param name="a">Value</param>
		/// <returns>The absolute value of the value</returns>
		template<typename T1>
		static auto Abs(T1 a) {
			if (std::is_unsigned<T1>::value) {
				return a;
			}
			else {
				return (a < 0) ? -a : a;
			}
		}

		/// <summary>
		/// Truncate a value
		/// </summary>
		/// <param name="a">Value</param>
		/// <returns>The truncated value</returns>
		template<typename T1>
		static auto Trunc(T1 a) {
			if (std::is_integral<T1>::value) {
				return a;
			}
			else if (std::is_same<T1, double>::value) {
				return static_cast<T1>(static_cast<S64>(a));
			}
			else {
				return static_cast<T1>(static_cast<int>(a));
			}
		}

		/// <summary>
		/// Round a value
		/// </summary>
		/// <param name="a">Value</param>
		/// <returns>The rounded value</returns>
		template<typename T1>
		static auto Round(T1 a) {
			if (std::is_integral<T1>::value) {
				return a;
			}
			else if (std::is_unsigned<T1>::value) {
				T1 r = Trunc(a);
				return ((a - r) >= 0.5f) ? (r + 1) : r;
			}
			else {
				T1 r = Trunc(a);
				return ((a - r) >= 0.5f) ? (r + ((a < 0) ? -1 : 1)) : r;
			}
		}

		/// <summary>
		/// Get the floor of a value
		/// </summary>
		/// <param name="a">Value</param>
		/// <returns>The floor of a value</returns>
		template<typename T1>
		static auto Floor(T1 a) {
			if (std::is_integral<T1>::value) {
				return a;
			}
			else if (std::is_unsigned<T1>::value) {
				return Trunc(a);
			}
			else {
				T1 r = Trunc(a);
				return (a < 0) ? (r - 1) : r;
			}
		}

		/// <summary>
		/// Get the ceiling of a value
		/// </summary>
		/// <param name="a">Value</param>
		/// <returns>The ceiling of a value</returns>
		template<typename T1>
		static auto Ceil(T1 a) {
			if (std::is_integral<T1>::value) {
				return a;
			}
			else if (std::is_unsigned<T1>::value) {
				return Trunc(a) + 1;
			}
			else {
				T1 r = Trunc(a);
				return (a < 0) ? r : (r + 1);
			}
		}

		/// <summary>
		/// Align a value to a floor boundary
		/// </summary>
		/// <param name="a">Value</param>
		/// <param name="b">Floor boundary</param>
		/// <returns>Aligned value</returns>
		template<typename T1, typename T2>
		static auto AlignFloor(T1 a, T2 b) {
			return Floor(a / b) * b;
		}

		/// <summary>
		/// Align a value to a ceiling boundary
		/// </summary>
		/// <param name="a">Value</param>
		/// <param name="b">Ceiling boundary</param>
		/// <returns>Aligned value</returns>
		template<typename T1, typename T2>
		static auto AlignCeil(T1 a, T2 b) {
			return Ceil(a / b) * b;
		}

		/// <summary>
		/// Convert degrees to radians
		/// </summary>
		/// <param name="d">Value in degrees</param>
		/// <returns>Value in radians</returns>
		template<typename T1>
		static auto DegToRad(T1 d) {
			return d * Pi / 180.0f;
		}

		/// <summary>
		/// Convert radians to degrees
		/// </summary>
		/// <param name="r">Value in radians</param>
		/// <returns>Value in degrees</returns>
		template<typename T1>
		static auto RadToDeg(T1 d) {
			return d * 180.0f / Pi;
		}

		/// <summary>
		/// Get the sine of a value
		/// </summary>
		/// <param name="a">Value</param>
		/// <returns>The sine of the value</returns>
		template<typename T1>
		static auto Sin(T1 a) {
			return sinf(static_cast<float>(a));
		}

		/// <summary>
		/// Get the sine of a value in degrees
		/// </summary>
		/// <param name="a">Value in degrees</param>
		/// <returns>The sine of the value</returns>
		template<typename T1>
		static auto SinDeg(T1 a) {
			return Sin(DegToRad(a));
		}

		/// <summary>
		/// Get the cosine of a value
		/// </summary>
		/// <param name="a">Value</param>
		/// <returns>The cosine of the value</returns>
		template<typename T1>
		static auto Cos(T1 a) {
			return cosf(static_cast<float>(a));
		}

		/// <summary>
		/// Get the cosine of a value in degrees
		/// </summary>
		/// <param name="a">Value in degrees</param>
		/// <returns>The cosine of the value</returns>
		template<typename T1>
		static auto CosDeg(T1 a) {
			return Cos(DegToRad(a));
		}

		/// <summary>
		/// Get ortho projection matrix
		/// </summary>
		/// <param name="l">Left</param>
		/// <param name="r">Right</param>
		/// <param name="t">Top</param>
		/// <param name="b">Bottom</param>
		/// <param name="n">Near</param>
		/// <param name="f">Far</param>
		/// <returns>Generated ortho projection matrix</returns>
		static Matrix4x4<float> GetOrthoMat(float l, float r, float t, float b, float n, float f);

		/// <summary>
		/// Get 2-dimensional translation matrix
		/// </summary>
		/// <param name="pos">Position</param>
		/// <returns>Generated matrix</returns>
		static Matrix4x4<float> Translate2DMat(Vec2D<float> pos);

		/// <summary>
		/// Get 2-dimensional scale matrix
		/// </summary>
		/// <param name="scale">Scale</param>
		/// <returns>Generated matrix</returns>
		static Matrix4x4<float> Scale2DMat(Vec2D<float> scale);

		/// <summary>
		/// Get 2-dimensional rotation matrix
		/// </summary>
		/// <param name="angle">Angle</param>
		/// <returns>Generated matrix</returns>
		static Matrix4x4<float> Rotate2DMat(float angle);

		/// <summary>
		/// Get 2-dimensional transformation matrix
		/// </summary>
		/// <param name="pos">Position</param>
		/// <param name="scale">Scale</param>
		/// <param name="angle">Angle</param>
		/// <returns>Generated matrix</returns>
		static Matrix4x4<float> Transform2DMat(Vec2D<float> pos, Vec2D<float> scale, float angle);
	};

}

#endif // VIOLET_MATH_HPP
