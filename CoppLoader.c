#include <GL/glew.h>
#include <GL/glut.h>
#include <stdio.h>

char * readShaderSource(char* shaderPath);
GLuint compileShader(GLenum type, char *source);
GLuint InitShader(char* vShaderPath, char* fShaderPath);

char *
readShaderSource(char* shaderPath)
{
    char *buffer = 0;
    long length;
    FILE *fp;

    fp = fopen(shaderPath, "r");
    if (fp == NULL) {
        printf("fuck");
    }
    fseek (fp, 0, SEEK_END);
    length = ftell (fp);
    fseek (fp, 0, SEEK_SET);
    buffer = malloc (length);
    if (!buffer)  {
        printf("Failed to allocate memory for source!");
    }
    fread (buffer, 1, length, fp);
    fclose (fp);

    //printf("File contents:\n%s", buffer);
    buffer[length] = '\0';
    return buffer;
}

GLuint
compileShader(GLenum type, char *sourcePath)
{

    GLuint s = glCreateShader(type);
    char *source = readShaderSource(sourcePath);
    printf("%s\n",source);
    printf("nc1\n");
    glShaderSource(s, 1, (GLchar**)&source, NULL);
    printf("nc2\n");
    glCompileShader(s);
    printf("nc3\n");
    GLint status;
    printf("Compiler status: %d\n", status);
    glGetShaderiv(s, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE) {
        char errlog[256];
        glGetShaderInfoLog(s, 512, NULL, errlog);
        printf("Failed to compile %s:\n%s\n", source, errlog);
    }
    free(source);
    return s;
}

GLuint
InitShader(char* vShaderPath, char* fShaderPath)
{
    GLuint vShader = compileShader(GL_VERTEX_SHADER, vShaderPath);
    GLuint fShader = compileShader(GL_FRAGMENT_SHADER, fShaderPath);

    GLuint sp = glCreateProgram();
    glAttachShader(sp, vShader);
    glAttachShader(sp, fShader);
    glLinkProgram(sp);

    return sp;
}
