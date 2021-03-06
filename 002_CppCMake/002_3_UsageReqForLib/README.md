## [_GAMEDEV_][gamedev] > [_CMake_][CMake] > **Step 3**: *Adding Usage Requirements for a Library*

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
[stp1]:    ../002_1_BasicStartingPoint/README.md
[stp2]:    ../002_2_AddingLibrary/README.md
[stp3]:    README.md
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

# <p align = center><b>002_3_UsageReqForLib</b></p>

Usage requirements allow for far better control over a library or executable's link and include line while also giving more control over the transitive property of targets inside CMake. The primary commands that leverage usage requirements are:

* `target_compile_definitions()`
* `target_compile_options()`
* `target_include_directories()`
* `target_link_libraries()`

Let's refactor our code from Adding a Library to use the modern CMake approach of usage requirements. We first state that anybody linking to **MathFunctions** needs to include the current source directory, while **MathFunctions** itself doesn't. So this can become an `INTERFACE` usage requirement.

Remember `INTERFACE` means things that consumers require but the producer doesn't. *Add* the following lines *to the end* of ***MathFunctions/CMakeLists.txt***:

### MathFunctions/CMakeLists.txt

```cmake
target_include_directories(
      MathFunctions
   INTERFACE
      ${CMAKE_CURRENT_SOURCE_DIR}
)
```

Now that we've specified usage requirements for **MathFunctions** we can safely remove our uses of the `EXTRA_INCLUDES` variable from the *top-level* ***CMakeLists.txt***, here:

### CMakeLists.txt

```cmake
if(USE_MYMATH)
   add_subdirectory(MathFunctions)
   list(
      APPEND
         EXTRA_LIBS
            MathFunctions
)
endif()
```

And here:

### CMakeLists.txt

```cmake
target_include_directories(
      Tutorial
   PUBLIC
      ${PROJECT_BINARY_DIR}
)
```

Once this is done, run the **cmake** executable or the **cmake-gui** to configure the project and then build it with your chosen build tool or by using `cmake --build .` from the build directory.

---