/******************************************************************/
/* Violet Engine                                                  */
/* (C) Devon Artmeier 2022                                        */
/******************************************************************/

#include "Violet.hpp"

namespace Violet {

	/// <summary>
	/// Vertex buffer constructor
	/// </summary>
	/// <param name="vertexSize">Size of vertex</param>
	/// <param name="vertexCount">Vertex count</param>
	VertexBuffer::VertexBuffer(const int vertex_size, const int vertex_count) {
		GLuint id, dataID;
		glGenVertexArrays(1, &id);
		glGenBuffers(1, &dataID);
		this->id = static_cast<Ptr>(id);
		this->dataID = static_cast<Ptr>(dataID);

		bufferSize = vertex_size * vertex_count;
		this->vertexSize = vertex_size;
		data = calloc(bufferSize, 1);

		SetActive();
		glBindBuffer(GL_ARRAY_BUFFER, dataID);
		glBufferData(GL_ARRAY_BUFFER, bufferSize, data, GL_STATIC_DRAW);
	}

	/// <summary>
	/// Vertex buffer destructor
	/// </summary>
	VertexBuffer::~VertexBuffer() {
		if (active == this) {
			Unset();
		}

		GLuint id = static_cast<GLuint>(this->id);
		GLuint dataID = static_cast<GLuint>(this->dataID);
		glDeleteVertexArrays(1, &id);
		glDeleteBuffers(1, &dataID);

		if (data) {
			free(data);
		}
	}

	/// <summary>
	/// Set active
	/// </summary>
	void VertexBuffer::SetActive() {
		if (active != this) {
			glBindVertexArray(static_cast<GLuint>(id));
			active = this;
		}
	}

	/// <summary>
	/// Add attribute
	/// </summary>
	/// <param name="type">Attribute type</param>
	/// <param name="size">Attribute size</param>
	void VertexBuffer::AddAttribute(AttribType type, int size) {
		GLenum type_gl = 0;
		int type_size = 0;

		if (size == 0) {
			Engine::Error("Vertex buffer attribute size cannot be 0.");
		}

		switch (type) {
		case AttribType::Float:
			type_gl = GL_FLOAT;
			type_size = sizeof(float);
			break;
		}
		if (type_gl == 0) {
			Engine::Error("Invalid vertex buffer attribute type.");
		}

		SetActive();
		glVertexAttribPointer(attribCount, size, type_gl, GL_FALSE, vertexSize, (void*)attribPtr);
		glEnableVertexAttribArray(attribCount++);
		attribPtr += static_cast<Ptr>(size) * type_size;
	}

	/// <summary>
	/// Refresh vertex data
	/// </summary>
	void VertexBuffer::RefreshData() {
		RefreshDataPart(0, bufferSize);
	}

	/// <summary>
	/// Refresh a portion of vertex data
	/// </summary>
	/// <param name="offset">Offset</param>
	/// <param name="size">Size</param>
	void VertexBuffer::RefreshDataPart(int offset, int size) {
		glBindBuffer(GL_ARRAY_BUFFER, static_cast<GLuint>(dataID));
		glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
	}

	/// <summary>
	/// Draw vertices
	/// </summary>
	/// <param name="count">Number of vertices to draw</param>
	void VertexBuffer::Draw(const int count) {
		glDrawArrays(GL_TRIANGLES, 0, count);
	}

	/// <summary>
	/// Get data buffer
	/// </summary>
	/// <returns>Data buffer</returns>
	void* VertexBuffer::GetDataBuffer() {
		return data;
	}

	/// <summary>
	/// Unset vertex buffer
	/// </summary>
	void VertexBuffer::Unset() {
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		active = nullptr;
	}

}
