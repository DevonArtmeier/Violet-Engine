/******************************************************************/
/* Violet Engine                                                  */
/* (C) Devon Artmeier 2022                                        */
/******************************************************************/

#ifndef VIOLET_SHADER_HPP
#define VIOLET_SHADER_HPP

namespace Violet {

	/// <summary>
	/// Shader
	/// </summary>
	class Shader {
	public:
		// Friend classes
		friend class Engine;
		friend class Graphics;

		/// <summary>
		/// Shader constructor
		/// </summary>
		/// <param name="vertexSize">Size of vertex</param>
		/// <param name="vertexCount">Vertex count</param>
		/// <param name="vertexCode">Vertex shader code</param>
		/// <param name="fragCode">Fragment shader code</param>
		Shader(const int vertexSize, const int vertexCount, std::string vertexCode = "", std::string fragCode = "");

		/// <summary>
		/// Shader destructor
		/// </summary>
		virtual ~Shader();

		/// <summary>
		/// Get ID
		/// </summary>
		/// <returns>Shader ID</returns>
		Ptr GetID() const;

		/// <summary>
		/// Set active
		/// </summary>
		void SetActive();

		/// <summary>
		/// Add variable
		/// </summary>
		/// <param name="name">Variable name</param>
		void AddVariable(std::string name);

		/// <summary>
		/// Set float
		/// </summary>
		/// <param name="name">Name of variable</param>
		/// <param name="val">Value to set</param>
		void SetFloat(std::string name, float val);

		/// <summary>
		/// Set signed integer
		/// </summary>
		/// <param name="name">Name of variable</param>
		/// <param name="val">Value to set</param>
		void SetInt(std::string name, S32 val);

		/// <summary>
		/// Set unsigned integer
		/// </summary>
		/// <param name="name">Name of variable</param>
		/// <param name="val">Value to set</param>
		void SetUInt(std::string name, U32 val);

		/// <summary>
		/// Set 1-dimensional vector
		/// </summary>
		/// <param name="name">Name of variable</param>
		/// <param name="vec">Vector to set</param>
		void SetVec1(std::string name, Vec1D<float> vec);

		/// <summary>
		/// Set 2-dimensional vector
		/// </summary>
		/// <param name="name">Name of variable</param>
		/// <param name="vec">Vector to set</param>
		void SetVec2(std::string name, Vec2D<float> vec);

		/// <summary>
		/// Set 3-dimensional vector
		/// </summary>
		/// <param name="name">Name of variable</param>
		/// <param name="vec">Vector to set</param>
		void SetVec3(std::string name,Vec3D<float> vec);

		/// <summary>
		/// Set 4-dimensional vector
		/// </summary>
		/// <param name="name">Name of variable</param>
		/// <param name="vec">Vector to set</param>
		void SetVec4(std::string name, Vec4D<float> vec);

		/// <summary>
		/// Set 1-dimensional signed integer vector
		/// </summary>
		/// <param name="name">Name of variable</param>
		/// <param name="vec">Vector to set</param>
		void SetIntVec1(std::string name, Vec1D<S32> vec);

		/// <summary>
		/// Set 2-dimensional signed integer vector
		/// </summary>
		/// <param name="name">Name of variable</param>
		/// <param name="vec">Vector to set</param>
		void SetIntVec2(std::string name, Vec2D<S32> vec);

		/// <summary>
		/// Set 3-dimensional signed integer vector
		/// </summary>
		/// <param name="name">Name of variable</param>
		/// <param name="vec">Vector to set</param>
		void SetIntVec3(std::string name, Vec3D<S32> vec);

		/// <summary>
		/// Set 4-dimensional signed integer vector
		/// </summary>
		/// <param name="name">Name of variable</param>
		/// <param name="vec">Vector to set</param>
		void SetIntVec4(std::string name, Vec4D<S32> vec);

		/// <summary>
		/// Set 1-dimensional unsigned integer vector
		/// </summary>
		/// <param name="name">Name of variable</param>
		/// <param name="vec">Vector to set</param>
		void SetUIntVec1(std::string name, Vec1D<U32> vec);

		/// <summary>
		/// Set 2-dimensional unsigned integer vector
		/// </summary>
		/// <param name="name">Name of variable</param>
		/// <param name="vec">Vector to set</param>
		void SetUIntVec2(std::string name, Vec2D<U32> vec);

		/// <summary>
		/// Set 3-dimensional unsigned integer vector
		/// </summary>
		/// <param name="name">Name of variable</param>
		/// <param name="vec">Vector to set</param>
		void SetUIntVec3(std::string name, Vec3D<U32> vec);

		/// <summary>
		/// Set 4-dimensional unsigned integer vector
		/// </summary>
		/// <param name="name">Name of variable</param>
		/// <param name="vec">Vector to set</param>
		void SetUIntVec4(std::string name, Vec4D<U32> vec);

		/// <summary>
		/// Set floats
		/// </summary>
		/// <param name="name">Name of variable</param>
		/// <param name="val">Values to set</param>
		void SetFloats(std::string name, std::initializer_list<float> val);

		/// <summary>
		/// Set signed integers
		/// </summary>
		/// <param name="name">Name of variable</param>
		/// <param name="val">Values to set</param>
		void SetInts(std::string name, std::initializer_list<S32> val);

		/// <summary>
		/// Set unsigned integers
		/// </summary>
		/// <param name="name">Name of variable</param>
		/// <param name="val">Values to set</param>
		void SetUInts(std::string name, std::initializer_list<U32> val);

		/// <summary>
		/// Set 1-dimensional vectors
		/// </summary>
		/// <param name="name">Name of variable</param>
		/// <param name="vec">Vectors to set</param>
		void SetVec1s(std::string name, std::initializer_list<Vec1D<float>> vec);

		/// <summary>
		/// Set 2-dimensional vectors
		/// </summary>
		/// <param name="name">Name of variable</param>
		/// <param name="vec">Vectors to set</param>
		void SetVec2s(std::string name, std::initializer_list<Vec2D<float>> vec);

		/// <summary>
		/// Set 3-dimensional vectors
		/// </summary>
		/// <param name="name">Name of variable</param>
		/// <param name="vec">Vectors to set</param>
		void SetVec3s(std::string name, std::initializer_list<Vec3D<float>> vec);

		/// <summary>
		/// Set 4-dimensional vectors
		/// </summary>
		/// <param name="name">Name of variable</param>
		/// <param name="vec">Vectors to set</param>
		void SetVec4s(std::string name, std::initializer_list<Vec4D<float>> vec);

		/// <summary>
		/// Set 1-dimensional signed integer vectors
		/// </summary>
		/// <param name="name">Name of variable</param>
		/// <param name="vec">Vectors to set</param>
		void SetIntVec1s(std::string name, std::initializer_list<Vec1D<S32>> vec);

		/// <summary>
		/// Set 2-dimensional signed integer vectors
		/// </summary>
		/// <param name="name">Name of variable</param>
		/// <param name="vec">Vectors to set</param>
		void SetIntVec2s(std::string name, std::initializer_list<Vec2D<S32>> vec);

		/// <summary>
		/// Set 3-dimensional signed integer vectors
		/// </summary>
		/// <param name="name">Name of variable</param>
		/// <param name="vec">Vectors to set</param>
		void SetIntVec3s(std::string name, std::initializer_list<Vec3D<S32>> vec);

		/// <summary>
		/// Set 4-dimensional signed integer vectors
		/// </summary>
		/// <param name="name">Name of variable</param>
		/// <param name="vec">Vectors to set</param>
		void SetIntVec4s(std::string name, std::initializer_list<Vec4D<S32>> vec);

		/// <summary>
		/// Set 1-dimensional unsigned integer vectors
		/// </summary>
		/// <param name="name">Name of variable</param>
		/// <param name="vec">Vectors to set</param>
		void SetUIntVec1s(std::string name, std::initializer_list<Vec1D<U32>> vec);

		/// <summary>
		/// Set 2-dimensional unsigned integer vectors
		/// </summary>
		/// <param name="name">Name of variable</param>
		/// <param name="vec">Vectors to set</param>
		void SetUIntVec2s(std::string name, std::initializer_list<Vec2D<U32>> vec);

		/// <summary>
		/// Set 3-dimensional unsigned integer vectors
		/// </summary>
		/// <param name="name">Name of variable</param>
		/// <param name="vec">Vectors to set</param>
		void SetUIntVec3s(std::string name, std::initializer_list<Vec3D<U32>> vec);

		/// <summary>
		/// Set 4-dimensional unsigned integer vectors
		/// </summary>
		/// <param name="name">Name of variable</param>
		/// <param name="vec">Vectors to set</param>
		void SetUIntVec4s(std::string name, std::initializer_list<Vec4D<U32>> vec);

		/// <summary>
		/// Set 2x2 matrix
		/// </summary>
		/// <param name="name">Name of variable</param>
		/// <param name="mat">Matrix to set</param>
		void SetMatrix2x2(std::string name, Matrix2x2<float> mat);

		/// <summary>
		/// Set 3x3 matrix
		/// </summary>
		/// <param name="name">Name of variable</param>
		/// <param name="mat">Matrix to set</param>
		void SetMatrix3x3(std::string name, Matrix3x3<float> mat);

		/// <summary>
		/// Set 4x4 matrix
		/// </summary>
		/// <param name="name">Name of variable</param>
		/// <param name="mat">Matrix to set</param>
		void SetMatrix4x4(std::string name, Matrix4x4<float> mat);

		/// <summary>
		/// Set 2x3 matrix
		/// </summary>
		/// <param name="name">Name of variable</param>
		/// <param name="mat">Matrix to set</param>
		void SetMatrix2x3(std::string name, Matrix2x3<float> mat);

		/// <summary>
		/// Set 3x2 matrix
		/// </summary>
		/// <param name="name">Name of variable</param>
		/// <param name="mat">Matrix to set</param>
		void SetMatrix3x2(std::string name, Matrix3x2<float> mat);

		/// <summary>
		/// Set 2x4 matrix
		/// </summary>
		/// <param name="name">Name of variable</param>
		/// <param name="mat">Matrix to set</param>
		void SetMatrix2x4(std::string name, Matrix2x4<float> mat);

		/// <summary>
		/// Set 4x2 matrix
		/// </summary>
		/// <param name="name">Name of variable</param>
		/// <param name="mat">Matrix to set</param>
		void SetMatrix4x2(std::string name, Matrix4x2<float> mat);

		/// <summary>
		/// Set 3x4 matrix
		/// </summary>
		/// <param name="name">Name of variable</param>
		/// <param name="mat">Matrix to set</param>
		void SetMatrix3x4(std::string name, Matrix3x4<float> mat);

		/// <summary>
		/// Set 4x3 matrix
		/// </summary>
		/// <param name="name">Name of variable</param>
		/// <param name="mat">Matrix to set</param>
		void SetMatrix4x3(std::string name, Matrix4x3<float> mat);

		/// <summary>
		/// Set 2x2 matrices
		/// </summary>
		/// <param name="name">Name of variable</param>
		/// <param name="mat">Matrices to set</param>
		void SetMatrices2x2(std::string name, std::initializer_list<Matrix2x2<float>> mat);

		/// <summary>
		/// Set 3x3 matrices
		/// </summary>
		/// <param name="name">Name of variable</param>
		/// <param name="mat">Matrices to set</param>
		void SetMatrices3x3(std::string name, std::initializer_list<Matrix3x3<float>> mat);

		/// <summary>
		/// Set 4x4 matrices
		/// </summary>
		/// <param name="name">Name of variable</param>
		/// <param name="mat">Matrices to set</param>
		void SetMatrices4x4(std::string name, std::initializer_list<Matrix4x4<float>> mat);

		/// <summary>
		/// Set 2x3 matrices
		/// </summary>
		/// <param name="name">Name of variable</param>
		/// <param name="mat">Matrices to set</param>
		void SetMatrices2x3(std::string name, std::initializer_list<Matrix2x3<float>> mat);

		/// <summary>
		/// Set 3x2 matrices
		/// </summary>
		/// <param name="name">Name of variable</param>
		/// <param name="mat">Matrices to set</param>
		void SetMatrices3x2(std::string name, std::initializer_list<Matrix3x2<float>> mat);

		/// <summary>
		/// Set 2x4 matrices
		/// </summary>
		/// <param name="name">Name of variable</param>
		/// <param name="mat">Matrices to set</param>
		void SetMatrices2x4(std::string name, std::initializer_list<Matrix2x4<float>> mat);

		/// <summary>
		/// Set 4x2 matrices
		/// </summary>
		/// <param name="name">Name of variable</param>
		/// <param name="mat">Matrices to set</param>
		void SetMatrices4x2(std::string name, std::initializer_list<Matrix4x2<float>> mat);

		/// <summary>
		/// Set 3x4 matrices
		/// </summary>
		/// <param name="name">Name of variable</param>
		/// <param name="mat">Matrices to set</param>
		void SetMatrices3x4(std::string name, std::initializer_list<Matrix3x4<float>> mat);

		/// <summary>
		/// Set 4x3 matrices
		/// </summary>
		/// <param name="name">Name of variable</param>
		/// <param name="mat">Matrices to set</param>
		void SetMatrices4x3(std::string name, std::initializer_list<Matrix4x3<float>> mat);
		
		// <summary>
		/// Start sprite draw
		/// </summary>
		virtual void StartSpriteDraw() = 0;

		/// <summary>
		/// Add sprite draw data
		/// </summary>
		/// <param name="textures">Sprite textures</param>
		/// <param name="sprite">Sprite data</param>
		virtual void AddSprite(std::shared_ptr<std::vector<TextureBind>> textures, SpriteData& sprite) = 0;

		/// <summary>
		/// Flush sprites
		/// </summary>
		virtual void FlushSprites() = 0;

	protected:
		/// <summary>
		/// Shader ID
		/// </summary>
		Ptr id{ 0 };

		/// <summary>
		/// Vertex buffer
		/// </summary>
		std::shared_ptr<VertexBuffer> vertexBuffer{ nullptr };

	private:
		/// <summary>
		/// Unset shader
		/// </summary>
		static void Unset();

		/// <summary>
		/// Variables
		/// </summary>
		std::unordered_map<std::string, int> variables;

		/// <summary>
		/// Active shader
		/// </summary>
		static Shader* active;
	};

}

#endif // VIOLET_SHADER_HPP
