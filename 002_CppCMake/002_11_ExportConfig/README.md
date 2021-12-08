## [_CMAKE_][CMake] > **Step 11: Adding Export Configuration**

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

# <p align = center><b>002_11_ExportConfig<b></p>

During *Installing* and *Testing* of the **tutorial** we added the ability for CMake to install the library and headers of the project. During *Packaging an Installer* we added the ability to package up this information so it could be distributed to other people.

The next step is to add the necessary information so that other CMake projects can use our project, be it from a build directory, a local install or when packaged.

The first step is to update our `install(TARGETS)` commands to not only specify a `DESTINATION` but also an `EXPORT`. The `EXPORT` keyword generates a CMake file containing code to import all targets listed in the install command from the installation tree. So let's go ahead and explicitly `EXPORT` the **MathFunctions** library by updating the `install` command in ***MathFunctions/CMakeLists.txt*** to look like:

### MathFunctions/CMakeLists.txt
```cmake
set(
   installable_libs
      MathFunctions
   tutorial_compiler_flags
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
   EXPORT
      MathFunctionsTargets
)

install(
   FILES
      MathFunctions.h
   DESTINATION
      include
)
```

Now that we have **MathFunctions** being exported, we also need to explicitly install the generated ***MathFunctionsTargets.cmake*** file. This is done by adding the following to the bottom of the top-level ***CMakeLists.txt***:

### CMakeLists.txt
```cmake
install(
   EXPORT
      MathFunctionsTargets
   FILE
      MathFunctionsTargets.cmake
   DESTINATION
      lib/cmake/MathFunctions
)
```

At this point you should try and run CMake. If everything is setup properly you will see that CMake will generate an error that looks like:

```bash
Target "MathFunctions" INTERFACE_INCLUDE_DIRECTORIES property contains
path:

  "/Users/robert/Documents/CMakeClass/Tutorial/Step11/MathFunctions"

which is prefixed in the source directory.
```

What CMake is trying to say is that during generating the export information it will export a path that is intrinsically tied to the current machine and will not be valid on other machines. The solution to this is to update the **MathFunctions** `target_include_directories()` to understand that it needs different `INTERFACE` locations when being used from within the build directory and from an *install / package*. This means converting the `target_include_directories()` call for **MathFunctions** to look like:

### MathFunctions/CMakeLists.txt
```cmake
target_include_directories(
      MathFunctions
   INTERFACE
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
      $<INSTALL_INTERFACE:include>
)
```

Once this has been updated, we can re-run CMake and verify that it doesn't warn anymore.

At this point, we have CMake properly packaging the target information that is required but we will still need to generate a ***MathFunctionsConfig.cmake*** so that the CMake `find_package()` command can find our project. So let's go ahead and add a new file to the top-level of the project called ***Config.cmake.in*** with the following contents:

### Config.cmake.in
```cmake
@PACKAGE_INIT@

include( "${CMAKE_CURRENT_LIST_DIR}/MathFunctionsTargets.cmake" )
```

Then, to properly configure and install that file, add the following to the bottom of the *top-level* ***CMakeLists.txt***:

### CMakeLists.txt
```cmake
install(
   EXPORT
      MathFunctionsTargets
   FILE
      MathFunctionsTargets.cmake
   DESTINATION
      lib/cmake/MathFunctions
)

include( CMakePackageConfigHelpers )
```

Next, we execute the `configure_package_config_file()`. This command will configure a provided file but with a few specific differences from the standard `configure_file()` way. To properly utilize this function, the input file should have a single line with the text `@PACKAGE_INIT@` in addition to the content that is desired. That variable will be replaced with a block of code which turns set values into relative paths. These values which are new can be referenced by the same name but prepended with a `PACKAGE_` prefix.

### CMakeLists.txt
```cmake
install(
   EXPORT
      MathFunctionsTargets
   FILE
      MathFunctionsTargets.cmake
   DESTINATION
      lib/cmake/MathFunctions
)

include(CMakePackageConfigHelpers)

# generate the config file that is includes the exports
configure_package_config_file(
   ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
      "${CMAKE_CURRENT_BINARY_DIR}/MathFunctionsConfig.cmake"
   INSTALL_DESTINATION
      "lib/cmake/example"
   NO_SET_AND_CHECK_MACRO
   NO_CHECK_REQUIRED_COMPONENTS_MACRO
)
```

The `write_basic_package_version_file()` is next. This command writes a file which is used by the "find_package" document the version and compatibility of the desired package. Here, we use the `Tutorial_VERSION_*` variables and say that it is compatible with `AnyNewerVersion`, which denotes that this version or any higher one are compatible with the requested version.

### CMakeLists.txt
```cmake
write_basic_package_version_file(
      "${CMAKE_CURRENT_BINARY_DIR}/MathFunctionsConfigVersion.cmake"
   VERSION
      "${Tutorial_VERSION_MAJOR}.${Tutorial_VERSION_MINOR}"
   COMPATIBILITY
      AnyNewerVersion
)
```

Finally, set both generated files to be installed:

### CMakeLists.txt
```cmake
install(
   FILES
      ${CMAKE_CURRENT_BINARY_DIR}/MathFunctionsConfig.cmake
      ${CMAKE_CURRENT_BINARY_DIR}/MathFunctionsConfigVersion.cmake
   DESTINATION
      lib/cmake/MathFunctions
)
```

At this point, we have generated a relocatable CMake Configuration for our project that can be used after the project has been installed or packaged. If we want our project to also be used from a build directory we only have to add the following to the bottom of the *top level* ***CMakeLists.txt***:

### CMakeLists.txt
```cmake
export( 
   EXPORT
      MathFunctionsTargets
   FILE
      "${CMAKE_CURRENT_BINARY_DIR}/MathFunctionsTargets.cmake"
)
```

With this export call we now generate a ***Targets.cmake***, allowing the configured ***MathFunctionsConfig.cmake*** in the build directory to be used by other projects, without needing it to be installed.

---