#pragma once

#include <vector>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#include "Utils.h"
#include "physicsObjects/World.h"

struct Vertex {
    glm::vec2 Position;
    glm::vec2 TexCoord;
    float TexIndex;
};

class Renderer {
public:
    void Clear() const;
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
    void DrawParticles(world::World& world) const;
};