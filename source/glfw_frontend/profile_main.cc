#include <stdio.h>
#include "Engine.h"

int main(int argc, char* argv[])
{
    printf("Hello world\n");
    ca::Engine engine(ca::Size(1024, 1024), false);
    engine.Init();
    engine.TestPerformance();
    return 0;
}
