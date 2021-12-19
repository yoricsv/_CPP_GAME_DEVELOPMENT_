#include <iostream>

#include "MathFunctions.h"
#include "TutorialConfig.h"                                     // generated header by CMake


int main (int argc, char * argv[])
{
    if (argc < 2)
    {
        std::cout << argv[0]
                  << " Version " << Tutorial_VERSION_MAJOR
                  << "." << Tutorial_VERSION_MINOR
                  << std::endl;
#ifdef CMD_ARGS
        return EXIT_FAILURE;
    }

    // convert input to double
    const double input_value = std::stod(argv[1]);
#else
    }

    double input_value;

    std::cout << "Enter a number: ";
    std::cin  >> input_value;
#endif

    const double result = math_functions::sqrt(input_value);

    std::cout   << "The sqrt of "   << input_value
                << " is "           << result
            << std::endl;

    return std::cout.good() ? EXIT_SUCCESS : EXIT_FAILURE;
}