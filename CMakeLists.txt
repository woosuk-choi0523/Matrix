cmake_minimum_required(VERSION 3.31)
project(Matrix C)

set(CMAKE_C_STANDARD 11)

# 라이브러리 생성 (Matrix.c, Ai.c 포함)
add_library(Matrix STATIC Matrix.c Ai.c)

# 실행 파일 생성 (main.c 포함)
add_executable(MatrixApp main.c)

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    message(STATUS "Running on Windows")
    # 실행 파일에 라이브러리 링크
    target_link_libraries(MatrixApp Matrix)

elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    message(STATUS "Running on Linux")
    # 실행 파일에 라이브러리 링
    target_link_libraries(MatrixApp Matrix m)

elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    message(STATUS "Running on macOS")
    # 실행 파일에 라이브러리 링
    target_link_libraries(MatrixApp Matrix m)
endif()

