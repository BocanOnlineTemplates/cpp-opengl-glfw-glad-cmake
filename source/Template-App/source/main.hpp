//
// cpp-opengl-glfw-cmake
// main.hpp
//
#pragma once

#include <array>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define INFOLOG_SIZE 512

unsigned int shaderProgram{};

unsigned int VBO;
unsigned int VAO;

int success;
char infoLog[INFOLOG_SIZE];

glm::mat4 rotationMatrix = glm::mat4(1.0f);

void processInput(GLFWwindow* window, float deltaTime);
void framebufferSizeChanged(GLFWwindow* window, int width, int height);
void render(GLFWwindow* window);

constexpr auto vertexShaderSource = R"(
    
    #version 330 core

    layout (location = 0) in vec3 aPos;
    uniform mat4 rotationMatrix;

    void main() {

        gl_Position = rotationMatrix * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    }
)";

constexpr auto fragmentShaderSource = R"(

    #version 330 core

    out vec4 FragColor;

    void main() {

        FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    }
)";

constexpr auto squareVertices = std::array {

    -0.5f,  0.5f,  0.0f, // top-left
     0.5f,  0.5f,  0.0f, // top-right
     0.5f,  0.5f,  0.0f, // top-right
     0.5f, -0.5f,  0.0f, // bottom-right
     0.5f, -0.5f,  0.0f, // bottom-right
    -0.5f, -0.5f,  0.0f, // bottom-left
    -0.5f, -0.5f,  0.0f, // bottom-left
    -0.5f,  0.5f,  0.0f  // top-left
};

void framebufferSizeChanged(GLFWwindow* window, int width, int height) {

    glViewport(0, 0, width, height);
    render(window);
}

void processInput(GLFWwindow* window, float deltaTime) {

    const float rotationSpeedDegreesPerSecond = 90.0f;
    const float rotationAnglePerFrame = rotationSpeedDegreesPerSecond * deltaTime;

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {

        rotationMatrix = glm::rotate(rotationMatrix,
                                     glm::radians(rotationAnglePerFrame),
                                     glm::vec3(0.0f, 0.0f, 1.0f));
    }
    
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {

        rotationMatrix = glm::rotate(rotationMatrix,
                                     glm::radians(-rotationAnglePerFrame),
                                     glm::vec3(0.0f, 0.0f, 1.0f));
    }
}

void render(GLFWwindow* window) {

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);

    auto location = glGetUniformLocation(shaderProgram, "rotationMatrix");
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(rotationMatrix));

    glDrawArrays(GL_LINES, 0, static_cast<GLsizei>(squareVertices.size() / 3));

    glfwSwapBuffers(window);
}
