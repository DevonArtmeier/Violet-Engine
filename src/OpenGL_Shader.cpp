/******************************************************************/
/* Violet Engine                                                  */
/* (C) Devon Artmeier 2022                                        */
/******************************************************************/

#include "Violet.hpp"

namespace Violet {

	// Info log
	static char infoLog[512];

	/// <summary>
	/// Compile shader code
	/// </summary>
	/// <param name="code">Pointer to code</param>
	/// <param name="type">Shader type</param>
	/// <returns>Compiled shader ID</returns>
	GLuint CompileShader(const char* code, GLenum type) {
		GLuint shader = glCreateShader(type);
		glShaderSource(shader, 1, &code, nullptr);
		glCompileShader(shader);

		int success;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			glDeleteShader(shader);
			Engine::Error("Failed to compile shader: " + std::string(infoLog));
		}

		return shader;
	}

	/// <summary>
	/// Shader constructor
	/// </summary>
	/// <param name="vertexSize">Size of vertex</param>
	/// <param name="vertexCount">Vertex count</param>
	/// <param name="vertexCode">Vertex shader code</param>
	/// <param name="fragCode">Fragment shader code</param>
	Shader::Shader(const int vertexSize, const int vertexCount, std::string vertexCode, std::string fragCode) {
		/* Compile shaders */
		GLuint vertexShader = 0;
		GLuint fragShader = 0;
		if (vertexCode.length() > 0) {
			vertexShader = CompileShader(vertexCode.c_str(), GL_VERTEX_SHADER);
		}
		if (fragCode.length() > 0) {
			fragShader = CompileShader(fragCode.c_str(), GL_FRAGMENT_SHADER);
		}

		/* Link shaders */
		int success;
		GLuint program = glCreateProgram();
		if (vertexShader) {
			glAttachShader(program, vertexShader);
		}
		if (fragShader) {
			glAttachShader(program, fragShader);
		}
		glLinkProgram(program);

		/* Clean up */
		if (vertexShader) {
			glDeleteShader(vertexShader);
		}
		if (fragShader) {
			glDeleteShader(fragShader);
		}

		/* Check status */
		glGetProgramiv(program, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(program, 512, NULL, infoLog);
			glDeleteProgram(program);
			program = 0;
			Engine::Error("Failed to link shaders: " + std::string(infoLog));
		}

		/* Finish setup */
		id = static_cast<Ptr>(program);
		vertexBuffer = std::shared_ptr<VertexBuffer>(new VertexBuffer(vertexSize, vertexCount));
	}

	/// <summary>
	/// Shader destructor
	/// </summary>
	Shader::~Shader() {
		if (active == this) {
			Unset();
		}
		glDeleteProgram(static_cast<GLuint>(id));
	}

	/// <summary>
	/// Get ID
	/// </summary>
	/// <returns>Shader ID</returns>
	Ptr Shader::GetID() const {
		return id;
	}

	/// <summary>
	/// Set active
	/// </summary>
	void Shader::SetActive() {
		if (active != this) {
			glUseProgram(static_cast<GLuint>(id));
			active = this;
		}
	}

	/// <summary>
	/// Add variable
	/// </summary>
	/// <param name="name">Variable name</param>
	void Shader::AddVariable(std::string name) {
		if (variables.find(name) == variables.end()) {
			variables[name] = glGetUniformLocation(static_cast<GLuint>(id), name.c_str());
		}
	}

	/// <summary>
	/// Get shader array data
	/// </summary>
	/// <param name="list">Data to get</param>
	/// <returns>Retrieved array data</returns>
	template<typename T>
	inline T* GetShaderArrayData(std::initializer_list<T> list) {
		T* valArray = new T[list.size()];
		for (int i = 0; i < list.size(); ++i) {
			valArray[i] = *(list.begin() + i);
		}
		return valArray;
	}

	/// <summary>
	/// Set float
	/// </summary>
	/// <param name="name">Name of variable</param>
	/// <param name="val">Value to set</param>
	void Shader::SetFloat(std::string name, float val) {
		if (variables.find(name) != variables.end()) {
			SetActive();
			glUniform1f(variables[name], val);
		}
	}

	/// <summary>
	/// Set signed integer
	/// </summary>
	/// <param name="name">Name of variable</param>
	/// <param name="val">Value to set</param>
	void Shader::SetInt(std::string name, S32 val) {
		if (variables.find(name) != variables.end()) {
			SetActive();
			glUniform1i(variables[name], val);
		}
	}

	/// <summary>
	/// Set unsigned integer
	/// </summary>
	/// <param name="name">Name of variable</param>
	/// <param name="val">Value to set</param>
	void Shader::SetUInt(std::string name, U32 val) {
		if (variables.find(name) != variables.end()) {
			SetActive();
			glUniform1ui(variables[name], val);
		}
	}

	/// <summary>
	/// Set floats
	/// </summary>
	/// <param name="name">Name of variable</param>
	/// <param name="val">Values to set</param>
	void Shader::SetFloats(std::string name, std::initializer_list<float> val) {
		if (variables.find(name) != variables.end()) {
			float* valArray = GetShaderArrayData<float>(val);
			SetActive();
			glUniform1fv(variables[name], static_cast<GLsizei>(val.size()), (GLfloat*)(valArray));
			delete[] valArray;
		}
	}

	/// <summary>
	/// Set signed integers
	/// </summary>
	/// <param name="name">Name of variable</param>
	/// <param name="val">Values to set</param>
	void Shader::SetInts(std::string name, std::initializer_list<S32> val) {
		if (variables.find(name) != variables.end()) {
			S32* valArray = GetShaderArrayData<S32>(val);
			SetActive();
			glUniform1iv(variables[name], static_cast<GLsizei>(val.size()), (GLint*)(valArray));
			delete[] valArray;
		}
	}

	/// <summary>
	/// Set unsigned integers
	/// </summary>
	/// <param name="name">Name of variable</param>
	/// <param name="val">Values to set</param>
	void Shader::SetUInts(std::string name, std::initializer_list<U32> val) {
		if (variables.find(name) != variables.end()) {
			U32* valArray = GetShaderArrayData<U32>(val);
			SetActive();
			glUniform1uiv(variables[name], static_cast<GLsizei>(val.size()), (GLuint*)(valArray));
			delete[] valArray;
		}
	}

	/// <summary>
	/// Set 1-dimensional vector
	/// </summary>
	/// <param name="name">Name of variable</param>
	/// <param name="vec">Vector to set</param>
	void Shader::SetVec1(std::string name, Vec1D<float> vec) {
		if (variables.find(name) != variables.end()) {
			SetActive();
			glUniform1f(variables[name], vec.x);
		}
	}

	/// <summary>
	/// Set 2-dimensional vector
	/// </summary>
	/// <param name="name">Name of variable</param>
	/// <param name="vec">Vector to set</param>
	void Shader::SetVec2(std::string name, Vec2D<float> vec) {
		if (variables.find(name) != variables.end()) {
			SetActive();
			glUniform2f(variables[name], vec.x, vec.y);
		}
	}

	/// <summary>
	/// Set 3-dimensional vector
	/// </summary>
	/// <param name="name">Name of variable</param>
	/// <param name="vec">Vector to set</param>
	void Shader::SetVec3(std::string name, Vec3D<float> vec) {
		if (variables.find(name) != variables.end()) {
			SetActive();
			glUniform3f(variables[name], vec.x, vec.y, vec.z);
		}
	}

	/// <summary>
	/// Set 4-dimensional vector
	/// </summary>
	/// <param name="name">Name of variable</param>
	/// <param name="vec">Vector to set</param>
	void Shader::SetVec4(std::string name, Vec4D<float> vec) {
		if (variables.find(name) != variables.end()) {
			SetActive();
			glUniform4f(variables[name], vec.x, vec.y, vec.z, vec.w);
		}
	}

	/// <summary>
	/// Set 1-dimensional signed integer vector
	/// </summary>
	/// <param name="name">Name of variable</param>
	/// <param name="vec">Vector to set</param>
	void Shader::SetIntVec1(std::string name, Vec1D<S32> vec) {
		if (variables.find(name) != variables.end()) {
			SetActive();
			glUniform1i(variables[name], vec.x);
		}
	}

	/// <summary>
	/// Set 2-dimensional signed integer vector
	/// </summary>
	/// <param name="name">Name of variable</param>
	/// <param name="vec">Vector to set</param>
	void Shader::SetIntVec2(std::string name, Vec2D<S32> vec) {
		if (variables.find(name) != variables.end()) {
			SetActive();
			glUniform2i(variables[name], vec.x, vec.y);
		}
	}

	/// <summary>
	/// Set 3-dimensional signed integer vector
	/// </summary>
	/// <param name="name">Name of variable</param>
	/// <param name="vec">Vector to set</param>
	void Shader::SetIntVec3(std::string name, Vec3D<S32> vec) {
		if (variables.find(name) != variables.end()) {
			SetActive();
			glUniform3i(variables[name], vec.x, vec.y, vec.z);
		}
	}

	/// <summary>
	/// Set 4-dimensional signed integer vector
	/// </summary>
	/// <param name="name">Name of variable</param>
	/// <param name="vec">Vector to set</param>
	void Shader::SetIntVec4(std::string name, Vec4D<S32> vec) {
		if (variables.find(name) != variables.end()) {
			SetActive();
			glUniform4i(variables[name], vec.x, vec.y, vec.z, vec.w);
		}
	}

	/// <summary>
	/// Set 1-dimensional unsigned integer vector
	/// </summary>
	/// <param name="name">Name of variable</param>
	/// <param name="vec">Vector to set</param>
	void Shader::SetUIntVec1(std::string name, Vec1D<U32> vec) {
		if (variables.find(name) != variables.end()) {
			SetActive();
			glUniform1ui(variables[name], vec.x);
		}
	}

	/// <summary>
	/// Set 2-dimensional unsigned integer vector
	/// </summary>
	/// <param name="name">Name of variable</param>
	/// <param name="vec">Vector to set</param>
	void Shader::SetUIntVec2(std::string name, Vec2D<U32> vec) {
		if (variables.find(name) != variables.end()) {
			SetActive();
			glUniform2ui(variables[name], vec.x, vec.y);
		}
	}

	/// <summary>
	/// Set 3-dimensional unsigned integer vector
	/// </summary>
	/// <param name="name">Name of variable</param>
	/// <param name="vec">Vector to set</param>
	void Shader::SetUIntVec3(std::string name, Vec3D<U32> vec) {
		if (variables.find(name) != variables.end()) {
			SetActive();
			glUniform3ui(variables[name], vec.x, vec.y, vec.z);
		}
	}

	/// <summary>
	/// Set 4-dimensional unsigned integer vector
	/// </summary>
	/// <param name="name">Name of variable</param>
	/// <param name="vec">Vector to set</param>
	void Shader::SetUIntVec4(std::string name, Vec4D<U32> vec) {
		if (variables.find(name) != variables.end()) {
			SetActive();
			glUniform4ui(variables[name], vec.x, vec.y, vec.z, vec.w);
		}
	}

	/// <summary>
	/// Set 1-dimensional vectors
	/// </summary>
	/// <param name="name">Name of variable</param>
	/// <param name="vec">Vectors to set</param>
	void Shader::SetVec1s(std::string name, std::initializer_list<Vec1D<float>> vec) {
		if (variables.find(name) != variables.end()) {
			Vec1D<float>* valArray = GetShaderArrayData<Vec1D<float>>(vec);
			SetActive();
			glUniform1fv(variables[name], static_cast<GLsizei>(vec.size()), (GLfloat*)(valArray));
			delete[] valArray;
		}
	}

	/// <summary>
	/// Set 2-dimensional vectors
	/// </summary>
	/// <param name="name">Name of variable</param>
	/// <param name="vec">Vectors to set</param>
	void Shader::SetVec2s(std::string name, std::initializer_list<Vec2D<float>> vec) {
		if (variables.find(name) != variables.end()) {
			Vec2D<float>* valArray = GetShaderArrayData<Vec2D<float>>(vec);
			SetActive();
			glUniform2fv(variables[name], static_cast<GLsizei>(vec.size()), (GLfloat*)(valArray));
			delete[] valArray;
		}
	}

	/// <summary>
	/// Set 3-dimensional vectors
	/// </summary>
	/// <param name="name">Name of variable</param>
	/// <param name="vec">Vectors to set</param>
	void Shader::SetVec3s(std::string name, std::initializer_list<Vec3D<float>> vec) {
		if (variables.find(name) != variables.end()) {
			Vec3D<float>* valArray = GetShaderArrayData<Vec3D<float>>(vec);
			SetActive();
			glUniform3fv(variables[name], static_cast<GLsizei>(vec.size()), (GLfloat*)(valArray));
			delete[] valArray;
		}
	}

	/// <summary>
	/// Set 4-dimensional vectors
	/// </summary>
	/// <param name="name">Name of variable</param>
	/// <param name="vec">Vectors to set</param>
	void Shader::SetVec4s(std::string name, std::initializer_list<Vec4D<float>> vec) {
		if (variables.find(name) != variables.end()) {
			Vec4D<float>* valArray = GetShaderArrayData<Vec4D<float>>(vec);
			SetActive();
			glUniform4fv(variables[name], static_cast<GLsizei>(vec.size()), (GLfloat*)(valArray));
			delete[] valArray;
		}
	}

	/// <summary>
	/// Set 1-dimensional signed integer vectors
	/// </summary>
	/// <param name="name">Name of variable</param>
	/// <param name="vec">Vectors to set</param>
	void Shader::SetIntVec1s(std::string name, std::initializer_list<Vec1D<S32>> vec) {
		if (variables.find(name) != variables.end()) {
			Vec1D<S32>* valArray = GetShaderArrayData<Vec1D<S32>>(vec);
			SetActive();
			glUniform1iv(variables[name], static_cast<GLsizei>(vec.size()), (GLint*)(valArray));
			delete[] valArray;
		}
	}

	/// <summary>
	/// Set 2-dimensional signed integer vectors
	/// </summary>
	/// <param name="name">Name of variable</param>
	/// <param name="vec">Vectors to set</param>
	void Shader::SetIntVec2s(std::string name, std::initializer_list<Vec2D<S32>> vec) {
		if (variables.find(name) != variables.end()) {
			Vec2D<S32>* valArray = GetShaderArrayData<Vec2D<S32>>(vec);
			SetActive();
			glUniform2iv(variables[name], static_cast<GLsizei>(vec.size()), (GLint*)(valArray));
			delete[] valArray;
		}
	}

	/// <summary>
	/// Set 3-dimensional signed integer vectors
	/// </summary>
	/// <param name="name">Name of variable</param>
	/// <param name="vec">Vectors to set</param>
	void Shader::SetIntVec3s(std::string name, std::initializer_list<Vec3D<S32>> vec) {
		if (variables.find(name) != variables.end()) {
			Vec3D<S32>* valArray = GetShaderArrayData<Vec3D<S32>>(vec);
			SetActive();
			glUniform3iv(variables[name], static_cast<GLsizei>(vec.size()), (GLint*)(valArray));
			delete[] valArray;
		}
	}

	/// <summary>
	/// Set 4-dimensional signed integer vectors
	/// </summary>
	/// <param name="name">Name of variable</param>
	/// <param name="vec">Vectors to set</param>
	void Shader::SetIntVec4s(std::string name, std::initializer_list<Vec4D<S32>> vec) {
		if (variables.find(name) != variables.end()) {
			Vec4D<S32>* valArray = GetShaderArrayData<Vec4D<S32>>(vec);
			SetActive();
			glUniform4iv(variables[name], static_cast<GLsizei>(vec.size()), (GLint*)(valArray));
			delete[] valArray;
		}
	}

	/// <summary>
	/// Set 1-dimensional unsigned integer vectors
	/// </summary>
	/// <param name="name">Name of variable</param>
	/// <param name="vec">Vectors to set</param>
	void Shader::SetUIntVec1s(std::string name, std::initializer_list<Vec1D<U32>> vec) {
		if (variables.find(name) != variables.end()) {
			Vec1D<U32>* valArray = GetShaderArrayData<Vec1D<U32>>(vec);
			SetActive();
			glUniform1uiv(variables[name], static_cast<GLsizei>(vec.size()), (GLuint*)(valArray));
			delete[] valArray;
		}
	}

	/// <summary>
	/// Set 2-dimensional unsigned integer vectors
	/// </summary>
	/// <param name="name">Name of variable</param>
	/// <param name="vec">Vectors to set</param>
	void Shader::SetUIntVec2s(std::string name, std::initializer_list<Vec2D<U32>> vec) {
		if (variables.find(name) != variables.end()) {
			Vec2D<U32>* valArray = GetShaderArrayData<Vec2D<U32>>(vec);
			SetActive();
			glUniform2uiv(variables[name], static_cast<GLsizei>(vec.size()), (GLuint*)(valArray));
			delete[] valArray;
		}
	}

	/// <summary>
	/// Set 3-dimensional unsigned integer vectors
	/// </summary>
	/// <param name="name">Name of variable</param>
	/// <param name="vec">Vectors to set</param>
	void Shader::SetUIntVec3s(std::string name, std::initializer_list<Vec3D<U32>> vec) {
		if (variables.find(name) != variables.end()) {
			Vec3D<U32>* valArray = GetShaderArrayData<Vec3D<U32>>(vec);
			SetActive();
			glUniform3uiv(variables[name], static_cast<GLsizei>(vec.size()), (GLuint*)(valArray));
			delete[] valArray;
		}
	}

	/// <summary>
	/// Set 4-dimensional unsigned integer vectors
	/// </summary>
	/// <param name="name">Name of variable</param>
	/// <param name="vec">Vectors to set</param>
	void Shader::SetUIntVec4s(std::string name, std::initializer_list<Vec4D<U32>> vec) {
		if (variables.find(name) != variables.end()) {
			Vec4D<U32>* valArray = GetShaderArrayData<Vec4D<U32>>(vec);
			SetActive();
			glUniform4uiv(variables[name], static_cast<GLsizei>(vec.size()), (GLuint*)(valArray));
			delete[] valArray;
		}
	}

	/// <summary>
	/// Set 2x2 matrix
	/// </summary>
	/// <param name="name">Name of variable</param>
	/// <param name="mat">Matrix to set</param>
	void Shader::SetMatrix2x2(std::string name, Matrix2x2<float> mat) {
		if (variables.find(name) != variables.end()) {
			SetActive();
			glUniformMatrix2fv(variables[name], 1, false, (GLfloat*)(&mat));
		}
	}

	/// <summary>
	/// Set 3x3 matrix
	/// </summary>
	/// <param name="name">Name of variable</param>
	/// <param name="mat">Matrix to set</param>
	void Shader::SetMatrix3x3(std::string name, Matrix3x3<float> mat) {
		if (variables.find(name) != variables.end()) {
			SetActive();
			glUniformMatrix3fv(variables[name], 1, false, (GLfloat*)(&mat));
		}
	}

	/// <summary>
	/// Set 4x4 matrix
	/// </summary>
	/// <param name="name">Name of variable</param>
	/// <param name="mat">Matrix to set</param>
	void Shader::SetMatrix4x4(std::string name, Matrix4x4<float> mat) {
		if (variables.find(name) != variables.end()) {
			SetActive();
			glUniformMatrix4fv(variables[name], 1, false, (GLfloat*)(&mat));
		}
	}

	/// <summary>
	/// Set 2x3 matrix
	/// </summary>
	/// <param name="name">Name of variable</param>
	/// <param name="mat">Matrix to set</param>
	void Shader::SetMatrix2x3(std::string name, Matrix2x3<float> mat) {
		if (variables.find(name) != variables.end()) {
			SetActive();
			glUniformMatrix2x3fv(variables[name], 1, false, (GLfloat*)(&mat));
		}
	}

	/// <summary>
	/// Set 3x2 matrix
	/// </summary>
	/// <param name="name">Name of variable</param>
	/// <param name="mat">Matrix to set</param>
	void Shader::SetMatrix3x2(std::string name, Matrix3x2<float> mat) {
		if (variables.find(name) != variables.end()) {
			SetActive();
			glUniformMatrix3x2fv(variables[name], 1, false, (GLfloat*)(&mat));
		}
	}

	/// <summary>
	/// Set 2x4 matrix
	/// </summary>
	/// <param name="name">Name of variable</param>
	/// <param name="mat">Matrix to set</param>
	void Shader::SetMatrix2x4(std::string name, Matrix2x4<float> mat) {
		if (variables.find(name) != variables.end()) {
			SetActive();
			glUniformMatrix2x4fv(variables[name], 1, false, (GLfloat*)(&mat));
		}
	}

	/// <summary>
	/// Set 4x2 matrix
	/// </summary>
	/// <param name="name">Name of variable</param>
	/// <param name="mat">Matrix to set</param>
	void Shader::SetMatrix4x2(std::string name, Matrix4x2<float> mat) {
		if (variables.find(name) != variables.end()) {
			SetActive();
			glUniformMatrix4x2fv(variables[name], 1, false, (GLfloat*)(&mat));
		}
	}

	/// <summary>
	/// Set 3x4 matrix
	/// </summary>
	/// <param name="name">Name of variable</param>
	/// <param name="mat">Matrix to set</param>
	void Shader::SetMatrix3x4(std::string name, Matrix3x4<float> mat) {
		if (variables.find(name) != variables.end()) {
			SetActive();
			glUniformMatrix3x4fv(variables[name], 1, false, (GLfloat*)(&mat));
		}
	}

	/// <summary>
	/// Set 4x3 matrix
	/// </summary>
	/// <param name="name">Name of variable</param>
	/// <param name="mat">Matrix to set</param>
	void Shader::SetMatrix4x3(std::string name, Matrix4x3<float> mat) {
		if (variables.find(name) != variables.end()) {
			SetActive();
			glUniformMatrix4x3fv(variables[name], 1, false, (GLfloat*)(&mat));
		}
	}

	/// <summary>
	/// Set 2x2 matrices
	/// </summary>
	/// <param name="name">Name of variable</param>
	/// <param name="mat">Matrices to set</param>
	void Shader::SetMatrices2x2(std::string name, std::initializer_list<Matrix2x2<float>> mat) {
		if (variables.find(name) != variables.end()) {
			Matrix2x2<float>* valArray = GetShaderArrayData<Matrix2x2<float>>(mat);
			SetActive();
			glUniformMatrix2fv(variables[name], static_cast<GLsizei>(mat.size()), false, (GLfloat*)(valArray));
			delete[] valArray;
		}
	}

	/// <summary>
	/// Set 3x3 matrices
	/// </summary>
	/// <param name="name">Name of variable</param>
	/// <param name="mat">Matrices to set</param>
	void Shader::SetMatrices3x3(std::string name, std::initializer_list<Matrix3x3<float>> mat) {
		if (variables.find(name) != variables.end()) {
			Matrix3x3<float>* valArray = GetShaderArrayData<Matrix3x3<float>>(mat);
			SetActive();
			glUniformMatrix3fv(variables[name], static_cast<GLsizei>(mat.size()), false, (GLfloat*)(valArray));
			delete[] valArray;
		}
	}

	/// <summary>
	/// Set 4x4 matrices
	/// </summary>
	/// <param name="name">Name of variable</param>
	/// <param name="mat">Matrices to set</param>
	void Shader::SetMatrices4x4(std::string name, std::initializer_list<Matrix4x4<float>> mat) {
		if (variables.find(name) != variables.end()) {
			Matrix4x4<float>* valArray = GetShaderArrayData<Matrix4x4<float>>(mat);
			SetActive();
			glUniformMatrix4fv(variables[name], static_cast<GLsizei>(mat.size()), false, (GLfloat*)(valArray));
			delete[] valArray;
		}
	}

	/// <summary>
	/// Set 2x3 matrices
	/// </summary>
	/// <param name="name">Name of variable</param>
	/// <param name="mat">Matrices to set</param>
	void Shader::SetMatrices2x3(std::string name, std::initializer_list<Matrix2x3<float>> mat) {
		if (variables.find(name) != variables.end()) {
			Matrix2x3<float>* valArray = GetShaderArrayData<Matrix2x3<float>>(mat);
			SetActive();
			glUniformMatrix2x3fv(variables[name], static_cast<GLsizei>(mat.size()), false, (GLfloat*)(valArray));
			delete[] valArray;
		}
	}

	/// <summary>
	/// Set 3x2 matrices
	/// </summary>
	/// <param name="name">Name of variable</param>
	/// <param name="mat">Matrices to set</param>
	void Shader::SetMatrices3x2(std::string name, std::initializer_list<Matrix3x2<float>> mat) {
		if (variables.find(name) != variables.end()) {
			Matrix3x2<float>* valArray = GetShaderArrayData<Matrix3x2<float>>(mat);
			SetActive();
			glUniformMatrix3x2fv(variables[name], static_cast<GLsizei>(mat.size()), false, (GLfloat*)(valArray));
			delete[] valArray;
		}
	}

	/// <summary>
	/// Set 2x4 matrices
	/// </summary>
	/// <param name="name">Name of variable</param>
	/// <param name="mat">Matrices to set</param>
	void Shader::SetMatrices2x4(std::string name, std::initializer_list<Matrix2x4<float>> mat) {
		if (variables.find(name) != variables.end()) {
			Matrix2x4<float>* valArray = GetShaderArrayData<Matrix2x4<float>>(mat);
			SetActive();
			glUniformMatrix2x4fv(variables[name], static_cast<GLsizei>(mat.size()), false, (GLfloat*)(valArray));
			delete[] valArray;
		}
	}

	/// <summary>
	/// Set 4x2 matrices
	/// </summary>
	/// <param name="name">Name of variable</param>
	/// <param name="mat">Matrices to set</param>
	void Shader::SetMatrices4x2(std::string name, std::initializer_list<Matrix4x2<float>> mat) {
		if (variables.find(name) != variables.end()) {
			Matrix4x2<float>* valArray = GetShaderArrayData<Matrix4x2<float>>(mat);
			SetActive();
			glUniformMatrix4x2fv(variables[name], static_cast<GLsizei>(mat.size()), false, (GLfloat*)(valArray));
			delete[] valArray;
		}
	}

	/// <summary>
	/// Set 3x4 matrices
	/// </summary>
	/// <param name="name">Name of variable</param>
	/// <param name="mat">Matrices to set</param>
	void Shader::SetMatrices3x4(std::string name, std::initializer_list<Matrix3x4<float>> mat) {
		if (variables.find(name) != variables.end()) {
			Matrix3x4<float>* valArray = GetShaderArrayData<Matrix3x4<float>>(mat);
			SetActive();
			glUniformMatrix3x4fv(variables[name], static_cast<GLsizei>(mat.size()), false, (GLfloat*)(valArray));
			delete[] valArray;
		}
	}

	/// <summary>
	/// Set 4x3 matrices
	/// </summary>
	/// <param name="name">Name of variable</param>
	/// <param name="mat">Matrices to set</param>
	void Shader::SetMatrices4x3(std::string name, std::initializer_list<Matrix4x3<float>> mat) {
		if (variables.find(name) != variables.end()) {
			Matrix4x3<float>* valArray = GetShaderArrayData<Matrix4x3<float>>(mat);
			SetActive();
			glUniformMatrix4x3fv(variables[name], static_cast<GLsizei>(mat.size()), false, (GLfloat*)(valArray));
			delete[] valArray;
		}
	}

	/// <summary>
	/// Unset shader
	/// </summary>
	void Shader::Unset() {
		glUseProgram(0);
		active = nullptr;
	}

}
