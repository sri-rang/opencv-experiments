cmake_minimum_required  (VERSION 2.8)

project                 (OpenCVExperiments)
set                     (CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin/")

find_package            (OpenCV REQUIRED)

add_executable          (face_detect src/face_detect.cpp)
target_link_libraries   (face_detect ${OpenCV_LIBS})

add_executable          (show_image src/show_image.cpp)
target_link_libraries   (show_image ${OpenCV_LIBS})