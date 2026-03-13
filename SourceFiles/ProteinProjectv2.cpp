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



#include "../HeaderFiles/main_imgui.h"
#include "../HeaderFiles/OpenGLDebugger.h"
#include "../HeaderFiles/Shader.h"
#include "../HeaderFiles/Mesh.h"
#include "../HeaderFiles/Camera.h"
#include "../HeaderFiles/SphereMeshGenerator.h"
#include "../HeaderFiles/CylinderMeshGenerator.h"
#include "../HeaderFiles/FileParserPDB.h"

const unsigned int Swidth = 1000;
const unsigned int Sheight = 800;

static bool mouseCaptured = false;

//int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
int main()
{
    // Initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_SAMPLES, 8); // Need to change when i add FBO (Frame Buffer Objects)
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE); // Debugger from Learn OpenGL
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // GLFW Create Window
    glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE); // start maximized
    GLFWwindow* window = glfwCreateWindow(Swidth, Sheight, "Protein Statement", NULL, NULL);
    //GLFWwindow* window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);




    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);






    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    // Adding the Debugger from Learn OpenGL
    //EnableOpenGLDebugging();

    glEnable(GL_CULL_FACE);     // Enable culling
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);


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


    glClearColor(0.1f, 0.1f, 0.12f, 1.0f); // Better to do twice (In and Out)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Better to do twice (In and Out)

    GenerateSphereValues gsv;
    GenerateCylinderFlatValues gcv;
    FileParserPDB fpp;

    //Mesh myMesh(gsv.sphereVertices, gsv.sphereIndices, fpp.LocationPointsVectors, fpp.ColorPointsVector, fpp.WanderVallsRadiusVector);
    Mesh myMesh2(gcv.cylinderVertices, gcv.cylinderIndices);
    Shader SphereShader("ShaderFiles/SphereShaderVertex.vert", "ShaderFiles/SphereShaderFragment.frag");
    Shader CylinderShader("ShaderFiles/CylinderShaderVertex.vert", "ShaderFiles/CylinderShaderFragment.frag");
    Camera myCamera;
    glfwSetWindowUserPointer(window, &myCamera);
    
    //glfwSetKeyCallback(window, &myCamera.GetMovementInput);
    //myCamera.GetMovementInput(window);

    

    

    
    /*float rotation = 0.0f;
    double prevTime = glfwGetTime();*/

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        ImGuiIO& io = ImGui::GetIO();

        // Resizing
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        //glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);



        // Background Color
        glClearColor(0.1f, 0.1f, 0.12f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // IMGUI
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        //ImGui::ShowDemoWindow();



        // Docking Space
        ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);

        DrawImGuiPanels();

        

        // OpenGl Drawings

        static float lastFrame = 0.0f;
        float currentFrame = glfwGetTime();
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        if (!io.WantCaptureKeyboard)
        {
            myCamera.GetMovementInput(window, deltaTime);
        }

        if (!io.WantCaptureMouse)
        {
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
            {
                if (!mouseCaptured)
                {
                    mouseCaptured = true;
                    myCamera.firstMouse = true;
                    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                }
                myCamera.GetMouseInput(window, display_w, display_h);
            }
            else
            {
                mouseCaptured = false;
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            }
        }
        
        /*SphereShader.use();
        myCamera.Use(display_w, display_h, SphereShader);
        myMesh.Draw();*/

        CylinderShader.use();
        myCamera.Use(display_w, display_h, CylinderShader);
        myMesh2.Draw();
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        




        // Close Stuff. Leave
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    // clear OpenGL
    //myMesh.Cleanup();
    myMesh2.Cleanup();
    SphereShader.cleanup();
    CylinderShader.cleanup();


    // clear IMGUI
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    // clear GLFW
    glfwTerminate();
    // end (Win)Main
    return 0;
}