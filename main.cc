#include <stdio.h>
#include "Engine.h"

int main(int argc, char* argv[])
{
    printf("Hello world\n");
    ca::Engine engine(ca::Size(512, 512));
    engine.Init();
    engine.RunLoop();
    return 0;
}
