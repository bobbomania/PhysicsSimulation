#pragma once

class IndexBuffer
{
private:
	// used as an id for the current object
	unsigned int m_RendererID;
	unsigned int m_Count; // how many indexes
public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	inline unsigned int getCount() const { return m_Count; }
};