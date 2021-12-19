cmake_minimum_required(VERSION 3.20)

    set(PROJECT_NAME
            Tutorial
    )

    set(
        INCLUDE_LIBRARY_NAME
            MathFunctions
    )

project(
    ${PROJECT_NAME}
        VERSION 1.0
)

    # use d as the postfix for build the debug versions
    # of the executable and libraries
    set(
        CMAKE_DEBUG_POSTFIX
            d
    )

add_library(
        ${PROJECT_NAME}_compiler_flags
    INTERFACE
)
target_compile_features(
        ${PROJECT_NAME}_compiler_flags
    INTERFACE
        cxx_std_17
)

    set(
        gcc_like_cxx
            $<COMPILE_LANG_AND_ID:
                AppleClang,
                ARMClang,
                Clang,
                CXX,
                GNU,
                LCC
            >
    )
    set(
        msvc_cxx
            $<COMPILE_LANG_AND_ID:
                CXX,
                MSVC
            >
    )
target_compile_options(
        ${PROJECT_NAME}_compiler_flags
    INTERFACE
        $<${gcc_like_cxx}:
            $<BUILD_INTERFACE:
                -Wall;
                -Wextra;
                -Wshadow;
                -Wformat=2;
                -Wunused
            >
        >
        $<${msvc_cxx}:
            $<BUILD_INTERFACE:
                -W3
            >
        >
)

    set(
        CMAKE_ARCHIVE_OUTPUT_DIRECTORY                  # Location of linked compilation libraries
            ${PROJECT_BINARY_DIR}
#            ${PROJECT_BINARY_DIR}/stat_lib
    )
    set(
        CMAKE_LIBRARY_OUTPUT_DIRECTORY                  # Location of dynamic library files
            ${PROJECT_BINARY_DIR}
#            ${PROJECT_BINARY_DIR}/dyn_lib
    )
    set(
        CMAKE_RUNTIME_OUTPUT_DIRECTORY                  # Location of target files
            ${PROJECT_BINARY_DIR}
#            ${PROJECT_BINARY_DIR}/bin
    )

option(
    BUILD_SHARED_LIBS
        "Build using shared libraries"     ON
)

if(APPLE)
    set(
        CMAKE_INSTALL_RPATH
            @executable_path/../lib
    )
elseif(UNIX)
    set(
        CMAKE_INSTALL_RPATH
            $ORIGIN/../lib
    )
endif()

add_subdirectory(${INCLUDE_LIBRARY_NAME})

configure_file(
    ${PROJECT_NAME}Config.h.in
        ${PROJECT_NAME}Config.h
)

add_executable(
    ${PROJECT_NAME}
        tutorial.cxx
)
# to create debug versions of the executable and libraries
set_target_properties(
        ${PROJECT_NAME}
    PROPERTIES
        DEBUG_POSTFIX
            ${CMAKE_DEBUG_POSTFIX}
)

target_link_libraries(
        ${PROJECT_NAME}
    PUBLIC
        ${INCLUDE_LIBRARY_NAME}                         # Gather the Libraries
)

target_include_directories(
        ${PROJECT_NAME}
    PUBLIC
        ${PROJECT_BINARY_DIR}                           # will find TutorialConfig.h
)


#### INSTALLATION, TESTS, PACKAGING ####
install(
    TARGETS
        ${PROJECT_NAME}
    DESTINATION
        bin                                             # output folder for binary executable files
)
install(
    FILES
        ${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.h
    DESTINATION
        include                                         # output folder for configured header files
)

include(CTest)                                          # CTest calls enable_testing() automatically

add_test(
    NAME
        Runs
    COMMAND
        ${PROJECT_NAME} 25
)

add_test(
    NAME
        Usage
    COMMAND
        ${PROJECT_NAME}
)
set_tests_properties(
        Usage
    PROPERTIES
        PASS_REGULAR_EXPRESSION
            "Usage:.*number"
)

function(
    do_test
        target arg
            result
)
    add_test(
        NAME
            Comp${arg}
        COMMAND
            ${target}
            ${arg}
    )
    set_tests_properties(
            Comp${arg}
        PROPERTIES
            PASS_REGULAR_EXPRESSION
                ${result}
    )
endfunction()

do_test(
    ${PROJECT_NAME} 4
        "4 is 2"
)
do_test(
    ${PROJECT_NAME} 9
        "9 is 3"
)
do_test(
    ${PROJECT_NAME} 5
        "5 is 2.236"
)
do_test(
    ${PROJECT_NAME} 7
        "7 is 2.645"
)
do_test(
    ${PROJECT_NAME} 25
        "25 is 5"
)
do_test(
    ${PROJECT_NAME} -25
        "-25 is (-nan|nan|0)"
)
do_test(
    ${PROJECT_NAME} 0.0001
        "0.0001 is 0.01"
)

include(InstallRequiredSystemLibraries)

    set(
        CPACK_RESOURCE_FILE_LICENSE
            ${CMAKE_CURRENT_SOURCE_DIR}/License.txt
    )

    set(
        CPACK_PACKAGE_NAME
            ${PROJECT_NAME}App
    )
    set(
        CPACK_PACKAGE_VENDOR
            yoric.pro
    )

    set(
        CPACK_PACKAGE_VERSION_MAJOR
            ${${PROJECT_NAME}_VERSION_MAJOR}
    )
    set(
        CPACK_PACKAGE_VERSION_MINOR
            ${${PROJECT_NAME}_VERSION_MINOR}
    )

    set(
        CPACK_PACKAGE_INSTALL_DIRECTORY
            "CMake ${CMake_VERSION_MAJOR}.${CMake_VERSION_MINOR}"
    )

    set(
        CPACK_SOURCE_GENERATOR
            TGZ
    )

if(WIN32 AND NOT UNIX)
    set(
        CPACK_PACKAGE_ICON
            ${CMake_SOURCE_DIR}/Utilities/Release\\\\InstallIcon.bmp
    )
    set(
        CPACK_NSIS_INSTALLED_ICON_NAME
            bin\\\\${PROJECT_NAME}.exe
    )
    set(
        CPACK_NSIS_DISPLAY_NAME
            ${CPACK_PACKAGE_INSTALL_DIRECTORY}
                "${PROJECT_NAME} Project"
    )
    set(
        CPACK_NSIS_HELP_LINK
            https:\\\\\\\\yoric.pro
    )
    set(
        CPACK_NSIS_URL_INFO_ABOUT
            https:\\\\\\\\yoric.pro
    )
    set(
        CPACK_NSIS_CONTACT
            yoricsv@yandex.ru
    )
    set(CPACK_NSIS_MODIFY_PATH      ON)
else()
    set(
        CPACK_STRIP_FILES
            bin/${PROJECT_NAME}
    )
    set(
        CPACK_SOURCE_STRIP_FILES ""
    )
endif()

    set(
        CPACK_PACKAGE_EXECUTABLES
            ${PROJECT_NAME}
            "Example Executable")

include(CPack)

install(
    EXPORT
        ${INCLUDE_LIBRARY_NAME}Targets                  # need to explicitly install the generated
    FILE
        ${INCLUDE_LIBRARY_NAME}Targets.cmake            # the name of the template for generating
    DESTINATION
        lib/cmake/${INCLUDE_LIBRARY_NAME}               # place where it should be located
)

include(CMakePackageConfigHelpers)

configure_package_config_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in                         # configure package file location
        ${CMAKE_CURRENT_BINARY_DIR}/${INCLUDE_LIBRARY_NAME}Config.cmake     # config file location
    INSTALL_DESTINATION
        lib/cmake/example                                                   # generated files location
    NO_SET_AND_CHECK_MACRO
    NO_CHECK_REQUIRED_COMPONENTS_MACRO
)

write_basic_package_version_file(
        ${CMAKE_CURRENT_BINARY_DIR}/${INCLUDE_LIBRARY_NAME}ConfigVersion.cmake  # file for find_package() function
    VERSION
        ${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR}       # version of the desired package
    COMPATIBILITY
        AnyNewerVersion
)

# Finally, install both generated configuration files
install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/${INCLUDE_LIBRARY_NAME}Config.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/${INCLUDE_LIBRARY_NAME}ConfigVersion.cmake
    DESTINATION
        lib/cmake/${INCLUDE_LIBRARY_NAME}
)

export(
    EXPORT
        ${INCLUDE_LIBRARY_NAME}Targets
    FILE
        ${CMAKE_CURRENT_BINARY_DIR}/${INCLUDE_LIBRARY_NAME}Targets.cmake
)