add_library(DLL STATIC "decompression_list.c")
target_include_directories(DLL PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../cdll_macros ${CMAKE_CURRENT_SOURCE_DIR}/../check_runtime_error_macro)
target_compile_options(DLL PUBLIC -O0 -ggdb3 -std=c17 -Wall -Wextra)