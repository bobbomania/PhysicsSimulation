#pragma once

#include "Renderer.h"
#include "Scene.h"

#include "Utils.h"

#include "imgui/imgui.h"
#include <memory>


namespace scene {
	class SandScene : public Scene
	{
	public:
		SandScene();
		~SandScene();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		Renderer m_Renderer;
		world::World m_World;
		ImGuiIO& m_Io;
	};
}