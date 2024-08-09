//
// Created by Administrator on 2024/7/29.
//

#ifndef ZEROMEDIA_CONFIG_H
#define ZEROMEDIA_CONFIG_H
extern "C" {
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libavutil/mem.h"
#include "libavutil/pixdesc.h"
#include "libavutil/hwcontext.h"
#include "libavutil/opt.h"
#include "libavutil/avassert.h"
#include "libavutil/imgutils.h"
}

#include <pthread.h>
//初始化失败
#define ERROR_INIT_FAILED -1000

#define ERROR_FILE_MISSING  -1001
//文件格式读取失败
#define ERROR_FILE_MISSING -1002

#define FFMPEGA_OK 0


#endif //ZEROMEDIA_CONFIG_H
