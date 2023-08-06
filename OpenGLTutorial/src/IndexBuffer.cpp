#include "IndexBuffer.h"

#include "Renderer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
    : m_Count(count)
{
    glGenBuffers(1, &m_RendererID); // give ID to the buffer
    Bind(); // bind the id to an array buffer, this is the buffer that is currently selected, and thus the one that is drawn
    // use GL_DYNAMIC if want to modify data often, use docs.gl
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW); // load in the data into the buffer
}

IndexBuffer::~IndexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_RendererID));
}

void IndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID); // bind the id to an array buffer, this is the buffer that is currently selected, and thus the one that is drawn
}

void IndexBuffer::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // bind the id to an array buffer, this is the buffer that is currently selected, and thus the one that is drawn
}
