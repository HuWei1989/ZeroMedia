cmake_minimum_required(VERSION 3.22.1)

project("ZeroMedia")
#include_directories(include)

#库文件地址
set(ffmpeg_dir ${CMAKE_CURRENT_SOURCE_DIR}/libs/${ANDROID_ABI})
set(jni_dir ${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp)

message("1=============================================================:" ${ffmpeg_dir})
message("2=============================================================:" ${jni_dir})


add_library(avcodec SHARED IMPORTED)
set_target_properties(avcodec PROPERTIES IMPORTED_LOCATION ${ffmpeg_dir}/libavcodec.so)

add_library(avfilter SHARED IMPORTED)
set_target_properties(avfilter PROPERTIES IMPORTED_LOCATION ${ffmpeg_dir}/libavfilter.so)

add_library(avformat SHARED IMPORTED)
set_target_properties(avformat PROPERTIES IMPORTED_LOCATION ${ffmpeg_dir}/libavformat.so)

add_library(avutil SHARED IMPORTED)
set_target_properties(avutil PROPERTIES IMPORTED_LOCATION ${ffmpeg_dir}/libavutil.so)

add_library(aac SHARED IMPORTED)
set_target_properties(aac PROPERTIES IMPORTED_LOCATION ${ffmpeg_dir}/libfdk-aac.so)

add_library(swresample SHARED IMPORTED)
set_target_properties(swresample PROPERTIES IMPORTED_LOCATION ${ffmpeg_dir}/libswresample.so)

add_library(swscale SHARED IMPORTED)
set_target_properties(swscale PROPERTIES IMPORTED_LOCATION ${ffmpeg_dir}/libswscale.so)

add_library(x264 SHARED IMPORTED)
set_target_properties(x264 PROPERTIES IMPORTED_LOCATION ${ffmpeg_dir}/libx264.so)

add_library(x265 SHARED IMPORTED)
set_target_properties(x265 PROPERTIES IMPORTED_LOCATION ${ffmpeg_dir}/libx265.so)

file(GLOB my_source_path
        ${jni_dir}/*.cpp
        ${jni_dir}/*.h
        ${jni_dir}/*.c)
#
add_library(hwmedia SHARED ${my_source_path})
#add_library(ffmpegjni-lib SHARED ${jni_dir}/ffmedia.cpp)

find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log
)

target_link_libraries(
        hwmedia
        android
        ${log-lib}
        avcodec
        avfilter
        avformat
        avutil
        aac
        swresample
        swscale
        x264
        x265
        #调用 OpenSLES 需要链接该库
        OpenSLES
        GLESv2 EGL)


#target_link_libraries(${CMAKE_PROJECT_NAME}
#        android
#        ${log-lib}
#        #调用 OpenSLES 需要链接该库
#        OpenSLES
#        GLESv2 EGL)