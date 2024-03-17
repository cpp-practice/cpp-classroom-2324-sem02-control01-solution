cmake_minimum_required (VERSION 3.8)

project(control-01)

set(CMAKE_CXX_STANDARD 20)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /WX") # CMake already contains W3 in its flags
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra-semi -O1 -g -fsanitize=address -fno-omit-frame-pointer")
endif()


add_executable(task-1-test-1 src/task_1/test_1.cpp src/task_1/zip.hpp)
add_executable(task-1-test-2 src/task_1/test_2.cpp src/task_1/zip.hpp)
add_executable(task-1-test-3 src/task_1/test_3.cpp src/task_1/zip.hpp)

add_executable(task-2-test-1 src/task_2/test_1.cpp src/task_2/maslenica.hpp)
add_executable(task-2-test-2 src/task_2/test_2.cpp src/task_2/maslenica.hpp)
add_executable(task-2-test-2-extra src/task_2/test_2_extra.cpp src/task_2/maslenica.hpp)

# tests for non-compilation cases
add_executable(task-2-test-2-ncomp1 src/task_2/ncomp_add_ii.cpp src/task_2/maslenica.hpp)
add_executable(task-2-test-2-ncomp2 src/task_2/ncomp_add_left_assoc.cpp src/task_2/maslenica.hpp)
add_executable(task-2-test-2-ncomp3 src/task_2/ncomp_add_mixed.cpp src/task_2/maslenica.hpp)
add_executable(task-2-test-2-ncomp4 src/task_2/ncomp_add_right_assoc.cpp src/task_2/maslenica.hpp)