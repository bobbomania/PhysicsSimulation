#pragma once

#include <GL/glew.h>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#define WIDTH_W 960.0f
#define HEIGHT_W 540.0f

// macro for asssert function, not supported by other c++ compilers
#define ASSERT(x) if ((!x)) __debugbreak();

// wraps the function x in an error checking macro, first clearing, running x, and loggin errors
// #x turns x into a string, and the other two are supported by all compilers
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

struct Vertex {
    glm::vec2 Position;
    glm::vec2 TexCoord;
    float TexIndex;
};

class Renderer {
public:
    void Clear() const;
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};