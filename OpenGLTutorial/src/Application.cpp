#include <iostream>

#include "Renderer.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"

#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "scenes/SandScene.h"

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow((int) WIDTH_W, (int) HEIGHT_W, "OpenGL tutorial", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // synchronizes the framerate
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK) {
        std::cout << "GLEW Error" << std::endl;
    };
    // this scope is to destruct the ib and vb objects before the opengl context terminates
    {
        // NOTE: vertex buffer -> index buffer -> glDraw is the order to always write/ structure opengl code

        // blending
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        GLCall(glEnable(GL_BLEND));

        Renderer renderer;

        // create context
         // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

        ImGui_ImplGlfw_InitForOpenGL(window, true);

        const char* glsl_version = "#version 330 core";
        ImGui_ImplOpenGL3_Init(glsl_version);
        ImGui::StyleColorsDark();

        scene::Scene* currentScene = nullptr;
        scene::SceneMenu* sceneMenu = new scene::SceneMenu(currentScene);
        currentScene = sceneMenu;

        sceneMenu->RegisterScene<scene::SandScene>("Sand");

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));

            /* Render here */
            renderer.Clear();

            // Start the Dear ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            if (currentScene) {
                currentScene->OnUpdate(0.0f);
                currentScene->OnRender();

                ImGui::Begin("Scene");

                // go back to menu
                if (currentScene != sceneMenu && ImGui::Button("<-"))
                {
                    delete currentScene;
                    currentScene = sceneMenu;
                }

                currentScene->OnImGuiRender();
                ImGui::End();
            }

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
        delete currentScene;

        if (currentScene != sceneMenu)
            delete sceneMenu;
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}