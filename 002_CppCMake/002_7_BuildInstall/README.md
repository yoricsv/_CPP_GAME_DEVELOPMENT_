## [_CMAKE_][CMake] > **Step 7: Packaging an Installe**

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

# <p align = center><b>002_7_BuildInstall<b></p>

Next suppose that we want to distribute our project to other people so that they can use it. We want to provide both binary and source distributions on a variety of platforms. This is a little different from the install we did previously in *Installing* and *Testing*, where we were installing the binaries that we had built from the source code. In this example we will be building installation packages that support binary installations and package management features. To accomplish this we will use CPack to create platform specific installers. Specifically we need to add a few lines to the bottom of our *top-level* ***CMakeLists.txt*** file.

### CMakeLists.txt
```cmake
include(InstallRequiredSystemLibraries)
   set(
      CPACK_RESOURCE_FILE_LICENSE
         "${CMAKE_CURRENT_SOURCE_DIR}/License.txt"
   )
   set(
      CPACK_PACKAGE_VERSION_MAJOR
         "${Tutorial_VERSION_MAJOR}"
   )
   set(
      CPACK_PACKAGE_VERSION_MINOR
         "${Tutorial_VERSION_MINOR}"
   )
include(CPack)
```

That is all there is to it. We start by including `InstallRequiredSystemLibraries`. This module will include any runtime libraries that are needed by the project for the current platform. Next we set some CPack variables to where we have stored the license and version information for this project. The version information was set earlier in this tutorial and the ***license.txt*** has been included in the *top-level source directory* for this step.

Finally we include the **CPack module** which will use these variables and some other properties of the current system to setup an installer.

The next step is to build the project in the usual manner and then run the `cpack` executable. To build a binary distribution, from the binary directory run:

```bash
cpack
```

To specify the generator, use the `-G` option. For multi-config builds, use `-C` to specify the configuration. *For example*:

```bash
cpack -G ZIP -C Debug
```

To create a source distribution you would type:

```bash
cpack --config CPackSourceConfig.cmake
```

Alternatively, run `make package` or *right click* the `Package` target and `Build Project` from an IDE.

Run the installer found in the binary directory. Then run the installed executable and verify that it works.

---