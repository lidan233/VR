cmake_minimum_required(VERSION 3.17)
project(VR)

set(CMAKE_CXX_STANDARD 14)

#find_package(imgui REQUIRED)

include(cmake/LidanBuild.cmake)
include(cmake/LidanBase.cmake)

ADD_SUBSRC(utildir util)
ADD_SUBSRC(shadertoydir shadertoy)
ADD_SUBSRC(opengldir opengl)



Lidan_ADD_LIB(PATH "${CMAKE_CURRENT_SOURCE_DIR}/external/glfw/" INCLUDEDIRS includedir MSVC "TRUE" SOURCEDIR glfwsrc COMPONENTS "glfw3")
Lidan_ADD_SRC(PATH "${CMAKE_CURRENT_SOURCE_DIR}/external/glad/" SOURCEDIR gladsrc)


include_directories(util/
        shadertoy/
        opengl/
        external/glfw/include
        external/glad
        external/SDL
        external/glm/
        external/eigen/
        external/imgui/
        external/stb/
        external/imgui/examples)
add_subdirectory(external/imgui/)

IF (WIN32)
    include_directories(external/SDL/lib-vc2019/include/)
    link_directories(external/SDL/lib-vc2019/lib/x64)
    message(STATUS "using windows external")
else()
    include_directories(/usr/local/Cellar/sdl2/2.0.9_1/include/)
    link_directories(/usr/local/Cellar/sdl2/2.0.9_1/lib)
    message(STATUS "using mac/linux external")
endif()



add_executable(VR
        ${utildir}
        ${shadertoydir}
        ${opengldir}
        main.cpp opengl/Sample2D.cpp opengl/Sample2D.h util/util.h render/Camera.cpp render/Camera.h geometry/Vertex.cpp geometry/Vertex.h util/Lmath.h util/Matrix.h geometry/Size.cpp geometry/Size.h geometry/Rectangle.cpp geometry/Rectangle.h render/EulerAngles.cpp render/EulerAngles.h render/Quaternion.cpp render/Quaternion.h render/Timer.cpp render/Timer.h util/FileReader.h opengl/Window.cpp opengl/Window.h opengl/Shader.cpp opengl/Shader.h opengl/BufferObject.cpp opengl/BufferObject.h opengl/FrameBuffer.cpp opengl/FrameBuffer.h)



target_link_libraries(VR imgui glfw3 SDL2)