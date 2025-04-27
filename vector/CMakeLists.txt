project(vector C)

add_executable(
        vector main.c
        vector.c
        vector.h
)

target_compile_definitions(vector PRIVATE DEBUG_ON=1)