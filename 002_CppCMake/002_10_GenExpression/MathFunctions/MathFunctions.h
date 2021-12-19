#pragma once
#ifndef MATH_FUNCTIONS_H
#define MATH_FUNCTIONS_H

#include <iostream>

#if defined(_WIN32)                             // for Windows OS
    #if defined(EXPORTING_MY_MATH)
        #define DECLSPEC __declspec(dllexport)
    #else
        #define DECLSPEC __declspec(dllimport)
    #endif
#else                                           // for other OS
    #define DECLSPEC
#endif

namespace math_functions
{
    double DECLSPEC sqrt(double input_value);
}

#endif // MATH_FUNCTIONS_H
