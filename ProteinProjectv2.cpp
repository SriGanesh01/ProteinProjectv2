//#include <windows.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <iostream>
#include <cmath>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



#include "main_imgui.h"
#include "OpenGLDebugger.h"
#include "Shader.h"
#include "Mesh.h"
#include "Camera.h"

const unsigned int Swidth = 1000;
const unsigned int Sheight = 800;

//int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
int main()
{
    // Initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE); // Debugger from Learn OpenGL
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // GLFW Create Window
    glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE); // start maximized
    GLFWwindow* window = glfwCreateWindow(Swidth, Sheight, "My Title", NULL, NULL);
    //GLFWwindow* window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);
    // Adding the Debugger from Learn OpenGL
    //EnableOpenGLDebugging();

    // Initialize IMGUI
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable Docking

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplOpenGL3_Init("#version 330");

    ImGui::StyleColorsDark();

    glEnable(GL_PROGRAM_POINT_SIZE);

    // Data
    std::vector<float> Tvertices = {
        /*
        // -------- QUAD (OLD DATA) --------
         0.5f,  0.5f,  0.0f,
        -0.5f,  0.5f,  0.0f,
        -0.5f, -0.5f,  0.0f,
         0.5f, -0.5f,  0.0f
        */

        // -------- PYRAMID (NEW DATA) --------
        // Base (square)
        -0.5f, 0.0f, -0.5f,   // 0
         0.5f, 0.0f, -0.5f,   // 1
         0.5f, 0.0f,  0.5f,   // 2
        -0.5f, 0.0f,  0.5f,   // 3

        // Apex (top)
         0.0f, 0.8f,  0.0f    // 4
    };

    std::vector<unsigned int> Tindices = {
        /*
        // -------- QUAD (OLD INDICES) --------
        0, 1, 2,
        0, 2, 3
        */

        // -------- PYRAMID (NEW INDICES) --------
        // Base
        0, 1, 2,
        0, 2, 3,

        // Sides
        0, 1, 4,
        1, 2, 4,
        2, 3, 4,
        3, 0, 4
    };

    // -------- PYRAMID VARIANT (SHORTER, WIDER) --------

    std::vector<float> bVertices = {
        // Base (rectangle) - Positioned at Y = 1.5
        // X      Y      Z
        2.0f,  1.5f,  2.0f,   // 0: Back-Left
        5.0f,  1.5f,  2.0f,   // 1: Back-Right
        5.0f,  1.5f,  4.0f,   // 2: Front-Right
        2.0f,  1.5f,  4.0f,   // 3: Front-Left

        // Apex (Pointed top) - Positioned higher at Y = 5.0
        3.5f,  5.0f,  3.0f    // 4: Top Center
    };

    std::vector<unsigned int> bIndices = {
        // Base
        0, 1, 2,
        0, 2, 3,

        // Sides
        0, 1, 4,
        1, 2, 4,
        2, 3, 4,
        3, 0, 4
    };



    glClearColor(0.45f, 0.55f, 0.60f, 1.00f); // Better to do twice (In and Out)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Better to do twice (In and Out)

    

    
    Mesh myMesh(Tvertices, Tindices);
    Mesh myMesh2(bVertices, bIndices);
    Shader myShader("./ShaderVertex.vert", "./ShaderFragment.frag");
    Camera myCamera;
    
    


    
    /*float rotation = 0.0f;
    double prevTime = glfwGetTime();*/

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // Resizing
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);



        // Background Color
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // IMGUI
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        //ImGui::ShowDemoWindow();



        // Docking Space
        ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);

        DrawImGuiPanels();

        myShader.use();

        // OpenGl Drawings

        myCamera.Use(display_w, display_h, myShader);


        myMesh.Draw();
        myMesh2.Draw();
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        




        // Close Stuff. Leave
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    // clear OpenGL
    myMesh.Cleanup();
    myMesh2.Cleanup();
    myShader.cleanup();


    // clear IMGUI
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    // clear GLFW
    glfwTerminate();
    // end (Win)Main
    return 0;
}