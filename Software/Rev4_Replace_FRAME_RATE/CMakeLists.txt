add_executable(BGT60U_revised2 BGT60U_revised2.c)
find_package (Python2 REQUIRED COMPONENTS Interpreter Development)

include_directories(${Python2_INCLUDE_DIRS} ${Python2_LIBRARY_DIRS})
target_link_libraries(BGT60U_revised2 sdk_fmcw sdk_avian ${Python2_LIBRARIES} sdk_algo)

