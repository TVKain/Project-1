project(data_structures)

add_library(${PROJECT_NAME} src/test.cpp)

add_library(ds::test ALIAS ${PROJECT_NAME})

target_include_directories( ${PROJECT_NAME}
  PUBLIC ${PROJECT_SOURCE_DIR}/include
)