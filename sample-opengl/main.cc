#include <bits/stdc++.h>
using namespace std;

#include <GL/glut.h>

void displayFunc()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_TRIANGLES);
    /**
     *                    (0.0, 1.0) (GREEN)
     * 
     * 
     *  (-1.0, 0.0) (RED)               (1.0, 0.0) (BLUE)
     */

        glColor3f(1, 0, 0); // RED
        glVertex2f(-1.0, 0.0);

        glColor3f(0, 1, 0); // GREEN
        glVertex2f(0.0, 1.0);

        glColor3f(0, 0, 1); // BLUE
        glVertex2f(1.0, 0.0);

    glEnd();

    glFlush();
}

int main(int ac, char **av)
{
    glutInit(&ac, av);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(400, 500);
    int window = glutCreateWindow("Sample");

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glutDisplayFunc(displayFunc);

    glutMainLoop();

    return 0;
}