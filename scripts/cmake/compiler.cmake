# Compiler specific settings

if(compiler_included)
    return()
endif()
set(compiler_included true)

function(add_compiler_flags)
    foreach(flag ${ARGV})
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${flag}" PARENT_SCOPE)
    endforeach()
endfunction()

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compiler_flags(-fvisibility=hidden)
    add_compiler_flags(-fstrict-aliasing)
    add_compiler_flags(-Wall)
    add_compiler_flags(-Wextra)
    add_compiler_flags(-fdiagnostics-show-option)
    add_compiler_flags(-Wold-style-cast)
    add_compiler_flags(-Wundef)
    add_compiler_flags(-Wredundant-decls)
    add_compiler_flags(-Wwrite-strings)
    add_compiler_flags(-Wpointer-arith)
    add_compiler_flags(-Wcast-qual)
    add_compiler_flags(-Wformat=2)
    add_compiler_flags(-Wmissing-include-dirs)
    add_compiler_flags(-Wcast-align)
    add_compiler_flags(-Wswitch-enum)
    add_compiler_flags(-Wnon-virtual-dtor)
    add_compiler_flags(-Wctor-dtor-privacy)
    add_compiler_flags(-Wsign-conversion)
    add_compiler_flags(-Wdisabled-optimization)
    add_compiler_flags(-Winline)
    add_compiler_flags(-Winvalid-pch)
    add_compiler_flags(-Woverloaded-virtual)
    add_compiler_flags(-Wdouble-promotion)
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compiler_flags(-Wshift-overflow=2)
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    add_compiler_flags(-Wlogical-op)
    add_compiler_flags(-Wnoexcept)
    add_compiler_flags(-Wtrampolines)
    add_compiler_flags(-Wzero-as-null-pointer-constant)
    add_compiler_flags(-Wuseless-cast)

    if(CMAKE_CXX_COMPILER_VERSION VERSION_EQUAL 6.0
            OR CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 6.0)
        add_compiler_flags(-Wnull-dereference)
        add_compiler_flags(-Wshift-overflow=2)
        add_compiler_flags(-Wduplicated-cond)
    endif()

    if(CMAKE_CXX_COMPILER_VERSION VERSION_EQUAL 7.0
            OR CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 7.0)
        add_compiler_flags(-Walloc-zero)
        add_compiler_flags(-Walloca)
        add_compiler_flags(-Wimplicit-fallthrough)
    endif()
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compiler_flags(-Wshift-overflow)
    add_compiler_flags(-Qunused-arguments -fcolor-diagnostics) # needed for ccache integration on travis
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    add_compiler_flags(/std:c++latest) # for post c++14 updates in MSVC
    add_definitions(-D_CRT_SECURE_NO_WARNINGS) # Suppress C4996

    if (NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 19.10)
        add_compiler_flags(/permissive-) # force standard conformance
    endif()
endif()
