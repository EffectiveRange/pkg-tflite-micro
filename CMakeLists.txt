cmake_minimum_required(VERSION 3.29)
include(ERBuild NO_POLICY_SCOPE)
include(GenerateExportHeader)
include(CMakePackageConfigHelpers)

set(libtflite_micro_VERSION 1.0.4)
project(LibTfliteMicro VERSION ${libtflite_micro_VERSION} DESCRIPTION "Pre-building and Packaging tflite-micro library" )

set(CMAKE_COMPILE_WARNING_AS_ERROR ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

ER_DEPS()

add_subdirectory(third_party)

file(GLOB_RECURSE SIGNAL_SOURCES 
    "signal/*.cpp"
    "signal/*.cc"
    "signal/*.c"
)

file(GLOB_RECURSE TF_SOURCES 
    "tensorflow/*.cpp"
    "tensorflow/*.cc"
    "tensorflow/*.c"
)


ER_ADD_STATIC_LIBRARY(tflite-micro SOURCES ${SIGNAL_SOURCES}  ${TF_SOURCES})

target_include_directories(tflite-micro PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}> $<INSTALL_INTERFACE:include>)

target_compile_definitions(tflite-micro PUBLIC TF_LITE_STATIC_MEMORY=1)

target_link_libraries(tflite-micro PUBLIC ruy kissfft_i16 kissfft_i32 kissfft_float gemmlowp flatbuffers)

install(DIRECTORY tensorflow DESTINATION include 
PATTERN "*.c" EXCLUDE
PATTERN "*.cc" EXCLUDE
PATTERN "*.cpp" EXCLUDE
PATTERN "*.cxx" EXCLUDE
    )

install(DIRECTORY signal DESTINATION include 
PATTERN "*.c" EXCLUDE
PATTERN "*.cc" EXCLUDE
PATTERN "*.cpp" EXCLUDE
PATTERN "*.cxx" EXCLUDE
    )

add_subdirectory(examples)

add_subdirectory(frontend)

install(FILES libfrontend.pc tflite-micro.pc DESTINATION ${CMAKE_INSTALL_DATADIR}/pkgconfig/)

ER_PACK()
