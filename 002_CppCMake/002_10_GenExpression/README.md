## [_CMAKE_][CMake] > **Step 10: Adding Generator Expressions**

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

# <p align = center><b>002_10_GenExpression<b></p>

**Generator expressions** are evaluated during build system generation to produce information specific to each build configuration.

**Generator expressions** are allowed in the context of many target properties, such as `LINK_LIBRARIES`, `INCLUDE_DIRECTORIES`, `COMPILE_DEFINITIONS` and *others*. They may also be used when using commands to populate those properties, such as `target_link_libraries()`, `target_include_directories()`, `target_compile_definitions()` and *others*.

**Generator expressions** may be used to enable conditional linking, conditional definitions used when compiling, conditional include directories and more. The conditions may be based on the build configuration, target properties, platform information or any other queryable information.

There are different types of **generator expressions** including Logical, Informational, and Output expressions.

Logical expressions are used to create conditional output. The basic expressions are the 0 and 1 expressions. A `$<0:...>` results in the empty string, and `<1:...>` results in the content of `...`. They can also be nested.

A common usage of **generator expressions** is to conditionally add compiler flags, such as those for language levels or warnings. A nice pattern is to associate this information to an `INTERFACE` target allowing this information to propagate. Let's start by constructing an `INTERFACE` target and specifying the required C++ standard level of **11** instead of using `CMAKE_CXX_STANDARD`.

So the following code:

### CMakeLists.txt
```cmake
# specify the C++ standard
   set(CMAKE_CXX_STANDARD          11  )
   set(CMAKE_CXX_STANDARD_REQUIRED True)
```

Would be replaced with:

### CMakeLists.txt
```cmake
add_library(
   tutorial_compiler_flags
      INTERFACE
)
target_compile_features(
      tutorial_compiler_flags
   INTERFACE
      cxx_std_11)
```

> ***NOTE***: This upcoming section will require a change to the `cmake_minimum_required()` usage in the code. The Generator Expression that is about to be used was introduced in 3.15. Update the call to require that more recent version:

### CMakeLists.txt
```cmake
cmake_minimum_required(VERSION 3.15)
```

Next we add the desired compiler warning flags that we want for our project. As warning flags vary based on the compiler we use the `COMPILE_LANG_AND_ID` generator expression to control which flags to apply given a language and a set of compiler ids as seen below:

### CMakeLists.txt
```cmake
   set(gcc_like_cxx
         "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU>"
   )
   set(msvc_cxx
         "$<COMPILE_LANG_AND_ID:CXX,MSVC>"
   )
target_compile_options(
      tutorial_compiler_flags
   INTERFACE
      "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>>"
      "$<${msvc_cxx}:$<BUILD_INTERFACE:-W3>>"
)
```

Looking at this we see that the warning flags are encapsulated inside a `BUILD_INTERFACE` condition. This is done so that consumers of our installed project will not inherit our warning flags.

**Exercise**: Modify ***MathFunctions/CMakeLists.txt*** so that all targets have a `target_link_libraries()` call to `tutorial_compiler_flags`.

---