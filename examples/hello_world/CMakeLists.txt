
ER_ADD_EXECUTABLE(tflite_hello SOURCES 
    hello_world_test.cc 
    models/hello_world_float_model_data.cc
    models/hello_world_int8_model_data.cc
    )

target_include_directories(tflite_hello PRIVATE .)

target_link_libraries(tflite_hello PRIVATE tflite-micro)