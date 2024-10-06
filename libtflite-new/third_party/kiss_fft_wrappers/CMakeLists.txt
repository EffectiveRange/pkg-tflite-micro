

ER_ADD_STATIC_LIBRARY(kissfft_i8 SOURCES src/kiss_fft_int8.cc)
target_link_libraries(kissfft_i8 PUBLIC kiss_fft)
target_include_directories(kissfft_i8 PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include>)

ER_ADD_STATIC_LIBRARY(kissfft_i16 SOURCES src/kiss_fft_int16.cc)
target_link_libraries(kissfft_i16 PUBLIC kiss_fft)
target_include_directories(kissfft_i16 PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include>)

ER_ADD_STATIC_LIBRARY(kissfft_i32 SOURCES src/kiss_fft_int32.cc)
target_link_libraries(kissfft_i32 PUBLIC kiss_fft)
target_include_directories(kissfft_i32 PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include>)

ER_ADD_STATIC_LIBRARY(kissfft_float SOURCES src/kiss_fft_float.cc)
target_link_libraries(kissfft_float PUBLIC kiss_fft)
target_include_directories(kissfft_float PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include>)
