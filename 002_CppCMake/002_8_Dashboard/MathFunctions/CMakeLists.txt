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

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_library(
    MathFunctions
        mysqrt.cxx                                  # mysqrt.cxx depends on the generated file Table.h
        ${CMAKE_CURRENT_BINARY_DIR}/Table.h         # add the Table.h to the list of sources of the MathFunctions
)

target_include_directories(
        MathFunctions
    INTERFACE                                       # make a scope only for targets depending on it
        ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE                                         # add the current BINARY directory so
        ${CMAKE_CURRENT_BINARY_DIR}                 # that mysqrt.cxx finds Table.h
)

install(
    TARGETS
        MathFunctions
    DESTINATION
        lib
)
install(
    FILES
        MathFunctions.h
    DESTINATION
        include
)