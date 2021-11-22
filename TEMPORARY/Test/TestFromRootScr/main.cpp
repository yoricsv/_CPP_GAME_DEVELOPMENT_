#include <iostream>
// #include <syscalls.h>
// #include <unistd.h>

// int print(const char* str, int size)
// {
//     int exit_code = 0;
//     syscall(SYS_write, 1, str, size);
//     return exit_code;
// }

constexpr auto word = "Hello, world!\n";
int main(int argc, char *argv[])
{

    // print(word, 14);

    // // return printf(word) < 0 ? EXIT_SUCCESS : EXIT_FAILURE;//2


   std::cout << word ; //1
   return std::cout.good() ? EXIT_SUCCESS : EXIT_FAILURE; //1
}