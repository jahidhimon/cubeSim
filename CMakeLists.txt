cmake_minimum_required(VERSION 3.23)

project(firstGL LANGUAGES C)

set(C_STANDARD 11)

add_executable(cubeSim main.c)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

target_link_libraries(
	cubeSim
	OpenGL::GL
	GLUT::GLUT
)
