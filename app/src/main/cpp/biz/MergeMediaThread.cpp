//
// Created by Administrator on 2024/7/30.
//

#include "MergeMediaThread.h"

MergeMediaThread::MergeMediaThread(vector<string> &fileList, string &outFile) {
    this->fileList = fileList;
    this->outFilePath = outFile;
}


void MergeMediaThread::run() {
    BaseThread::run();
    for (auto itertor = fileList.begin(); itertor != fileList.end(); itertor++) {
        struct stat buffer;
        if (stat((*itertor).c_str(), &buffer) == 0) {
            LogE("%s存在", (*itertor).c_str());
            //AVFormatContext *mFormatCtx = avformat_alloc_context();
            AVFormatContext *ifmt_ctx = nullptr;
            if (avformat_open_input(&ifmt_ctx, (*itertor).c_str(), NULL, NULL) < 0) {
                LogE("文件读取失败%s", (*itertor).c_str());
                return;
            }
            if (avformat_find_stream_info(ifmt_ctx, nullptr) < 0) {
                return;
            }
            mediaCtxMap.emplace(*itertor, ifmt_ctx);
        } else {
            LogE("%s不存在", (*itertor).c_str());
        }
    }
    //输出文件上下文
    avformat_alloc_output_context2(&outFormatCtx, nullptr, nullptr, this->outFilePath.c_str());
    //av_init_packet(&pkt);
    pkt = av_packet_alloc();

    return;
}

void MergeMediaThread::onStop() {
    BaseThread::onStop();
    LogE("onStop  释放内存");
    if (pkt != nullptr) {
        //清理数据
        av_packet_unref(pkt);
        //释放
        av_packet_free(&pkt);
    }
    //清理输出上下文
    if (outFormatCtx != nullptr) {
        avformat_free_context(outFormatCtx);
    }
    // 释放资源
    for (auto iter = mediaCtxMap.begin(); iter != mediaCtxMap.end();) {
        auto first = iter->first;
        auto second = iter->second;
        string().swap(first);
        if (second) {
            avformat_close_input(&second);
            avformat_free_context(second);
            second = NULL;
            mediaCtxMap.erase(iter++);      // 从map中删除元素，注意iter++的写法
        }
    }
    mediaCtxMap.clear();
    string().swap(this->outFilePath);
    ///free(mediaCtxMap);
}

MergeMediaThread::~MergeMediaThread() {
    for (auto iter = fileList.begin(); iter != fileList.end();) {
        string().swap(*iter);
        fileList.erase(iter++);
    }
    this->fileList.clear();

}