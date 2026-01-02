//#include <windows.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>


#include "main_imgui.h"
#include "OpenGLDebugger.h"

static std::string ParseShader(const std::string filepath)
{
    std::ifstream srcFile(filepath);
    std::stringstream srcCode;
    srcCode << srcFile.rdbuf();
    return srcCode.str();
}

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
    GLFWwindow* window = glfwCreateWindow(1000, 800, "My Title", NULL, NULL);
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
    float Tvertices[] = {
        /*-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
         0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
         0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f,

         -0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,
         0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,
         0.0f,  -0.5f * float(sqrt(3)) / 3, 0.0f,*/

        0.5f, 0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f

    };

    unsigned int Tindices[] = {
        0, 1, 2,
        0, 2, 3
    };

    glClearColor(0.45f, 0.55f, 0.60f, 1.00f); // Better to do twice (In and Out)
    glClear(GL_COLOR_BUFFER_BIT); // Better to do twice (In and Out)

    // Generate and bind VAO
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO); // Better to bind inside the while loop. So do both

    // Genetate, Bind and add data to VBO
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);  
    glBufferData(GL_ARRAY_BUFFER, sizeof(Tvertices), Tvertices, GL_STATIC_DRAW);

    // Tell VBO How to read the data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Genetate, Bind and add data to EBO
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Tindices), Tindices, GL_STATIC_DRAW);

    // Read vertex shader
    std::string vertexShaderSourceString = ParseShader("./ShaderVertex.vert");
    const char* vertexShaderSourceCharPointer = vertexShaderSourceString.c_str();

    // Read fragment Shader
    std::string fragmentShaderSourceString = ParseShader("./ShaderFragment.frag");
    const char* fragmentShaderSourceCharPointer = fragmentShaderSourceString.c_str();

    // Create Vertex Shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSourceCharPointer, NULL);
    glCompileShader(vertexShader);

    // Create Fragment Shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSourceCharPointer, NULL);
    glCompileShader(fragmentShader);

    // Error Check (Default Code)
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // End of Error Check (Default Code) Code

    // Create Program and tell it to use the shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Delete created Shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    


    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // Resizing
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);

        // Background Color
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);

        // IMGUI
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        //ImGui::ShowDemoWindow();



        // Docking Space
        ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);

        DrawImGuiPanels();


        // OpenGl Drawings

        glBindVertexArray(VAO); // Bind here instead of outside if vertex changes often. Bind at both places. Better Practice
        glUseProgram(shaderProgram);
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);




        // Close Stuff. Leave
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    // clear OpenGL
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);


    // clear IMGUI
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    // clear GLFW
    glfwTerminate();
    // end (Win)Main
    return 0;
}