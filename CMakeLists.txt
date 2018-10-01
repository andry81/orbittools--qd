cmake_minimum_required(VERSION 3.0)

include(Common)

project("qd")

set(PROJECT_LIB_NAME qd)

discover_variable(ENABLE_QD_QD_INTEGRATION STRING "enable Qd library qd_real replacement for the double")
discover_variable(ENABLE_QD_DD_INTEGRATION STRING "enable Qd library dd_real replacement for the double")


file(GLOB_RECURSE all_headers ${CMAKE_CURRENT_LIST_DIR}/include/*.h*)
file(GLOB_RECURSE all_sources ${CMAKE_CURRENT_LIST_DIR}/src/*.c*)

add_library(${PROJECT_LIB_NAME} STATIC ${all_headers};${all_sources})

initialize_library_target_defaults(${PROJECT_LIB_NAME} "32bit")

source_groups_from_dir_list("Header Files" FILES ${CMAKE_CURRENT_LIST_DIR}/include *.h*)
source_groups_from_dir_list("Source Files" FILES ${CMAKE_CURRENT_LIST_DIR}/src *.c*)

target_include_directories(${PROJECT_LIB_NAME}
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include
    ${CMAKE_CURRENT_LIST_DIR}
)

if (ENABLE_QD_QD_INTEGRATION)
  add_target_compile_definitions(${PROJECT_LIB_NAME} *
    PUBLIC
      ENABLE_QD_QD_INTEGRATION
  )
endif()
if (ENABLE_QD_DD_INTEGRATION)
  add_target_compile_definitions(${PROJECT_LIB_NAME} *
    PUBLIC
      ENABLE_QD_DD_INTEGRATION
  )
endif()
