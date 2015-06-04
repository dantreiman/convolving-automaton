#include <stdio.h>
#include "Engine.h"

int main(int argc, char* argv[])
{
    printf("Hello world\n");
    ca::Engine engine(ca::Size(2048, 2048));
    engine.Init();
    engine.TestPerformance();
    return 0;
}
