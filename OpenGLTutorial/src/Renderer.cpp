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

void DrawParticle(world::Particle *particle, world::World& world) {

    glPointSize((GLfloat) particle->radius);

    glm::vec4 color = world.m_Solids.getColor(particle);
    glColor3f(color.r, color.g, color.b);

    glVertex2i((GLint) particle->Pos.x, (GLint) HEIGHT_W - particle->Pos.y);
}

void Renderer::DrawParticles(world::World& world) const {

    // setup opengl
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, WIDTH_W, HEIGHT_W, 0.0, -1.0f, 1.0f);

    glBegin(GL_POINTS);

    world.IterateMovableParticles(*DrawParticle);
    world.IterateImmovableParticles(*DrawParticle);

    glEnd();
}
