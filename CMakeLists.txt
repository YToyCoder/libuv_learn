cmake_minimum_required(VERSION 3.27.0)

project(learnLibuv)

set(CMAKE_GENERATOR "MinGW Makefiles")
set(var_libuv_path "D:/App/libuv/")

include_directories(${var_libuv_path}/include )

#cplOption: main | cli
if ("main" STREQUAL ${cplOption})
  message(STATUS "build main proj")
  add_executable(main main.c)
  target_link_libraries(main ${var_libuv_path}/libuv.lib)
elseif ("cli" STREQUAL ${cplOption})
  message(STATUS "build cli proj")
  add_executable(cli cli.c)
  target_link_libraries(cli ${var_libuv_path}/libuv.lib)
endif()
