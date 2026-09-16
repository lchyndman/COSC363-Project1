cmake_minimum_required(VERSION 2.8)

project(363Assignment1)

add_executable(Factory.out Factory.cpp legoman.cpp skybox.cpp conveyor.cpp particles.cpp gear.cpp)

set(OpenGL_GL_PREFERENCE LEGACY)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

target_link_libraries( Factory.out ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} )
