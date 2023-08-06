#pragma once

class VertexBuffer
{
private:
	// used as an id for the current object
	unsigned int m_RendererID;
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
};