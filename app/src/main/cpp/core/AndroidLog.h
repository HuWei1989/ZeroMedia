//
// Created by Administrator on 2024/7/29.
//

#ifndef ZEROMEDIA_ANDROIDLOG_H
#define ZEROMEDIA_ANDROIDLOG_H

#include "android/log.h"

extern "C" {
#include "jni.h"
}

//android打印
#define LogE(...) __android_log_print(ANDROID_LOG_ERROR,"Android-ZeroMedia",__VA_ARGS__)

#endif //ZEROMEDIA_ANDROIDLOG_H
