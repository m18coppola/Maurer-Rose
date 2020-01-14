#include <GL/glew.h>
#include <GL/glut.h>
#include <stdio.h>
#include "CoppLoader.h"

char* readShaderSource(char* shaderPath){
    char * buffer = 0;
    long length;
    FILE *fp;

    fp = fopen(shaderPath, "r");
    if(fp == NULL){
        printf("fuck");
    }
    fseek (fp, 0, SEEK_END);
    length = ftell (fp);
    fseek (fp, 0, SEEK_SET);
    buffer = malloc (length);
    if (!buffer)
    {
        printf("Failed to allocate memory for source!");
    }
    fread (buffer, 1, length, fp);
    fclose (fp);

    //printf("File contents:\n%s", buffer);
    return buffer;
}
