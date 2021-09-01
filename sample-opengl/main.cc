#include <bits/stdc++.h>
using namespace std;

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shaders.hh"

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

    /**
     *             (0.0, 1.0)
     * 
     *  (-1.0, 0.0)         (1.0, 0.0)
     */

    float pos[] = {
        0.0f, 1.0f,
        -1.0f, 0.0f,
        1.0f, 0.0f};

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
                 6 * sizeof(float), // SIZE in Bytes
                 pos,
                 GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);

    glVertexAttribPointer(0,                 // Starting index
                          2,                 // Amount of indices for 1 vertex
                          GL_FLOAT,          // Type
                          GL_FALSE,          // Normalize (convert into float, (false as already float))
                          sizeof(float) * 2, // Space between starting and next vertex index
                          0);

    auto shader_program = gen_shader_program("sample-opengl/shaders");
    glUseProgram(shader_program);

    while (!glfwWindowShouldClose(window))
    {

        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, // Mode
                     0,            // Starting index of active array
                     3);           // counts of vertex

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