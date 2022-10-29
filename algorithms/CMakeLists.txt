project(algorithms)

add_library(${PROJECT_NAME} src/sorting.cpp)
add_library(algo::sorting ALIAS ${PROJECT_NAME})

target_include_directories( ${PROJECT_NAME}
	PUBLIC ${PROJECT_SOURCE_DIR}/include
)