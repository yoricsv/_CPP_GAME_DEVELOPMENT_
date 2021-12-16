add_library(
    MathFunctions
        mysqrt.cxx
)

target_include_directories(
        MathFunctions
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# Check does this system provide the log and exp functions?
# [REMARK] The checks have to the call after target_include_directories()
# [REMARK] Beside all, have to add log and exp in the source code (see below)
include(CheckSymbolExists)

# This function check support of log
check_symbol_exists(
    log
        math.h
    HAVE_LOG                            # In case OK - set flag HAVE_LOG
)

# This function check support of exp
check_symbol_exists(
    exp
        math.h
    HAVE_EXP                            # In case OK - set flag HAVE_EXP
)

# In case NOT, clear cache variables
if(NOT (HAVE_LOG AND HAVE_EXP))
    unset(
        HAVE_LOG
            CACHE
    )
    unset(
        HAVE_EXP
            CACHE
    )

    # for use this require the m library and try again
    set(CMAKE_REQUIRED_LIBRARIES    m)

    # try again to check support log and exp
    check_symbol_exists(
        log
            math.h
        HAVE_LOG
    )
    check_symbol_exists(
        exp
            math.h
        HAVE_EXP
    )

    # If everything is OK add m Library to the project
    if(HAVE_LOG AND HAVE_EXP)
        target_link_libraries(
                MathFunctions
            PRIVATE
                m                           # add m library for log/exp
        )

        # [OPTIONAL] IF AVAILABLE, try to use it instead previous one
#        target_compile_definitions(
#                MathFunctions
#            PRIVATE
#                HAVE_LOG
#                HAVE_EXP
#        )
    endif()
endif()

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