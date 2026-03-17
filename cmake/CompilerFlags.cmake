# Compiler and linker flags for enhanced error detection
include(CheckCXXCompilerFlag)

# Function to check and add compiler flag if supported
function(add_cxx_compiler_flag TARGET FLAG)
    check_cxx_compiler_flag("${FLAG}" COMPILER_SUPPORTS_${FLAG})
    if(COMPILER_SUPPORTS_${FLAG})
        target_compile_options(${TARGET} PRIVATE ${FLAG})
    endif()
endfunction()

# Function to add warning flags to a target
function(add_warning_flags TARGET)
    # Common flags for all compilers
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(${TARGET} PRIVATE
            -Wall
            -Wextra
            -Wpedantic
            -Werror
        )
        
        # GCC and Clang common flags
        target_compile_options(${TARGET} PRIVATE
            -Wcast-align
            -Wcast-qual
            -Wconversion
            -Wctor-dtor-privacy
            -Wdouble-promotion
            # -Weffc++
            -Wextra-semi
            -Wfloat-equal
            -Wformat=2
            -Wmissing-declarations
            -Wmissing-include-dirs
            # -Wnoexcept
            -Wnon-virtual-dtor
            -Wnull-dereference
            # -Wold-style-cast
            -Woverloaded-virtual
            -Wpointer-arith
            -Wredundant-decls
            -Wshadow
            -Wsign-conversion
            -Wswitch-default
            -Wswitch-enum
            -Wundef
            -Wunused
            # -Wzero-as-null-pointer-constant
            -Wno-exit-time-destructors
            -Wno-global-constructors
            -Wno-weak-vtables
        )

        # GCC specific flags
        if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
            target_compile_options(${TARGET} PRIVATE
                -Wmisleading-indentation
                -Wduplicated-branches
                -Wduplicated-cond
                -Wlogical-op
            )
        endif()

        # Clang specific flags
        if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
            target_compile_options(${TARGET} PRIVATE
                -Weverything
                -Wno-c++98-compat
                -Wno-c++98-compat-pedantic
                -Wno-padded
                -Wno-documentation-unknown-command
            )
        endif()

    # MSVC specific flags
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        target_compile_options(${TARGET} PRIVATE
            /W4
            /WX
            /permissive-
            /w14242
            /w14254
            /w14263
            /w14265
            /w14287
            /we4289
            /w14296
            /w14311
            /w14545
            /w14546
            /w14547
            /w14549
            /w14555
            /w14619
            /w14640
            /w14826
            /w14905
            /w14906
            /w14928
            /w14946
        )
    endif()

    # Sanitizer flags (for Debug builds)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
            # Address sanitizer
            # target_compile_options(${TARGET} PRIVATE -fsanitize=address)
            # target_link_options(${TARGET} PRIVATE -fsanitize=address)
            
            # Undefined behavior sanitizer
            # target_compile_options(${TARGET} PRIVATE -fsanitize=undefined)
            # target_link_options(${TARGET} PRIVATE -fsanitize=undefined)
            
            # Thread sanitizer (can't be used with address sanitizer)
            # Uncomment if needed:
            # target_compile_options(${TARGET} PRIVATE -fsanitize=thread)
            # target_link_options(${TARGET} PRIVATE -fsanitize=thread)
        endif()
    endif()
endfunction()

# Example usage in your CMakeLists.txt:
# cmake_minimum_required(VERSION 3.12)
# project(YourProject CXX)
#
# # Create your target
# add_executable(your_target source1.cpp source2.cpp)
#
# # Set C++ standard
# target_compile_features(your_target PRIVATE cxx_std_17)
#
# # Add warning flags
# add_warning_flags(your_target)
