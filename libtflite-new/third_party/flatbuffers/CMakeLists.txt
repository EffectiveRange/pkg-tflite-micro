
ADD_LIBRARY(flatbuffers INTERFACE)

target_include_directories(flatbuffers INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include>)
file(GLOB_RECURSE FLATBUFFER_HEADERS 
    "include/flatbuffers/*.h"
)
target_sources(flatbuffers INTERFACE FILE_SET HEADERS BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include FILES ${FLATBUFFER_HEADERS})

install(
    TARGETS flatbuffers
    EXPORT flatbuffersTargets
    FILE_SET HEADERS DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)