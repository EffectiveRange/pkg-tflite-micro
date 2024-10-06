

ADD_LIBRARY(ruy INTERFACE)

# install include headers

target_include_directories(ruy INTERFACE .)

install(DIRECTORY "./ruy" DESTINATION include)