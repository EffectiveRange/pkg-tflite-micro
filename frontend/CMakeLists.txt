file(GLOB_RECURSE SOURCES 
    "src/*.cpp"
    "src/*.cc"
    "src/*.c"
)

list(FILTER SOURCES EXCLUDE REGEX ".*_test\\.cc$")

ER_ADD_STATIC_LIBRARY(frontend SOURCES ${SOURCES})
target_include_directories(frontend PUBLIC include PRIVATE include/frontend)
target_link_libraries(frontend PUBLIC tflite-micro kissfft_i16 kissfft_i8)