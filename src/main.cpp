// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <ft2build.h>
#include <stdio.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include FT_FREETYPE_H

// clang-format on
#define HEIGHT 800
#define WIDTH 800

char *ReadFileToBuffer(char *file_path) {
    char *buffer;
    FILE *f = fopen(file_path, "r");
    fseek(f, 0, SEEK_SET);
    fread(buffer, 1024, 1, f);
    return buffer;
}

void CreateProgram(unsigned int ID, char *shader, char *shader2) {
    unsigned int vertex, fragment;
    char *VertexShaderCode = ReadFileToBuffer(shader);
    char *FragmentShaderCode = ReadFileToBuffer(shader2);
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &VertexShaderCode, NULL);
    glCompileShader(vertex);

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &FragmentShaderCode, NULL);
    glCompileShader(fragment);

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

static void glfw_update_viewport(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

static void glfw_error_callback(int error, const char *description) {
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

int main(int, char **) {
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(1280, 720, "Hello World", NULL, NULL);
    if (window == NULL)
        return 1;
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    while (!glfwWindowShouldClose(window)) {
        glClearColor(1.0f, 0.4f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
