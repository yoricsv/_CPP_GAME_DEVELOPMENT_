#include "main.h"

int main()
{
    Engine engine{};

    engine.init("Windows name");

    while (engine.isActive())
    {
        engine.update();
    }
    
    return 0;
}