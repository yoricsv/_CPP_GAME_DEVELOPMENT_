#include <Engine.h>

int main(int argc, char * argv[])
{
    Engine engine{};

    engine.init("Windows name");

    while (engine.isActive())
    {
        engine.update();
    }

    return  0; //exit_code == -1 || exit_code != getStringLength(word) ? EXIT_FAILURE : EXIT_SUCCESS;
}

