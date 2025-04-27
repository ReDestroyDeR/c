project(merge_sort C)

add_executable(
        merge_sort main.c
        msort.c
        msort.h
        ../debug.h
)

target_compile_definitions(merge_sort PRIVATE DEBUG_ON=1)