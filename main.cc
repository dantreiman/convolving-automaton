#include "Engine.h"

int main(int argc, char* argv[]) {
    const bool fullscreen = false;
    ca::Engine engine(ca::Size(512, 512), fullscreen);
    engine.Init();
    engine.RunLoop();
    return 0;
}
