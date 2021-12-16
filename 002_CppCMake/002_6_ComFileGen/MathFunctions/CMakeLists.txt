# first we add the executable that generates the table
add_executable(
    MakeTable
        MakeTable.cxx
)

# add the command to generate the source code
add_custom_command(
    OUTPUT
        ${CMAKE_CURRENT_BINARY_DIR}/Table.h         # specified that Table.h will be generated
    COMMAND
        MakeTable
            ${CMAKE_CURRENT_BINARY_DIR}/Table.h     # it will generate after the MakeTable is compiled
    DEPENDS
        MakeTable                                   # Table.h depends on MakeTable
)

# add the binary tree directory to the search path for include files
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# add MakeTable headers to the main library
add_library(
    MathFunctions
        mysqrt.cxx                                  # mysqrt.cxx depends on the generated file Table.h
        ${CMAKE_CURRENT_BINARY_DIR}/Table.h         # add the Table.h to the list of sources of the MathFunctions
)

# add the list of include directories
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