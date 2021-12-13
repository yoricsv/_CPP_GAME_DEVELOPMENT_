add_library(
    MathFunctions
        mysqrt.cxx
)

target_include_directories(
        MathFunctions
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# add rules to install the library and header files for the application
install(
    TARGETS
        MathFunctions
    DESTINATION
        lib                 # output folder where will placed executable header
)
install(
    FILES
        MathFunctions.h
    DESTINATION
        include             # output folder where will placed configured headers
)