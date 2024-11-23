cmake_minimum_required(VERSION 3.7)
project(dos-app)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "-O2 -ffast-math")
add_compile_options(-fpermissive)
file(GLOB sources CONFIGURE_DEPENDS "src/*.cpp")
include_directories(${CMAKE_SOURCE_DIR}/include)
add_executable(main ${sources})
set_target_properties(main PROPERTIES OUTPUT_NAME "TETRO")
target_link_libraries(main ${CMAKE_SOURCE_DIR}/allegro/lib/djgpp/liballeg.a)
target_include_directories(main PRIVATE ${CMAKE_SOURCE_DIR}/allegro/include)
add_custom_target(assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/assets
    ${CMAKE_BINARY_DIR}
)
add_custom_target(allegro_cfg
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_SOURCE_DIR}/allegro.cfg
    ${CMAKE_BINARY_DIR}/allegro.cfg
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_SOURCE_DIR}/setup.exe
    ${CMAKE_BINARY_DIR}/setup.exe
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_SOURCE_DIR}/setup.dat
    ${CMAKE_BINARY_DIR}/setup.dat    
)
add_dependencies(main assets allegro_cfg)