
ADD_LIBRARY(gemmlowp INTERFACE)

target_include_directories(gemmlowp INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}> $<INSTALL_INTERFACE:include>)
target_sources(gemmlowp INTERFACE fixedpoint/fixedpoint_neon.h fixedpoint/fixedpoint_sse.h fixedpoint/fixedpoint.h "internal/detect_platform.h")
install(DIRECTORY ./fixedpoint DESTINATION include)
install(DIRECTORY "./internal" DESTINATION include)
