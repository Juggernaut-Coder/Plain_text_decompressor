add_library(DTOK STATIC "dtok.c")
target_compile_options(DTOK PUBLIC -O0 -ggdb3 -std=c17 -Wall -Wextra)
target_include_directories(DTOK PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../check_runtime_error_macro)