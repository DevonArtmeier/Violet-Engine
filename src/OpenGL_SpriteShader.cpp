/******************************************************************/
/* Violet Engine                                                  */
/* (C) Devon Artmeier 2022                                        */
/******************************************************************/

#include "Violet.hpp"

namespace Violet {
	// Default sprite shader vertex shader code
	static const char* vertexCode =
		"#version 330 core\n"
		"layout (location = 0) in vec2 inPos;\n"
		"layout (location = 1) in vec4 inColor;\n"
		"layout (location = 2) in vec2 texCoord;\n"
		"uniform mat4 projection;\n"
		"out vec4 fragColor;\n"
		"out vec2 fragTexCoord;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = projection * vec4(inPos.x, inPos.y, 0.0, 1.0);\n"
		"	fragColor = inColor;\n"
		"	fragTexCoord = texCoord;\n"
		"}";

	// Default sprite shader fragment shader code
	static const char* fragCode =
		"#version 330 core\n"
		"uniform sampler2D texture0;\n"
		"in vec4 fragColor;\n"
		"in vec2 fragTexCoord;\n"
		"out vec4 outColor;\n"
		"void main()\n"
		"{\n"
		"	outColor = texture(texture0, fragTexCoord) * fragColor;\n"
		"}";

	/// <summary>
	/// Get sprite shader vertex shader code
	/// </summary>
	/// <returns>Sprite shader vertex shader code</returns>
	const char* SpriteShader::GetVertexShader() {
		return vertexCode;
	}

	/// <summary>
	/// Get sprite shader fragment shader code
	/// </summary>
	/// <returns>Sprite shader fragment shader code</returns>
	const char* SpriteShader::GetFragmentShader() {
		return fragCode;
	}
}
