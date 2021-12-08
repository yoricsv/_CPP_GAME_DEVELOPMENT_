## [_CMAKE_][CMake] > **Step 9: Selecting Static or Shared Libraries**

## <p align=center>[Step 1][stp1] | [Step 2][stp2] | [Step 3][stp3] | [Step 4][stp4] | [Step 5][stp5] | [Step 6][stp6] <br/> [Step 7][stp7] | [Step 8][stp8] | [Step 9][stp9] | [Step 10][stp10] | [Step 11][stp11] | [Step 12][stp12]  </p>

<!--
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
[CMake]: ../../README.md
[stp1]: https://github.com/yoricsv/002_CppCMake/002_1_BasicStartingPoint.git
[stp2]: https://github.com/yoricsv/002_CppCMake/002_2_AddingLibrary.git
[stp3]: https://github.com/yoricsv/002_CppCMake/002_3_UsageReqForLib.git
[stp4]: https://github.com/yoricsv/002_CppCMake/002_4_InstallAndTest.git
[stp5]: https://github.com/yoricsv/002_CppCMake/002_5_SysIntrospection.git
[stp6]: https://github.com/yoricsv/002_CppCMake/002_6_ComFileGen.git
[stp7]: https://github.com/yoricsv/002_CppCMake/002_7_BuildInstall.git
[stp8]: https://github.com/yoricsv/002_CppCMake/002_8_Dashboard.git
[stp9]: https://github.com/yoricsv/002_CppCMake/002_9_StaticShared.git
[stp10]: https://github.com/yoricsv/002_CppCMake/002_10_GenExpression.git
[stp11]: https://github.com/yoricsv/002_CppCMake/002_11_ExportConfig.git
[stp12]: https://github.com/yoricsv/002_CppCMake/002_12_PackDebRel.git

---
<br/>
<!-- ---------------------------------- * Navigation * ---------------------------------- -->

# <p align = center><b>002_9_StaticShared<b></p>

In this section we will show how the `BUILD_SHARED_LIBS` variable can be used to control the default behavior of `add_library()`, and allow control over how libraries without an explicit type (`STATIC`, `SHARED`, `MODULE` or `OBJECT`) are built.

To accomplish this we need to add BUILD_SHARED_LIBS to the *top-level* ***CMakeLists.txt***. We use the `option()` command as it allows users to optionally select if the value should be `ON` or `OFF`.

Next we are going to refactor **MathFunctions** to become a real library that encapsulates using `mysqrt` or `sqrt`, instead of requiring the calling code to do this logic. This will also mean that `USE_MYMATH` will not control building **MathFunctions**, but instead will control the behavior of this library.

The first step is to update the starting section of the *top-level* ***CMakeLists.txt*** to look like:

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

# control where the static and shared libraries are built so that on windows
# we don't need to tinker with the path to run the executable
   set(
      CMAKE_ARCHIVE_OUTPUT_DIRECTORY
         "${PROJECT_BINARY_DIR}"
   )
   set(
      CMAKE_LIBRARY_OUTPUT_DIRECTORY
         "${PROJECT_BINARY_DIR}"
   )
   set(
      CMAKE_RUNTIME_OUTPUT_DIRECTORY
         "${PROJECT_BINARY_DIR}"
   )

option(
   BUILD_SHARED_LIBS
      "Build using shared libraries"   ON
)

# configure a header file to pass the version number only
configure_file(
   TutorialConfig.h.in
      TutorialConfig.h
)

# add the MathFunctions library
add_subdirectory(MathFunctions)

# add the executable
add_executable(
   Tutorial
      tutorial.cxx
)
target_link_libraries(
      Tutorial
   PUBLIC
      MathFunctions
)
```

Now that we have made **MathFunctions** always be used, we will need to update the logic of that library. So, in ***MathFunctions/CMakeLists.txt*** we need to create a SqrtLibrary that will conditionally be built and installed when `USE_MYMATH` is enabled. Now, since this is a tutorial, we are going to explicitly require that SqrtLibrary is built statically.

The end result is that ***MathFunctions/CMakeLists.txt*** should look like:

### MathFunctions/CMakeLists.txt
```cmake
# add the library that runs
add_library(
   MathFunctions
   MathFunctions.cxx
)

# state that anybody linking to us needs to include the current source dir
# to find MathFunctions.h, while we don't.
target_include_directories(
      MathFunctions
   INTERFACE
      ${CMAKE_CURRENT_SOURCE_DIR}
)

# should we use our own math functions
option(
   USE_MYMATH
      "Use tutorial provided math implementation"  ON
)

if(USE_MYMATH)
   target_compile_definitions(
         MathFunctions
      PRIVATE
         "USE_MYMATH"
   )

   # first we add the executable that generates the table
   add_executable(
      MakeTable
         MakeTable.cxx
   )

   # add the command to generate the source code
   add_custom_command(
      OUTPUT
         ${CMAKE_CURRENT_BINARY_DIR}/Table.h
      COMMAND
         MakeTable
            ${CMAKE_CURRENT_BINARY_DIR}/Table.h
      DEPENDS
         MakeTable
   )

   # library that just does sqrt
   add_library(
         SqrtLibrary
      STATIC
         mysqrt.cxx
         ${CMAKE_CURRENT_BINARY_DIR}/Table.h
   )

   # state that we depend on our binary dir to find Table.h
   target_include_directories(
         SqrtLibrary
      PRIVATE
         ${CMAKE_CURRENT_BINARY_DIR}
   )

   target_link_libraries(
         MathFunctions
      PRIVATE
         SqrtLibrary
   )
endif()

# define the symbol stating we are using the declspec(dllexport) when
# building on windows
target_compile_definitions(
      MathFunctions
   PRIVATE
      "EXPORTING_MYMATH"
)

# install rules
   set(
      installable_libs
         MathFunctions
   )

if(TARGET SqrtLibrary)
   list(
      APPEND
         installable_libs
            SqrtLibrary
   )
endif()

install(
   TARGETS
      ${installable_libs}
   DESTINATION
      lib
)

install(
   FILES
      MathFunctions.h
   DESTINATION
      include
)
```

Next, update ***MathFunctions/mysqrt.cxx*** to use the **mathfunctions** and **detail** namespaces:

### MathFunctions/mysqrt.cxx
```cpp
#include <iostream>

#include "MathFunctions.h"

// include the generated table
#include "Table.h"

namespace mathfunctions
{
   namespace detail
   {
      // a hack square root calculation using simple operations
      double mysqrt(double x)
      {
         if (x <= 0)
         {
            return 0;
         }

         // use the table to help find an initial value
         double result = x;
         
         if (x >= 1 && x < 10)
         {
            std::cout   << "Use the table to help find an initial value " << std::endl;
            
            result = sqrtTable[static_cast<int>(x)];
         }

         // do ten iterations
         for (int i = 0;
                  i < 10;
                  ++i
            )
         {
            if (result <= 0)
            {
               result = 0.1;
            }

            double delta = x - (result * result);

            result = result + 0.5 * delta / result;

            std::cout   << "Computing sqrt of " << x
                        << " to be "            << result
                        << std::endl;
         }

         return result;
      }
   }
}
```

We also need to make some changes in ***tutorial.cxx***, so that it no longer uses `USE_MYMATH`:

1. Always include ***MathFunctions.h***
2. Always use `mathfunctions::sqrt`
3. Don't include `cmath`

Finally, update ***MathFunctions/MathFunctions.h*** to use dll export defines:

### MathFunctions/MathFunctions.h
```cpp
#if defined(_WIN32)
   #if defined(EXPORTING_MYMATH)
      #define DECLSPEC __declspec(dllexport)
   #else
      #define DECLSPEC __declspec(dllimport)
   #endif
#else
   // non windows
   #define DECLSPEC
#endif

namespace mathfunctions
{
   double DECLSPEC sqrt(double x);
}
```

At this point, if you build everything, you may notice that linking fails as we are combining a static library without position independent code with a library that has position independent code. The solution to this is to explicitly set the `POSITION_INDEPENDENT_CODE` target property of SqrtLibrary to be `True` no matter the build type.

### MathFunctions/CMakeLists.txt
```cmake
# state that SqrtLibrary need PIC when the default is shared libraries
set_target_properties(
      SqrtLibrary
   PROPERTIES
      POSITION_INDEPENDENT_CODE
         ${BUILD_SHARED_LIBS}
)

target_link_libraries(
      MathFunctions
   PRIVATE
      SqrtLibrary
)
```

**Exercise**: We modified ***MathFunctions.h*** to use dll export defines. Using CMake documentation can you find a helper module to simplify this?

---