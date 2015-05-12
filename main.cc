#include <stdio.h>
#include "Engine.h"

//#define GLFW_INCLUDE_GLU

int main(int argc, char* argv[])
{
    printf("Hello world\n");
    ca::Engine engine(ca::Size(512, 512));
    engine.Init();
    engine.RunLoop();
    return 0;
}
