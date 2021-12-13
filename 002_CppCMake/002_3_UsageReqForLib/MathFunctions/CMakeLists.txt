add_library(
    MathFunctions
        mysqrt.cxx
)

# add transitive property
# For this, needs to include the current source directory
target_include_directories(
        MathFunctions
    INTERFACE								# for using this Library in the other projects
        ${CMAKE_CURRENT_SOURCE_DIR}			# Library sources PATH start from here
)