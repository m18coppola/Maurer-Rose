#include <stdio.h>
#include <stdlib.h>

#include "CoppLoader.h"

int
main()
{
    char * source = readShaderSource("test.glsl");
    printf("%s",source);
    free(source);
    return 0;
}
