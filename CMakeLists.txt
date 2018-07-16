cmake_minimum_required(VERSION 3.0)

include(Common)

project("qd")

set(PROJECT_LIB_NAME qd)

file(GLOB_RECURSE all_headers ${CMAKE_CURRENT_LIST_DIR}/include/*.h*)
file(GLOB_RECURSE all_sources ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)

add_library(${PROJECT_LIB_NAME} STATIC ${all_headers};${all_sources})

source_groups_from_dir_list("Header Files" FILES ${CMAKE_CURRENT_LIST_DIR}/include *.h*)
source_groups_from_dir_list("Source Files" FILES ${CMAKE_CURRENT_LIST_DIR}/src *.cpp)

target_include_directories(${PROJECT_LIB_NAME}
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include
    ${CMAKE_CURRENT_LIST_DIR}
)

if(GCC)
  add_target_compile_definitions(${PROJECT_LIB_NAME} DEBUG
    PUBLIC
      _DEBUG
  )

  add_target_compile_properties(${PROJECT_LIB_NAME} DEBUG
    -g
  )

  add_target_compile_properties(${PROJECT_LIB_NAME} *
    -m32        # compile 32 bit target on 64 bit host
  )

  add_target_link_properties(${PROJECT_LIB_NAME} *
    -m32        # link 32 bit target on 64 bit host
  )
endif()
