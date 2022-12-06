/******************************************************************/
/* Violet Engine                                                  */
/* (C) Devon Artmeier 2022                                        */
/******************************************************************/

#include "Violet.hpp"

namespace Violet {

	/// <summary>
	/// Get default ortho projection matrix
	/// </summary>
	/// <returns>Default ortho projection matrix</returns>
	Matrix4x4<float> Engine::GetDefaultOrthoMat() {
		Size2D<int> window_size = Graphics::GetViewSize();
		return Math::GetOrthoMat(0, static_cast<float>(window_size.w), 0, static_cast<float>(window_size.h), -1, 1);
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
	Matrix4x4<float> Math::GetOrthoMat(float l, float r, float t, float b, float n, float f) {
		return glm::ortho(l, r, b, t, n, f);
	}

	/// <summary>
	/// Get 2-dimensional translation matrix
	/// </summary>
	/// <param name="pos">Position</param>
	/// <returns>Generated matrix</returns>
	Matrix4x4<float> Math::Translate2DMat(Vec2D<float> pos) {
		return glm::translate(glm::mat4(1.0f), glm::vec3(pos.x, pos.y, 0.0f));
	}

	/// <summary>
	/// Get 2-dimensional scale matrix
	/// </summary>
	/// <param name="scale">Scale</param>
	/// <returns>Generated matrix</returns>
	Matrix4x4<float> Math::Scale2DMat(Vec2D<float> scale) {
		return glm::scale(glm::mat4(1.0f), glm::vec3(scale.x, scale.y, 1));
	}

	/// <summary>
	/// Get 2-dimensional rotation matrix
	/// </summary>
	/// <param name="angle">Angle</param>
	/// <returns>Generated matrix</returns>
	Matrix4x4<float> Math::Rotate2DMat(float angle) {
		return glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0, 0, 1));
	}

	/// <summary>
	/// Get 2-dimensional transformation matrix
	/// </summary>
	/// <param name="pos">Position</param>
	/// <param name="scale">Scale</param>
	/// <param name="angle">Angle</param>
	/// <returns>Generated matrix</returns>
	Matrix4x4<float> Math::Transform2DMat(Vec2D<float> pos, Vec2D<float> scale, float angle) {
		glm::mat4 trns = glm::translate(glm::mat4(1.0f), glm::vec3(pos.x, pos.y, 0.0f));
		trns = glm::rotate(trns, Math::DegToRad(angle), glm::vec3(0, 0, 1));
		trns = glm::scale(trns, glm::vec3(scale.x, scale.y, 1));
		return trns;
	}

}
