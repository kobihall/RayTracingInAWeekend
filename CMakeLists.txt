cmake_minimum_required(VERSION 3.10)

project(imgui_boilerplate)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++14 " )

include_directories(imgui)

file(GLOB src_files "*.hpp" "*.cpp")
file(GLOB imgui_src "imgui/*.cpp" "imgui/backends/imgui_impl_glfw.cpp" "imgui/backends/imgui_impl_vulkan.cpp")
add_executable(${PROJECT_NAME} ${src_files} ${imgui_src})

find_package(Vulkan REQUIRED)
find_package(glfw3 3.3 REQUIRED)

if (VULKAN_FOUND)
    message(STATUS "Found Vulkan, Including and Linking now")
    include_directories(${Vulkan_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${Vulkan_LIBRARIES} glfw)
endif (VULKAN_FOUND)