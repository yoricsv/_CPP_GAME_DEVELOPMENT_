## [_CMAKE_][CMake] > **Step 5: Adding System Introspection**

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

# <p align = center><b>002_5_SysIntrospection<b></p>

Let us consider adding some code to our project that depends on features the target platform may not have. For this example, we will add some code that depends on whether or not the target platform has the `log` and `exp`* functions. Of course almost every platform has these functions but for this tutorial assume that they are not common.

If the platform has `log` and `exp` then we will use them to compute the square root in the `mysqrt` function. We first test for the availability of these functions using the ***CheckSymbolExists*** module in ***MathFunctions/CMakeLists.txt***. On some platforms, we will need to link to the m library. If `log` and `exp` are not initially found, require the **m** library and try again.

Add the checks for `log` and `exp` to ***MathFunctions/CMakeLists.txt***, after the call to `target_include_directories()`:

### MathFunctions/CMakeLists.txt
```cmake
target_include_directories(
      MathFunctions
   INTERFACE
      ${CMAKE_CURRENT_SOURCE_DIR}
)

# does this system provide the log and exp functions?
include(CheckSymbolExists)
check_symbol_exists(
   log
      "math.h"
   HAVE_LOG
)
check_symbol_exists(
   exp
      "math.h"
   HAVE_EXP
)
if(NOT (HAVE_LOG AND HAVE_EXP))
   unset(
      HAVE_LOG
         CACHE
   )
   unset(
      HAVE_EXP
         CACHE
   )

   set(CMAKE_REQUIRED_LIBRARIES "m")

   check_symbol_exists(
      log
         "math.h"
      HAVE_LOG
   )
   check_symbol_exists(
      exp
         "math.h"
      HAVE_EXP
   )
   if(HAVE_LOG AND HAVE_EXP)
      target_link_libraries(
            MathFunctions
         PRIVATE
            m
      )
   endif()
endif()
```

If available, use `target_compile_definitions()` to specify `HAVE_LOG` and `HAVE_EXP` as `PRIVATE` compile definitions.

### MathFunctions/CMakeLists.txt
```cmake
if(HAVE_LOG AND HAVE_EXP)
   target_compile_definitions(
         MathFunctions
      PRIVATE
         "HAVE_LOG"
         "HAVE_EXP"
   )
endif()
```

If `log` and `exp` are available on the system, then we will use them to compute the square root in the `mysqrt` function. Add the following code to the `mysqrt` function in ***MathFunctions/mysqrt.cxx*** 
(**don't forget the `#endif` before returning the result!**):

### MathFunctions/mysqrt.cxx
```cpp
#if defined(HAVE_LOG) && defined(HAVE_EXP)
   double result = exp(log(x) * 0.5);
   std::cout << "Computing sqrt of " << x
             << " to be "            << result
             << " using log and exp" 
             << std::endl;
#else
   double result = x;
```

We will also *need to modify* ***mysqrt.cxx*** to include `cmath`.

### MathFunctions/mysqrt.cxx
```cpp
#include <cmath>
```

Run the **cmake** executable or the **cmake-gui** to configure the project and then build it with your chosen build tool and run the Tutorial executable.

Which function gives better results now, `sqrt` or `mysqrt`?

---