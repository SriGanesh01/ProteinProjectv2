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

    }
    ImGui::End();

    if (ImGui::Begin("Ae3")) {
        ImGui::Text("Hello, World!");
        ImGui::Text("This is some useful text.");

    }
    ImGui::End();
}


