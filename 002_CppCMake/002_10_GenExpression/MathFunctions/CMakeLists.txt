    set(
        LIBRARY_NAME
            MathFunctions
    )

add_library(
    ${LIBRARY_NAME}
        MathFunctions.cxx
)

target_include_directories(
        ${LIBRARY_NAME}
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

option(
    USE_MY_MATH
        "Use tutorial provided math implementation"     ON
)

if(USE_MY_MATH)
    target_compile_definitions(
            ${LIBRARY_NAME}
        PRIVATE
            USE_MY_MATH
    )

    add_executable(
        MakeTable
            MakeTable.cxx
    )

    add_custom_command(
        OUTPUT
            ${CMAKE_CURRENT_BINARY_DIR}/Table.h         # specified that Table.h will be generated
        COMMAND
            MakeTable
                ${CMAKE_CURRENT_BINARY_DIR}/Table.h     # it will generate after the MakeTable is compiled
        DEPENDS
            MakeTable                                   # Table.h depends on MakeTable
    )

    add_library(
            SqrtLibrary
        STATIC
            mysqrt.cxx                                  # mysqrt.cxx depends on the generated file Table.h
            ${CMAKE_CURRENT_BINARY_DIR}/Table.h         # add the Table.h to the list of sources of the MathFunctions
    )

    target_include_directories(
            SqrtLibrary
        PRIVATE                                         # add the current BINARY directory so
            ${CMAKE_CURRENT_BINARY_DIR}                 # that mysqrt.cxx finds Table.h
    )

    set_target_properties(
            SqrtLibrary
        PROPERTIES
            POSITION_INDEPENDENT_CODE
                ${BUILD_SHARED_LIBS}
    )

    target_link_libraries(
            ${LIBRARY_NAME}
        PRIVATE
            SqrtLibrary
    )
endif()

target_compile_definitions(
        ${LIBRARY_NAME}
    PRIVATE
        EXPORTING_MY_MATH
)

    set(
        INSTALLABLE_LIBS
            ${LIBRARY_NAME}
    )

if(TARGET SqrtLibrary)
    list(
        APPEND
            INSTALLABLE_LIBS
                SqrtLibrary
    )
endif()


install(
    TARGETS
        ${INSTALLABLE_LIBS}
    DESTINATION
        lib
)
install(
    FILES
        MathFunctions.h
    DESTINATION
        include
)