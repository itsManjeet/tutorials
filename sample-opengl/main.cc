#include <bits/stdc++.h>
using namespace std;

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shaders.hh"

static void error_callback(
    unsigned int source,
    unsigned int type,
    unsigned int id,
    unsigned int serverity,
    int length,
    char const *message,
    void const *user_param)
{
    fprintf(stderr, "CALLBACK: %s, TYPE : 0x%x, Serverity : 0x%x\nMessage: %s\n",
            (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
            type, serverity, message);
}

int main(int ac, char **av)
{
    GLFWwindow *window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(800, 600, "Sample", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
    {
        cout << "Error! failed to init glew" << endl;
        return 1;
    }

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(error_callback, 0);

    /**
     *  -0.5, 0.5  (3)      0.5, 0.5 (0)
     * 
     *                 
     * 
     *  -0.5, -0.5 (2)      0.5, -0.5 (1)
     */

    // in anti-clock-wise order
    float pos[] = {
        0.5f, 0.5f,   // 0
        0.5f, -0.5f,  // 1
        -0.5f, -0.5f, // 2
        -0.5f, 0.5f}; // 3

    unsigned int indices[] = {
        0, 1, 2, // First triangle
        2, 3, 0, // Second triangle
    };

    /**
     * Steps of creating Buffer
     * 1. Generate Buffer Space
     * 2. Specify target type and bind buffer to opengl
     * 3. Bind Data
     *    a. size : in bytes
     *    b. usage: GL_(FREQ)_(NATURE) of access
     *       (only gave hints of the regarding access, not a constraints
     *        slow the process if not a appro. one)
     */

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);

    glBufferData(GL_ARRAY_BUFFER,
                 8 * sizeof(float), // SIZE in Bytes
                 pos,
                 GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);

    glVertexAttribPointer(0,                 // Starting index
                          2,                 // Amount of indices for 1 vertex
                          GL_FLOAT,          // Type
                          GL_FALSE,          // Normalize (convert into float, (false as already float))
                          sizeof(float) * 2, // Space between starting and next vertex index
                          0);

    unsigned int index_buffer;
    glGenBuffers(1, &index_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    auto shader_program = gen_shader_program("sample-opengl/shaders");
    glUseProgram(shader_program);

    while (!glfwWindowShouldClose(window))
    {

        glClear(GL_COLOR_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        /** 
         * SINGLE_BUFFER - Flush()
         * 
         * DOUBLE_BUFFER - SwapBuffer 
         */
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}