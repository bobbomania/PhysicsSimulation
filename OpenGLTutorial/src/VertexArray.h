#pragma once

#include "VertexBuffer.h"

// used to avoid circular ref in renderer
class VertexBufferLayout;

class VertexArray
{
	private:
		unsigned int m_RendererID;

	public:
		VertexArray();
		~VertexArray();
			
		void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

		void Bind() const;
		void Unbind() const;

};