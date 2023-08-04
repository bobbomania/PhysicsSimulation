#pragma once

#include "SandScene.h"
#include "Renderer.h"

#include "imgui/imgui.h"

namespace scene {

	scene::SandScene::SandScene()
        : m_Proj(glm::ortho(0.0f, WIDTH_W, 0.0f, HEIGHT_W, -1.0f, 1.0f)),
          m_View(glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0, 0)))
    {

        // blending
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        GLCall(glEnable(GL_BLEND));

        m_VAO  = std::make_unique<VertexArray>();

        // vertex buffer obj
        //m_VertexBuffer = std::make_unique<VertexBuffer>(positions, sizeof(positions));

        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);  // for the texture coordinates

        m_VAO->AddBuffer(*m_VertexBuffer, layout);
        m_VAO->Bind();

        //m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 12);

        // TODO: write camera api

        // matrix representing the model, with a 200 shift up and right
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(200, 200, 0));

        // model, view, projection matrix
        glm::mat4 mvp = m_Proj * m_View * model;

        m_Shader = std::make_unique<Shader>("res/shaders/Temp.glsl.shader");
        m_Shader->Bind();

        m_Shader->SetUniformMat4f("u_MVP", mvp);

	}

    scene::SandScene::~SandScene()
	{
	}

	void scene::SandScene::OnUpdate(float deltaTime)
	{
	}

	void scene::SandScene::OnRender()
	{
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));


	}

	void scene::SandScene::OnImGuiRender()
	{
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
	}
}
