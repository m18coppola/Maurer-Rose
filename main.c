#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include "CoppLoader.h"
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/freeglut.h>

#define BUFFER_OFFSET(bytes) ((GLvoid*) (bytes))

const int NumPoints = 50000;

typedef struct {
    GLfloat x;
    GLfloat y;
} point2;

void init();
void display();


void init()
{

    point2 points[NumPoints];

    //A triangle

    point2 verticies[3] = {
        {.x = -1.0, .y = -1.0},
        {.x =  0.0, .y =  1.0},
        {.x =  1.0, .y = -1.0}
    };

    //arbitrary point in triangle
    points[0].x = 0.25;
    points[0].y = 0.50;
    //compute and store NumPoints-1 new points
    for(int k = 1; k < NumPoints; k++)
    {
        int j = rand() % 3; //pick a vertex at random

        //compute the point halfway between selected vertex and previous point
        GLfloat prev_x = points[k-1].x;
        GLfloat prev_y = points[k-1].y;
        GLfloat vert_x = verticies[j].x;
        GLfloat vert_y = verticies[j].y;

        GLfloat new_x = (prev_x + vert_x)/2.0;
        GLfloat new_y = (prev_y + vert_y)/2.0;

        points[k].x = new_x;
        points[k].y = new_y;
    }

    GLuint program = InitShader("shader.glsl","fshader.glsl");
    glUseProgram(program);


    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);


    GLuint loc = glGetAttribLocation(program, "vPosition");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glClearColor(1.0, 1.0, 1.0, 1.0);


}

void
display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_POINTS, 0, NumPoints);
    glFlush();
}

int
main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(512, 512);

    glutInitContextVersion(3, 2);
    glutInitContextProfile(GLUT_CORE_PROFILE);

    glutCreateWindow("example");

    glewInit();
    init();
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}



