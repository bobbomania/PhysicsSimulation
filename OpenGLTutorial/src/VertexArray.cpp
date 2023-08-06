#include "VertexArray.h"
#include "VertexBufferLayout.h"

VertexArray::VertexArray()
{
    // create a vertex array object and binds it
    GLCall(glGenVertexArrays(1, &m_RendererID));
}

VertexArray::~VertexArray()
{
    GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
    Bind();     // bind the array
	vb.Bind();  // bind the buffer

    const auto& elements = layout.GetElements();
    unsigned int offset = 0;

    // binds the layouts
    for (unsigned int i = 0; i < elements.size(); i++) 
    {
        const auto& element = elements[i];
        // enable the vertex
        GLCall(glEnableVertexAttribArray(i));
        // specifies data format of vertex, can also use a struct
        // this line also links the vertex buffer (currently bound buffer) to the vertex array (index 0, 1st parameter)
        GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*) offset));
        offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
    }

}

void VertexArray::Bind() const
{
    GLCall(glBindVertexArray(m_RendererID));
}

void VertexArray::Unbind() const
{
    GLCall(glBindVertexArray(0));
}
