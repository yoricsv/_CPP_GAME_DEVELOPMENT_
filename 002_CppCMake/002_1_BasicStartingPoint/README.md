## [_GAMEDEV_][gamedev] > [_CMake_][CMake] > **Step 1: A Basic Starting Point**

### <p align=center>[Step 1][stp1] | [Step 2][stp2] | [Step 3][stp3] | [Step 4][stp4] | [Step 5][stp5] | [Step 6][stp6] <br/> [Step 7][stp7] | [Step 8][stp8] | [Step 9][stp9] | [Step 10][stp10] | [Step 11][stp11] | [Step 12][stp12]  </p>

<!--
* [_GAMEDEV_][gamedev]
* [_CMAKE_][CMake]
* [Step 1][stp1]
* [Step 2][stp2]
* [Step 3][stp3]
* [Step 4][stp4]
* [Step 5][stp5]
* [Step 6][stp6]
* [Step 7][stp7]
* [Step 8][stp8]
* [Step 9][stp9]
* [Step 10][stp10]
* [Step 11][stp11]
* [Step 12][stp12]
-->

[gamedev]: ../../README.md
[CMake]:   ../README.md
[stp1]:    README.md
[stp2]:    ../002_2_AddingLibrary/README.md
[stp3]:    ../002_3_UsageReqForLib/README.md
[stp4]:    ../002_4_InstallAndTest/README.md
[stp5]:    ../002_5_SysIntrospection/README.md
[stp6]:    ../002_6_ComFileGen/README.md
[stp7]:    ../002_7_BuildInstall/README.md
[stp8]:    ../002_8_Dashboard/README.md
[stp9]:    ../002_9_StaticShared/README.md
[stp10]:   ../002_10_GenExpression/README.md
[stp11]:   ../002_11_ExportConfig/README.md
[stp12]:   ../002_12_PackDebRel/README.md

---
<!-- ---------------------------------- * Navigation * ---------------------------------- -->

# <p align = center><b>002_1_BasicStartingPoint</b></p>

The most basic project is an executable built from source code files. For simple projects, a three line `CMakeLists.txt` file is all that is required. This will be the starting point for our tutorial. Create a `CMakeLists.txt` file in the **Step1** directory that looks like:

### CMakeLists.txt

```cmake
cmake_minimum_required(VERSION 3.10)

# set the project name
project(
        Tutorial
)

# add the executable
add_executable(
        Tutorial
        tutorial.cxx
)
```

> ***Note***: that this example uses lower case commands in the `CMakeLists.txt` file. Upper, lower, and mixed case commands are supported by CMake. The source code for `tutorial.cxx` is provided in the **Step1** directory and can be used to compute the square root of a number.

---

## Build and Run

That's all that is needed - we can build and run our project now! First, run the ***cmake*** executable or the ***cmake-gui*** to configure the project and then build it with your chosen build tool.

*For example*, from the command line we could navigate to the `Help/guide/tutorial` directory of the CMake source code tree and create a build directory:

```bash
mkdir Step1_build
```

Next, navigate to the build directory and run CMake to configure the project and generate a native build system:

```bash
cd Step1_build
cmake ../Step1
```

Then call that build system to actually **compile**/**link** the project:

```bash
cmake --build .
```

Finally, try to use the newly built `Tutorial` with these commands:

```bash
Tutorial 4294967296
Tutorial 10
Tutorial
```

---

## Adding a Version Number and Configured Header File

The first feature we will add is to provide our executable and project with a version number. While we could do this exclusively in the source code, using `CMakeLists.txt` provides more flexibility.

First, modify the `CMakeLists.txt` file to use the `project()` command to set the project name and version number.

### CMakeLists.txt

```cmake
cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(
    Tutorial
        VERSION 1.0
)
```

Then, configure a header file to pass the version number to the source code:

### CMakeLists.txt

```cmake
configure_file(
        TutorialConfig.h.in
        TutorialConfig.h
)
```

Since the configured file will be written into the binary tree, we must add that directory to the list of paths to search for include files. Add the following lines to the end of the `CMakeLists.txt` file:

### CMakeLists.txt

```cmake
target_include_directories(
        Tutorial
    PUBLIC
        "${PROJECT_BINARY_DIR}"
)
```

Using your favorite editor, create `TutorialConfig.h.in` in the source directory with the following contents:

### Create TutorialConfig.h.in via Powershell

```shell
New_Item TutorialConfig.h.in
```

or

```shell
New-Item -Path 'C:\<pathToProjectFolder>\TutorialConfig.h.in' -Force
```

### Create TutorialConfig.h.in via Terminal (*nix)

```shell
> TutorialConfig.h.in
```
or
```shell
touch TutorialConfig.h.in
```

### TutorialConfig.h.in

```cpp
// the configured options and settings for Tutorial
#define Tutorial_VERSION_MAJOR @Tutorial_VERSION_MAJOR@
#define Tutorial_VERSION_MINOR @Tutorial_VERSION_MINOR@
```

When CMake configures this header file the values for `@Tutorial_VERSION_MAJOR@` and `@Tutorial_VERSION_MINOR@` will be replaced.

Next modify `tutorial.cxx` to include the configured header file, `TutorialConfig.h`.

### tutorial.cxx

```cpp
#include "TutorialConfig.h"
```

Finally, let's print out the executable name and version number by updating `tutorial.cxx` as follows:

### tutorial.cxx

```cpp
/**
 * If the number of arguments (argc) is less than 2,
 * the if statement must return FAILURE, because
 * the first element is the application path (argv [0]), and
 * the second is the version (argv [1])
 */
if (argc < 2)
{
    // report version
    std::cout << argv[0] 
              << " Version "
              << Tutorial_VERSION_MAJOR 
              << "."
              << Tutorial_VERSION_MINOR 
              << std::endl;

    std::cout << "Usage: "
              << argv[0]
              << " number"
              << std::endl;

    return 1;
}
```

---
<br/>

## Specify the C++ Standard

Next let's add some C++11 features to our project by replacing `atof` with `std::stod` in `tutorial.cxx`. At the same time, **remove** `#include <cstdlib>`.

### tutorial.cxx

```cpp
const double inputValue = std::stod(argv[1]);
```

We will need to explicitly state in the CMake code that it should use the correct flags. The easiest way to enable support for a specific C++ standard in CMake is by using the **CMAKE_CXX_STANDARD** variable. For this tutorial, set the **CMAKE_CXX_STANDARD** variable in the `CMakeLists.txt` file to **11** and **CMAKE_CXX_STANDARD_REQUIRED** to **True**. Make sure to add the **CMAKE_CXX_STANDARD** declarations above the call to `add_executable()`.

### CMakeLists.txt

```cmake
cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(
    Tutorial
        VERSION 1.0
)

# specify the C++ standard
    set(CMAKE_CXX_STANDARD          11  )
    set(CMAKE_CXX_STANDARD_REQUIRED True)
```

---
<br/>

## Rebuild

Let's build our project again. We already created a build directory and ran CMake, so we can skip to the build step:

```bash
cd Step1_build
cmake --build .
```

Now we can try to use the newly built `Tutorial` with same commands as before:

```bash
Tutorial 4294967296
Tutorial 10
Tutorial
```
Check that the version number is now reported when running the executable without any arguments.

---

<!--
## For maximum optimization,  of the "Hello, World!" app decided to use system calls, but OS Windows doesn't support the syscall.h file. To solve this problem, I'm using the `write()` function from the unistd.h library with output validation.

> ***NOTE***: This project has two options that directly affect performance:</br>
> 1. You can use a function to count the characters in a string, but this will have a negative effect because you have to use a loop. *(To activate this feature, you need to uncomment the  `COMPILE_DEFINITIONS  USE_GET_LENGTH_FUNCTION` line in the CMakeLists.txt file)*
> 2. For maximum performance, the string length is hardcoded, but this isn't checked!

### The Write() function returns:

* On SUCCESS, is returned the TOTAL NUMBER of written characters.<br/>
* If a writing ERROR occurs, is returned a NEGATIVE number !!!!<br/>

### Requirements:

**Compiler<br/> / Build System** | **Standard<br/> / Version**
--: | :--
**gcc** | v.6.3.0
**MinGW** | v.3.82.90
**C++ Standard** | 2017
**CMake** | v.3.20
-->
<!--**clang** | v.11.0.0 --> <!--"C:\Program Files\LLVM\bin"-->
<!--**g++** | v.6.3.0 -->    <!--"C:\MinGW_Compiler_C-C++\bin"-->
<!--
### Dependencies:

**Library** | **Used functions, definitions, constants:**
--: | :--
**unistd.h** | *write()*
**cstdlib** | *EXIT_FAILURE, EXIT_SUCCESS*

### Additional libraries

**Library** | **Version**
--: | :--
SDL2 | v.2.0.16 (stable)
-->

<!--
## Build the project

> **NOTE**:</br> To download and install the latest version of:</br>
> **CMake** use next link: ([*CMake download*][cmake])</br> 
> **MinGW (g++)** toolchain use ([*MinGW download*][mingw])

## **TIP:** To compile and build the project for **Windows OS**

1. Run the **CommandPrompt** or **PowerShell**:
   * `[Win]+[R]` -> Type: *`cmd`* or *`pwsh`* -> `[Shift]+[Ctrl]+[Enter]` *(to get admin rights)*
2. Use the `cd` command to open the root of the project

### *(For Example:)*

```bash
cd %USERPROFILE%\Downloads\001_2_CppHelloWorld_std17
```

3. To keep the source code clean you should do *"out-of-source"* builds.

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

4. To run the target open `\out` folder *(will be generated by CMake)* and run executable file.

```bash
cd ..\out
HelloWorld.exe
```

## **TIP:** To compile and build the project for **\*nix OS**

1. Run the **Terminal**: `[Ctrl]+[Alt]+[T]`
2. Use the `cd` command to open the root of the project

### *(For Example:)*

```bash
cd $home/001_2_CppHelloWorld_std17
```

3. To keep the source code clean you should do *"out-of-source"* builds.

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

4. To run the target open `/out` folder *(will be generated by CMake)* and run executable file.

```bash
cd ../out
HelloWorld
```

### The result:

![Result][result]

repo URL:

```
https://github.com/yoricsv/001_2_CppHelloWorld_std17-O2.git
```

---

* [*CMake download*][cmake]
* [*MinGW download*][mingw]
* [Result][result]

[cmake]: https://cmake.org/download
[mingw]: https://www.mingw-w64.org/downloads
[result]: res/img/cpp_helloworld_check_cout.png
-->
