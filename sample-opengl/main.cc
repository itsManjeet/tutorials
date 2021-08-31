#include <bits/stdc++.h>
using namespace std;

#include <GL/glut.h>

void displayFunc()
{
}
int main(int ac, char **av)
{
    glutInit(&ac, av);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(400, 500);
    int window = glutCreateWindow("Sample");

    glClearColor(0.0, 0.0, 0.0, 0.0);
    gluOrtho2D(0, 400, 500, 0);
    glutDisplayFunc(displayFunc);

    glutMainLoop();

    return 0;
}