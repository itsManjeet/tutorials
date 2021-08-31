#include <bits/stdc++.h>
using namespace std;

#include <GL/glew.h>
#include <GLFW/glfw3.h>

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

    while (!glfwWindowShouldClose(window))
    {

        glClear(GL_COLOR_BUFFER_BIT);

        /**
         *             (0.0, 1.0)
         * 
         *  (-1.0, 0.0)         (1.0, 0.0)
         */
        glBegin(GL_TRIANGLES);
            glVertex2f(0.0f, 1.0f);
            glVertex2f(-1.0f, 0.0f);
            glVertex2f(1.0f, 0.0f);
        glEnd();

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}