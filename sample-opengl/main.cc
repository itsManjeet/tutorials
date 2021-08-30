#include <bits/stdc++.h>
using namespace std;

#include <GLES3/gl3.h>
#include <GLFW/glfw3.h>

static const char
    *vertex_shader_buffer = "#version 330 core\n"
                            "layout (location = 0) in vec3 aPos;\n"
                            "void main()\n"
                            "{\n"
                            "  gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                            "}\0";

static const char
    *fragment_shader_buffer = "#version 330 core\n"
                              "out vec4 FragColor;\n"
                              "void main()\n"
                              "{\n"
                              "  FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                              "}\n\0";
int main(int ac, char **av)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "Sample", nullptr, nullptr);
    if (window == nullptr)
    {
        cout << "Initialization failed" << endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(
        window,
        [](GLFWwindow *window, int width, int height)
        { glViewport(0, 0, width, height); });

    unsigned int vertexShader;
    {
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertex_shader_buffer, nullptr);
        glCompileShader(vertexShader);

        int success;
        char info_log[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertexShader, 512, nullptr, info_log);
            cout << "Error! vertex shader " << info_log << endl;
        }
    }

    unsigned int fragmentShader;
    {
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragment_shader_buffer, nullptr);
        glCompileShader(fragmentShader);

        int success;
        char info_log[512];
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragmentShader, 512, nullptr, info_log);
            cout << "Error! fragment shader " << info_log << endl;
        }
    }

    unsigned int shaderProgram;
    {
        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);

        int success;
        char info_log[512];
        glGetShaderiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shaderProgram, 512, nullptr, info_log);
            cout << "Error! fragment shader " << info_log << endl;
        }
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f};

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window))
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}