#include <bits/stdc++.h>
using namespace std;

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shaders.hh"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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
        -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f}; // 3

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

    unsigned int arr_buf_id;
    glGenVertexArrays(1, &arr_buf_id);
    glBindVertexArray(arr_buf_id);

    unsigned int ver_buf_id;
    glGenBuffers(1, &ver_buf_id);
    glBindBuffer(GL_ARRAY_BUFFER, ver_buf_id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(pos), pos, GL_STATIC_DRAW);

    unsigned int idx_buf_id;
    glGenBuffers(1, &idx_buf_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idx_buf_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    unsigned int shader_prog_id;
    shader_prog_id = gen_shader_program("sample-opengl/shaders");
    if (shader_prog_id == 0)
        cerr << "Error! in shader program" << endl;

    glUseProgram(shader_prog_id);

    GLint pos_attrib = glGetAttribLocation(shader_prog_id, "position");
    glEnableVertexAttribArray(pos_attrib);
    glVertexAttribPointer(pos_attrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), 0);

    GLint color_attrib = glGetAttribLocation(shader_prog_id, "color");
    glEnableVertexAttribArray(color_attrib);
    glVertexAttribPointer(color_attrib, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *)(2 * sizeof(float)));

    GLint tex_attrib = glGetAttribLocation(shader_prog_id, "texcoord");
    glEnableVertexAttribArray(tex_attrib);
    glVertexAttribPointer(tex_attrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *)(5 * sizeof(float)));

    unsigned int texture;
    glGenTextures(2, &texture);

    int width, height;
    unsigned char *data;
    glBindTexture(GL_TEXTURE_2D, texture);
    data = stbi_load("input.png", &width, &height, 0, STBI_rgb);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);
    glUniform1i(glGetUniformLocation(shader_prog_id, "tex"), 0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    while (!glfwWindowShouldClose(window))
    {

        glClear(GL_COLOR_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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