#include "iostream"

#include "TutorialConfig.h"

int main (int argc, char * argv[])
{
    /**
     * If the number of arguments (argc) is less than 2,
     * the if statement must return app name and version, because
     * the first element is the application path (argv[0]), and
     * the second is the version (argv[1])
     */

    if (argc < 2)
    {
        std::cout << argv[0]
                  << " Version "    << Tutorial_VERSION_MAJOR
                  << "."            << Tutorial_VERSION_MINOR
            << std::endl;

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}