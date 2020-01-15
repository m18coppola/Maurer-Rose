#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include "CoppLoader.h"
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/freeglut.h>
#include <math.h>

#define BUFFER_OFFSET(bytes) ((GLvoid*) (bytes))

typedef struct {
    GLfloat x;
    GLfloat y;
} point2;

const float DegreesToRadians = M_PI / 180.0;

void init();
void display();


void
init()
{

    point2 verticies[3] = {
        {.x = -1.0, .y = -1.0},
        {.x =  0.0, .y =  1.0},
        {.x =  1.0, .y = -1.0}
    };

    point2 points[361];

    int n = 7;
    int d = 29;

    for(int i = 0; i < 361; i++){

        GLfloat k = i * d;
        GLfloat r = sin(n*k*DegreesToRadians);
        GLfloat x = r * cos(k * DegreesToRadians);
        GLfloat y = r * sin(k * DegreesToRadians);
        points[i].x = x;
        points[i].y = y;
    }



    GLuint program = InitShader("shader.glsl","fshader.glsl");
    glUseProgram(program);

    glLineWidth(1.0);


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
    glDrawArrays(GL_LINE_LOOP, 0, 361);
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

    glutCreateWindow("OpenGL Example");

    glewInit();
    init();
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}



