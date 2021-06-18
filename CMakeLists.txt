cmake_minimum_required(VERSION 3.17)
project(ProjetTransverse)

set(CMAKE_CXX_STANDARD 14)

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)

#Can manually add the sources using the set command as follows:
#set(SOURCES_CPP
#        src/animation.cpp
#        src/first_prog.cpp
#        src/forms.cpp
#        src/geometry.cpp
#        src/cube_face.cpp
#        src/cuboid.cpp)

#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES_CPP "./src/*.cpp")

#set(HEADERS_HPP
#        include/animation.h
#        include/forms.h
#        include/geometry.h
#        include/cube_face.h
#        include/sphere.h
#        include/cuboid.h
#        )

# Adding headers here make them part of the project for the IDE.
# They can be safely be removed after
add_executable(${PROJECT_NAME} ${SOURCES_CPP})

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES})
target_include_directories(${PROJECT_NAME} PRIVATE "./include")
