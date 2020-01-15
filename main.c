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

typedef struct {
    GLfloat r;
    GLfloat g;
    GLfloat b;
} color;

color red  = {1.0, 0.0, 0.0};
color blue = {0.0, 0.0, 1.0};

const float DegreesToRadians = M_PI / 180.0;

void init();
void display();


void
init()
{
    point2 rose[361];
    point2 path[361];
    color roseColor[361];
    color pathColor[361];

    int n = 6;
    int d = 71;

    for(int i = 0; i < 361; i++){

        GLfloat k = i * d;
        GLfloat r = sin(n*k*DegreesToRadians);
        GLfloat x = r * cos(k * DegreesToRadians);
        GLfloat y = r * sin(k * DegreesToRadians);
        rose[i].x = x;
        rose[i].y = y;

        roseColor[i] = red;
    }

    for(int i = 0; i < 361; i++){

        GLfloat k = i;
        GLfloat r = sin(n*k*DegreesToRadians);
        GLfloat x = r * cos(k * DegreesToRadians);
        GLfloat y = r * sin(k * DegreesToRadians);
        path[i].x = x;
        path[i].y = y;

        pathColor[i] = blue;
    }



    GLuint program = InitShader("shader.glsl","fshader.glsl");
    glUseProgram(program);




    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rose) + sizeof(path) + sizeof(roseColor) + sizeof(pathColor), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(rose), rose);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(rose), sizeof(path), path);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(rose) + sizeof(path), sizeof(roseColor) , roseColor);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(rose) + sizeof(path) + sizeof(roseColor), sizeof(pathColor), pathColor);


    GLuint loc = glGetAttribLocation(program, "vPosition");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

    GLuint loc2 = glGetAttribLocation(program, "vColor");
    glEnableVertexAttribArray(loc2);
    glVertexAttribPointer(loc2, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(rose)+sizeof(path)));


    glClearColor(1.0, 1.0, 1.0, 1.0);


}

void
display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(1.0);
    glDrawArrays(GL_LINE_LOOP, 0, 361);
    glLineWidth(2.0);
    glDrawArrays(GL_LINE_LOOP, 361, 361);
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



