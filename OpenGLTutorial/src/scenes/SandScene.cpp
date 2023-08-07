#pragma once

#include "SandScene.h"

namespace scene {

	scene::SandScene::SandScene()
        : m_Renderer(), m_World(true), m_Io(ImGui::GetIO())
    {

        // blending
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        GLCall(glEnable(GL_BLEND));

		(void) m_Io;

		world::Particle p;
		p.Pos = { 100, 100 };
		p.Vel = { 100, 100 };
		p.Acc = { 0, 0 };
		p.radius = 10.0f;

		p.type = world::SAND;

		m_World.AddParticle(p);
	}

    scene::SandScene::~SandScene()
	{
	}

	void scene::SandScene::OnUpdate(float deltaTime)
	{
		float fps = m_Io.Framerate;
		m_World.Update(1.0f / fps);
	}

	void scene::SandScene::OnRender()
	{
		m_Renderer.DrawParticles(m_World);
	}

	void scene::SandScene::OnImGuiRender()
	{
        m_Io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		m_Io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / m_Io.Framerate, m_Io.Framerate);
	}
}
