cmake_minimum_required(VERSION 3.7)
project(dos-app)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "-O3 -ffast-math")
add_compile_options(-fpermissive)
file(GLOB sources CONFIGURE_DEPENDS "src/*.cpp")
include_directories(${CMAKE_SOURCE_DIR}/include)
add_executable(main ${sources})
target_link_libraries(main ${CMAKE_SOURCE_DIR}/allegro/lib/djgpp/liballeg.a)
target_link_libraries(main ${CMAKE_SOURCE_DIR}/jgmod/lib/libjgmod.a)
target_include_directories(main PRIVATE ${CMAKE_SOURCE_DIR}/allegro/include)
target_include_directories(main PRIVATE ${CMAKE_SOURCE_DIR}/jgmod/include)
add_custom_target(assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/assets
    ${CMAKE_BINARY_DIR}
)
add_dependencies(main assets)