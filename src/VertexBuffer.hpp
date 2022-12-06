/******************************************************************/
/* Violet Engine                                                  */
/* (C) Devon Artmeier 2022                                        */
/******************************************************************/

#ifndef VIOLET_VERTEX_BUFFER_HPP
#define VIOLET_VERTEX_BUFFER_HPP

namespace Violet {
	
	/// <summary>
	/// Vertex buffer
	/// </summary>
	class VertexBuffer : public std::enable_shared_from_this<VertexBuffer> {
	public:
		// Friend classes
		friend class Engine;
		friend class Graphics;
		friend class Shader;

		/// <summary>
		/// Attribute type
		/// </summary>
		enum class AttribType {
			Float = 0
		};

		/// <summary>
		/// Vertex buffer destructor
		/// </summary>
		~VertexBuffer();

		/// <summary>
		/// Set active
		/// </summary>
		void SetActive();

		/// <summary>
		/// Add attribute
		/// </summary>
		/// <param name="type">Attribute type</param>
		/// <param name="size">Attribute size</param>
		void AddAttribute(AttribType type, int size);

		/// <summary>
		/// Refresh vertex data
		/// </summary>
		void RefreshData();

		/// <summary>
		/// Refresh a portion of vertex data
		/// </summary>
		/// <param name="offset">Offset</param>
		/// <param name="size">Size</param>
		void RefreshDataPart(int offset, int size);

		/// <summary>
		/// Draw vertices
		/// </summary>
		/// <param name="count">Number of vertices to draw</param>
		void Draw(const int count);

		/// <summary>
		/// Get data buffer
		/// </summary>
		/// <returns>Data buffer</returns>
		void* GetDataBuffer();

	private:
		/// <summary>
		/// Vertex buffer constructor
		/// </summary>
		/// <param name="vertexSize">Size of vertex</param>
		/// <param name="vertexCount">Vertex count</param>
		VertexBuffer(const int vertexSize, const int vertexCount);

		/// <summary>
		/// Unset vertex buffer
		/// </summary>
		static void Unset();

		/// <summary>
		/// Buffer ID
		/// </summary>
		Ptr id{ 0 };

		/// <summary>
		/// Buffer data ID
		/// </summary>
		Ptr dataID{ 0 };

		/// <summary>
		/// Buffer data
		/// </summary>
		void* data{ nullptr };

		/// <summary>
		/// Buffer size
		/// </summary>
		int bufferSize{ 0 };

		/// <summary>
		/// Vertex size
		/// </summary>
		int vertexSize{ 0 };

		/// <summary>
		/// Attribute count
		/// </summary>
		int attribCount{ 0 };

		/// <summary>
		/// Attribute pointer
		/// </summary>
		Ptr attribPtr{ 0 };

		/// <summary>
		/// Active vertex buffer
		/// </summary>
		static VertexBuffer* active;
	};

}

#endif // VIOLET_VERTEX_BUFFER_HPP
