## [_CMAKE_][CMake] > **Step 2: Adding a Library**

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

# <p align = center><b>002_2_AddingLibrary<b></p>

Now we will add a library to our project. This library will contain our own implementation for computing the square root of a number. The executable can then use this library instead of the standard square root function provided by the compiler.

For this tutorial we will put the library into a subdirectory called **MathFunctions**. This directory already contains a header file, ***MathFunctions.h***, and a source file ***mysqrt.cxx***. The source file has one function called `mysqrt` that provides similar functionality to the compiler's `sqrt` function.

Add the following one line ***CMakeLists.txt*** file to the **MathFunctions** directory:

### MathFunctions/CMakeLists.txt
```cmake
add_library(MathFunctions mysqrt.cxx)
```
To make use of the new library we will add an `add_subdirectory()` call in the top-level ***CMakeLists.txt*** file so that the library will get built. We add the new library to the executable, and add **MathFunctions** as an include directory so that the ***mysqrt.h*** header file can be found. The last few lines of the top-level ***CMakeLists.txt*** file should now look like:

### CMakeLists.txt
```cmake
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

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
target_include_directories(
      Tutorial
   PUBLIC
      "${PROJECT_BINARY_DIR}"
      "${PROJECT_SOURCE_DIR}/MathFunctions"
)
```

Now let us make the **MathFunctions** library optional. While for the tutorial there really isn't any need to do so, for larger projects this is a common occurrence. The first step is to add an option to the top-level ***CMakeLists.txt*** file.

### CMakeLists.txt
```cmake
option(
   USE_MYMATH
      "Use tutorial provided math implementation"  ON
)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file(
   TutorialConfig.h.in
      TutorialConfig.h
)
```
This option will be displayed in the **cmake-gui** and **ccmake** with a default value of **ON** that can be changed by the user. This setting will be stored in the cache so that the user does not need to set the value each time they run CMake on a build directory.

The next change is to make building and linking the **MathFunctions** library conditional. To do this, we will create an `if` statement which checks the value of the option. Inside the `if` block, put the `add_subdirectory()` command from above with some additional list commands to store information needed to link to the library and add the subdirectory as an include directory in the **Tutorial** *target*. The end of the *top-level* ***CMakeLists.txt*** file will now look like the following:

### CMakeLists.txt
```cmake
if(USE_MYMATH)
   add_subdirectory(MathFunctions)
   list(
      APPEND
         EXTRA_LIBS
            MathFunctions
   )
   list(
      APPEND
         EXTRA_INCLUDES
            "${PROJECT_SOURCE_DIR}/MathFunctions"
   )
endif()

# add the executable
add_executable(
   Tutorial
      tutorial.cxx
)

target_link_libraries(
      Tutorial
   PUBLIC
      ${EXTRA_LIBS}
)

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
target_include_directories(
      Tutorial
   PUBLIC
      "${PROJECT_BINARY_DIR}"
      ${EXTRA_INCLUDES}
)
```

> **NOTE**: the use of the variable `EXTRA_LIBS` to collect up any optional libraries to later be linked into the executable. The variable `EXTRA_INCLUDES` is used similarly for optional header files. This is a classic approach when dealing with many optional components, we will cover the modern approach in the next step.

The corresponding changes to the source code are fairly straightforward. First, in ***tutorial.cxx***, include the ***MathFunctions.h*** header if we need it:

### tutorial.cxx
```cpp
#ifdef USE_MYMATH
#  include "MathFunctions.h"
#endif
```

Then, in the same file, make `USE_MYMATH` control which square root function is used:

### tutorial.cxx
```cpp
#ifdef USE_MYMATH
  const double outputValue = mysqrt(inputValue);
#else
  const double outputValue = sqrt(inputValue);
#endif
```

Since the source code now requires `USE_MYMATH` we can add it to ***TutorialConfig.h.in*** with the following line:

### TutorialConfig.h.in
```cpp
#cmakedefine USE_MYMATH
```

**Exercise**: Why is it important that we configure ***TutorialConfig.h.in*** after the option for `USE_MYMATH`? What would happen if we inverted the two?

Run the **cmake** executable or the **cmake-gui** to configure the project and then build it with your chosen build tool. Then run the built Tutorial executable.

Now let's update the value of `USE_MYMATH`. The easiest way is to use the **cmake-gui** or **ccmake** if you're in the terminal. Or, alternatively, if you want to change the option from the command-line, try:

```bash
cmake ../Step2 -DUSE_MYMATH=OFF
```

Rebuild and run the tutorial again.

Which function gives better results, `sqrt` or `mysqrt`?

---