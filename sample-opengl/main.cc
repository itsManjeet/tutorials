#include <bits/stdc++.h>
using namespace std;

#include <GL/glut.h>

int main(int ac, char **av)
{
    glutInit(&ac, av);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(1200, 800);
    glutInitWindowPosition(0, 0);

    glutCreateWindow("Window");
    glClearColor(0.0, 0.0, 0.0, 1.0);

    glutDisplayFunc(
        []()
        {
            glClear(GL_COLOR_BUFFER_BIT);
            glBegin(GL_TRIANGLES);

            // red
            glColor3f(1, 0, 0);
            glVertex2f(-0.8, -0.8);

            glColor3f(1, 1, 0);
            glVertex2f(0.8, -0.8);

            glColor3f(1, 0, 1);
            glVertex2f(0, 0.8);

            glEnd();
            glutSwapBuffers();
        });

    glutMainLoop();
}