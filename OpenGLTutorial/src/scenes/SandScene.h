#pragma once

#include "Scene.h"

#include "Texture.h"
#include "VertexBufferLayout.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

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
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;

		std::unique_ptr<Shader> m_Shader;

		glm::mat4 m_Proj, m_View;
	};
}