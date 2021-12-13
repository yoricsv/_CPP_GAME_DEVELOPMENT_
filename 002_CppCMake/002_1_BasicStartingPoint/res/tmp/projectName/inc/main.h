#pragma once

#ifndef MAIN_H
#define MAIN_H

#include <unistd.h>
#include <cstdlib>

const int STDOUT_FILENO = 1;

constexpr auto word = "Hello, world!\n";

#ifndef USE_GET_LENGTH_FUNCTION

    int print(const char * str, int length)
    {
        return write(STDOUT_FILENO, str, length);
    }

#else

    int getStringLength(const char * string)
    {
        int counter = 0;

        while (string[counter] != '\0')
        {
            counter++;
        }

        return counter;
    }

    int print(const char * str)
    {
        return write(STDOUT_FILENO, str, getStringLength(str));
    }

#endif

#endif // MAIN_H