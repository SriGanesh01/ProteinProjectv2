#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

void DrawImGuiPanels()
{

    if (ImGui::Begin("Ae")) {
        ImGui::Text("Hello, World!");
        ImGui::Text("This is some useful text.");

    }
    ImGui::End();

    if (ImGui::Begin("Ae2")) {
        ImGui::Text("Hello, World!");
        ImGui::Text("This is some useful text.");

        static ImVec4 color = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);

        ImGui::ColorPicker4("Protein Color", (float*)&color);

    }
    ImGui::End();

    if (ImGui::Begin("Ae3")) {
        ImGui::Text("Hello, World!");
        ImGui::Text("This is some useful text.");

    }
    ImGui::End();

    if (ImGui::Begin("Performance")) {
        ImGuiIO& io = ImGui::GetIO();
        ImGui::Text("FPS: %.1f", io.Framerate);
        ImGui::Text("Frame Time: %.3f ms", 1000.0f / io.Framerate);
    }
    ImGui::End();
}


