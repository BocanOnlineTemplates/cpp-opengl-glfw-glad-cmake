//
// cpp-opengl-glfw-cmake
// main.cpp
//

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "main.hpp"

int main(int argc, char** argv) {

    if (!glfwInit()) {

        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    const GLFWvidmode* VideoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    const auto ScreenHeight = VideoMode->height;

    GLFWwindow* window = glfwCreateWindow(ScreenHeight / 2, ScreenHeight / 2,
                                          "Bocan Online C++ Template (OpenGL, GLFW, GLAD, GLM)", 
                                          NULL, NULL);

    if (!window) {
        
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {

        std::cerr << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }
   
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success) {

        glGetShaderInfoLog(vertexShader, INFOLOG_SIZE, nullptr, infoLog);
        std::cout << "Vertex Shader Compilation Failed: " << infoLog << std::endl;
    }

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if (!success) {

        glGetShaderInfoLog(fragmentShader, INFOLOG_SIZE, nullptr, infoLog);
        std::cout << "Fragment Shader Compliation Failed: " << infoLog << std::endl;
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

    if (!success) {

        glGetProgramInfoLog(shaderProgram, INFOLOG_SIZE, nullptr, infoLog);
        std::cout << "Shader Program Linking Failed: " << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER,
                 squareVertices.size() * sizeof(float),
                 squareVertices.data(),
                 GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glfwSetFramebufferSizeCallback(window, framebufferSizeChanged);

    float lastFrameStartTime = 0.0f;

    while (!glfwWindowShouldClose(window)) {

        float currentFrameStartTime = static_cast<float>(glfwGetTime());
        float deltaTime = currentFrameStartTime - lastFrameStartTime;
        lastFrameStartTime = currentFrameStartTime;

        processInput(window, deltaTime);
        render(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate(); 
    return 0;
}
