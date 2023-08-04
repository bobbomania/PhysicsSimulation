#include "Scene.h"
#include "imgui/imgui.h"

#pragma once

namespace scene {
	SceneMenu::SceneMenu(Scene*& currentScenePointer)
		: m_CurrentScene(currentScenePointer)
	{
	}

	void SceneMenu::OnImGuiRender()
	{
		for (auto& Scene : m_Scenes)
		{
			if (ImGui::Button(Scene.first.c_str()))
				m_CurrentScene = Scene.second();
		}
	}
}
