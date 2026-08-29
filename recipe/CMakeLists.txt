cmake_minimum_required(VERSION 3.15)
project(libaec_consumers LANGUAGES C)

find_package(libaec CONFIG REQUIRED)

add_executable(aec_consumer test_aec.c)
target_link_libraries(aec_consumer PRIVATE libaec::aec)

add_executable(sz_consumer test_sz.c)
target_link_libraries(sz_consumer PRIVATE libaec::sz)
