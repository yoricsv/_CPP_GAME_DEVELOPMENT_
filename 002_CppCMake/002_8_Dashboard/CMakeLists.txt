cmake_minimum_required(VERSION 3.20)

    set(PROJECT_NAME
            Tutorial
    )

project(
    ${PROJECT_NAME}
        VERSION 1.0
)

    set(CMAKE_CXX_STANDARD          17  )
    set(CMAKE_CXX_STANDARD_REQUIRED True)

option(
    USE_MY_MATH
        "Use tutorial provided math implementation"  ON
)

if(USE_MY_MATH)
    add_subdirectory(MathFunctions)
    list(
        APPEND
            EXTRA_LIBS                                  # to collect up any optional libraries to later be linked
                MathFunctions                           # Name of the including Library
    )
endif()

configure_file(
    ${PROJECT_NAME}Config.h.in
        ${PROJECT_NAME}Config.h
)

add_executable(
    ${PROJECT_NAME}
        tutorial.cxx
)

target_link_libraries(
        Tutorial
    PUBLIC
        ${EXTRA_LIBS}                                   # Gather the Libraries
)

target_include_directories(
        ${PROJECT_NAME}
    PUBLIC
        ${PROJECT_BINARY_DIR}                           # will find TutorialConfig.h
)

install(
    TARGETS
        Tutorial
    DESTINATION
        bin                                             # output folder where will placed binary executable files
)
install(
    FILES
        ${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.h
    DESTINATION
        include                                         # output folder where will placed configured header files
)

# add CTest to include support for dashboard
include(CTest)                                          # CTest will automatically call enable_testing()

add_test(
    NAME
        Runs
    COMMAND
        Tutorial 25
)

add_test(
    NAME
        Usage
    COMMAND
        Tutorial
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
    Tutorial 4
        "4 is 2"
)
do_test(
    Tutorial 9
        "9 is 3"
)
do_test(
    Tutorial 5
        "5 is 2.236"
)
do_test(
    Tutorial 7
        "7 is 2.645"
)
do_test(
    Tutorial 25
        "25 is 5"
)
do_test(
    Tutorial -25
        "-25 is (-nan|nan|0)"
)
do_test(
    Tutorial 0.0001
        "0.0001 is 0.01"
)

include(InstallRequiredSystemLibraries)

    set(
        CPACK_PACKAGE_NAME
            ${PROJECT_NAME}App
    )
    set(
        CPACK_PACKAGE_VENDOR
            Yoric.pro
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