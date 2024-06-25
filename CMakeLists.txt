cmake_minimum_required(VERSION 3.18)

project(
  print-html
  VERSION 0.0.1
  LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
include(Cache)
include(Sanitizers)
include(Warnings)

find_package(Qt6 REQUIRED COMPONENTS Core WebEngineWidgets)

qt_standard_project_setup()

qt_add_library(${PROJECT_NAME}
  src/printhtml.cpp
  src/printhtml_wrapper.cpp
)
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME} PUBLIC Qt6::Core Qt::PrintSupport Qt::WebEngineWidgets)

enable_sanitizers(${PROJECT_NAME})
set_project_warnings(${PROJECT_NAME})

add_executable(${PROJECT_NAME}_test src/main.c)
target_link_libraries(${PROJECT_NAME}_test PUBLIC ${PROJECT_NAME})
