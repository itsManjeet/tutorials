#include <bits/stdc++.h>
using namespace std;

#include <GL/glew.h>
#include <GLFW/glfw3.h>

/**
 * 
 **/
unsigned int
create_shader(string const &vertex_shader,
              string const &fragment_shader)
{

    auto compile_shader = [](string const &source, uint type) -> uint
    {
        uint id = glCreateShader(type);
        char const *src = source.c_str();
        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);

        int result;
        glGetShaderiv(id, GL_COMPILE_STATUS, &result);
        if (!result)
        {
            int len;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
            char *mesg = new char[len];
            glGetShaderInfoLog(id, len, &len, mesg);

            cout << "Error! Failed to compile" << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " failed" << endl;
            cout << mesg << endl;

            glDeleteShader(id);
            return 0;
        }

        return id;
    };

    auto program = glCreateProgram();
    auto v_shader_id = compile_shader(vertex_shader, GL_VERTEX_SHADER);
    auto f_shader_id = compile_shader(fragment_shader, GL_FRAGMENT_SHADER);

    glAttachShader(program, v_shader_id);
    glAttachShader(program, f_shader_id);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(v_shader_id);
    glDeleteShader(f_shader_id);

    return program;
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

    string vertex_shared =
        "#version 330 core\n"                      // Version of opengl
        "layout(location = 0) in vec4 position;\n" // use starting index 0 of vertex as a Vector4 and store in "position" variable
        "void main() {\n"
        "  gl_Position = position;\n" // set gl_Position i.e. vertex
        "}\n";

    string fragment_shared =
        "#version 330 core\n"
        "layout(location = 0) out vec4 color;\n"
        "void main() {\n"
        "   color = vec4(1.0, 1.0, 0.0, 1.0);\n" // set color as RED = 1.0, GREEN = 1.0, BLUE = 0.0, ALPHA = 1.0
        "}\n";

    auto shader = create_shader(vertex_shared, fragment_shared);
    glUseProgram(shader);

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