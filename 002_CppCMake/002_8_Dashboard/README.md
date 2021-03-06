## [_GAMEDEV_][gamedev] > [_CMake_][CMake] > **Step 8**: *Adding Support for a Testing Dashboard*

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
[stp3]:    ../002_3_UsageReqForLib/README.md
[stp4]:    ../002_4_InstallAndTest/README.md
[stp5]:    ../002_5_SysIntrospection/README.md
[stp6]:    ../002_6_ComFileGen/README.md
[stp7]:    ../002_7_BuildInstall/README.md
[stp8]:    README.md
[stp9]:    ../002_9_StaticShared/README.md
[stp10]:   ../002_10_GenExpression/README.md
[stp11]:   ../002_11_ExportConfig/README.md
[stp12]:   ../002_12_PackDebRel/README.md

---
<!-- ---------------------------------- * Navigation * ---------------------------------- -->

# <p align = center><b>002_8_Dashboard</b></p>

Adding support for submitting our test results to a dashboard is simple. We already defined a number of tests for our project in **Testing Support**. Now we just have to run those tests and submit them to a dashboard. To include support for dashboards we include the CTest module in our *top-level* ***CMakeLists.txt***.

Replace:

### CMakeLists.txt

```cmake
# enable testing
enable_testing()
```

With:

### CMakeLists.txt

```cmake
# enable dashboard scripting
include(CTest)
```

The CTest module will automatically call `enable_testing()`, so we can remove it from our CMake files.

We will also need to acquire a ***CTestConfig.cmake*** file to be placed in the top-level directory where we can specify information to CTest about the project. It contains:

* The project name
* The project "Nightly" start time
  * The time when a 24 hour "day" starts for this project.
* The URL of the CDash instance where the submission's generated documents will be sent

One has been provided for you in this directory. It would normally be downloaded from the **Settings** page of the project on the CDash instance that will host and display the test results. Once downloaded from CDash, the file should not be modified locally.

### CTestConfig.cmake

```cmake
   set(CTEST_PROJECT_NAME
         CMakeTutorial
   )
   set(CTEST_NIGHTLY_START_TIME
         "00:00:00 EST"
   )

   set(CTEST_DROP_METHOD
         http
   )
   set(CTEST_DROP_SITE
         my.cdash.org
   )
   set(CTEST_DROP_LOCATION
         /submit.php?project=CMakeTutorial
   )
   set(CTEST_DROP_SITE_CDASH
         TRUE
   )
```

The **ctest** executable will read in this file when it runs. To create a simple dashboard you can run the **cmake** executable or the **cmake-gui** to configure the project, but do not build it yet. Instead, change directory to the binary tree, and then run:

```bash
ctest [-VV] -D Experimental
```

Remember, for multi-config generators (e.g. Visual Studio), the configuration type must be specified:

```bash
ctest [-VV] -C Debug -D Experimental
```

Or, from an IDE, build the *Experimental* target.

The **ctest** executable will build and test the project and submit the results to Kitware's public dashboard: https://my.cdash.org/index.php?project=CMakeTutorial.

---