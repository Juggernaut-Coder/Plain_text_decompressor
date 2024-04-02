cmake_minimum_required(VERSION 3.16)
#ONLY SUITABLE FOR PERSONAL PROJECTS
#COMPIER
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_C_COMPILER "gcc") # GCC version > 10 #x86_64-w64-mingw32-gcc does not work
set(CMAKE_C_STANDARD 17)  # THE DOCUMENTATION OF THIS STANDARD USED WHILE CODING   
set(CMAKE_C_STANDARD_REQUIRED ON) # Therefore this is set on
#FLAGS
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0 -ggdb3") 
set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

#PROJECT
project(A5_DECOMPRESSION LANGUAGES C ASM)
enable_language(C ASM)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib_dllist)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib_dcomp_strtok)

add_executable(DECOMPRESSION ${CMAKE_CURRENT_SOURCE_DIR}/src/main.c) #Add main.c
target_compile_options(DECOMPRESSION PUBLIC -O0 -ggdb3 -std=c17 -Wall -Wextra) # best option for debugging
target_link_libraries(DECOMPRESSION DLL DTOK) # LINK main.c and static libraries
target_include_directories(DECOMPRESSION PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib_dllist ${CMAKE_CURRENT_SOURCE_DIR}/lib_dcomp_strtok ${CMAKE_CURRENT_SOURCE_DIR}/check_runtime_error_macro) 
