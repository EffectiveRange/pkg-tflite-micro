
add_library(kiss_fft INTERFACE)
target_include_directories(kiss_fft INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}> $<INSTALL_INTERFACE:include>)
target_sources(kiss_fft INTERFACE kiss_fft.c kiss_fft.h _kiss_fft_guts.h)
install(TARGETS kiss_fft 
        EXPORT kiss_fftTargets)
# install(DIRECTORY ./tools DESTINATION include)
# install(FILES _kiss_fft_guts.h kiss_fft.h DESTINATION include)
