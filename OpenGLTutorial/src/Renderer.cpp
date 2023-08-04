#include "Renderer.h"

#include <iostream>

// clears all errors, has to be called in loop for all errors
void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

// checks errors
bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] {" << error << "}: " << function << " " << file << ":" << line << std::endl;
        return false;
    }

    return true;
}

void Renderer::Clear() const
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    shader.Bind();

    va.Bind();
    ib.Bind();

    // as the last binded buffer was the index buffer, we have a nullptr
    GLCall(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr));
}
