add_library(
        imgui
        STATIC
        ${CMAKE_CURRENT_LIST_DIR}/imgui.cpp
        ${CMAKE_CURRENT_LIST_DIR}/imgui_demo.cpp
        ${CMAKE_CURRENT_LIST_DIR}/imgui_draw.cpp
        ${CMAKE_CURRENT_LIST_DIR}/imgui_widgets.cpp
        ${CMAKE_CURRENT_LIST_DIR}/examples/imgui_impl_glfw.cpp
        ${CMAKE_CURRENT_LIST_DIR}/examples/imgui_impl_opengl3.cpp
        ${CMAKE_CURRENT_LIST_DIR}/examples/imgui_impl_opengl3.h  # Not sure if you need to include these here
        ${CMAKE_CURRENT_LIST_DIR}/examples/imgui_impl_glfw.h
        ${CMAKE_SOURCE_DIR}/external/glad/src/glad.cpp
        )

target_include_directories(imgui PUBLIC .)
target_include_directories(imgui PUBLIC ./backends )

add_compile_definitions(IMGUI_IMPL_OPENGL_LOADER_GLAD)  # Sometimes, MSVC doesn't have correct preprocessor definitions

# GLAD and GLFW should have already been found, otherwise the impl files won't work.
target_link_libraries(imgui glfw3)

#target_link_libraries(imgui glad)

set_target_properties(imgui PROPERTIES FOLDER "imgui")


