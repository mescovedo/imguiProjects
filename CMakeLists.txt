cmake_minimum_required(VERSION 4.0)
project(imguiProjects)

set(CMAKE_CXX_STANDARD 20)

# --- Paths for dependencies ---
set(GLFW_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/external/glfw/include)
set(GLFW_LIB_DIR ${CMAKE_SOURCE_DIR}/external/glfw/lib)
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/external/imgui)
set(JSON_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/external/json/include)

# --- Includes ---
include_directories(${GLFW_INCLUDE_DIR})
include_directories(${IMGUI_DIR} ${IMGUI_DIR}/backends)
include_directories(${JSON_INCLUDE_DIR})

# --- ImGui sources ---
set(IMGUI_SRC
        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
        ${IMGUI_DIR}/imgui_demo.cpp
        ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
        ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

# --- Executable ---
add_executable(imguiProjects main.cpp ${IMGUI_SRC})

# --- Static linking with GLFW + OpenGL ---
target_link_libraries(imguiProjects
        ${GLFW_LIB_DIR}/libglfw3.a   # GLFW static
        opengl32                     # OpenGL (default Windows library)
)

# --- Define CONFIG_DIR for the project root ---
target_compile_definitions(imguiProjects PRIVATE CONFIG_DIR="${CMAKE_SOURCE_DIR}")
