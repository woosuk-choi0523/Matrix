cmake_minimum_required(VERSION 3.31)
project(Matrix C)

set(CMAKE_C_STANDARD 11)

# 라이브러리 생성 (Matrix.c, Ai.c 포함)
add_library(Matrix STATIC Matrix.c Ai.c)

# 실행 파일 생성 (main.c 포함)
add_executable(MatrixApp main.c)

# 실행 파일에 라이브러리 링크
target_link_libraries(MatrixApp PRIVATE Matrix)