## [_CMAKE_][CMake] > **Step 12: Packaging Debug and Release**

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

# <p align = center><b>002_12_PackDebRel<b></p>

> ***NOTE***: This example is valid for single-configuration generators and will not work for multi-configuration generators (e.g. Visual Studio).

By default, CMake's model is that a build directory only contains a single configuration, be it Debug, Release, MinSizeRel, or RelWithDebInfo. It is possible, however, to setup CPack to bundle multiple build directories and construct a package that contains multiple configurations of the same project.

First, we want to ensure that the debug and release builds use different names for the executables and libraries that will be installed. Let's use ***d*** as the postfix for the debug executable and libraries.

Set `CMAKE_DEBUG_POSTFIX` near the beginning of the *top-level* ***CMakeLists.txt*** file:

### CMakeLists.txt
```cmake
set(CMAKE_DEBUG_POSTFIX d)

add_library(
   tutorial_compiler_flags
      INTERFACE
)
```

And the `DEBUG_POSTFIX` property on the tutorial executable:

### CMakeLists.txt
```cmake
add_executable(
   Tutorial
      tutorial.cxx
)
set_target_properties(
      Tutorial
   PROPERTIES
      DEBUG_POSTFIX
         ${CMAKE_DEBUG_POSTFIX}
)

target_link_libraries(
      Tutorial
   PUBLIC
      MathFunctions
)
```

Let's also add version numbering to the** MathFunctions** library. In ***MathFunctions/CMakeLists.txt***, set the `VERSION` and `SOVERSION` properties:

### MathFunctions/CMakeLists.txt
```cmake
set_property(
   TARGET
      MathFunctions
   PROPERTY
      VERSION
         "1.0.0"
)
set_property(
   TARGET
      MathFunctions
   PROPERTY
      SOVERSION
         "1"
)
```

From the **Step12** directory, create ***debug*** and ***release*** subbdirectories. The layout will look like:

```bash
- Step12
   - debug
   - release
```

Now we need to setup debug and release builds. We can use `CMAKE_BUILD_TYPE` to set the configuration type:

```bash
cd debug
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build .
cd ../release
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
```

Now that both the debug and release builds are complete, we can use a custom configuration file to package both builds into a single release. In the **Step12** directory, create a file called ***MultiCPackConfig.cmake***. In this file, first include the default configuration file that was created by the **cmake** executable.

Next, use the `CPACK_INSTALL_CMAKE_PROJECTS` variable to specify which projects to install. In this case, we want to install both debug and release.

### MultiCPackConfig.cmake
```cmake
include("release/CPackConfig.cmake")

set(
   CPACK_INSTALL_CMAKE_PROJECTS
      "debug;Tutorial;ALL;/"
      "release;Tutorial;ALL;/"
)
```

From the **Step12** directory, run `cpack` specifying our custom configuration file with the **config** option:

```bash
cpack --config MultiCPackConfig.cmake
```

---