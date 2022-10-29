cmake_minimum_required (VERSION 3.5)

project(project1-1)

add_subdirectory(data_structures)
add_subdirectory(algorithms)

add_executable(${PROJECT_NAME} src/main.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "main")

target_link_libraries(${PROJECT_NAME}
    ds::array_list
    algo::sorting
)