//
// Created by Administrator on 2024/7/30.
//

#include "MergeMediaThread.h"

MergeMediaThread::MergeMediaThread(vector<string> &fileList)  {
    this->fileList = fileList;
}


void MergeMediaThread::run() {
    BaseThread::run();
    for (auto itertor = fileList.begin(); itertor != fileList.end(); itertor++) {
        struct stat buffer;
        if (stat((*itertor).c_str(), &buffer) == 0) {
            LogE("%s存在", (*itertor).c_str());
            AVFormatContext *mFormatCtx = avformat_alloc_context();
            mediaCtxMap.emplace(*itertor, mFormatCtx);
        } else {
            LogE("%s不存在", (*itertor).c_str());
        }
    }

    return;
}

void MergeMediaThread::onStop() {
    BaseThread::onStop();
    // 释放资源
    for (auto iter = mediaCtxMap.begin(); iter != mediaCtxMap.end();) {
        auto first = iter->first;
        auto second = iter->second;
        string().swap(first);
        if (second) {
            avformat_close_input(&second);
            second = NULL;
            mediaCtxMap.erase(iter++);      // 从map中删除元素，注意iter++的写法
        }
    }
    mediaCtxMap.clear();
    ///free(mediaCtxMap);
}

MergeMediaThread::~MergeMediaThread(){
    for (auto iter = fileList.begin(); iter != fileList.end();) {
        string().swap(*iter);
        fileList.erase(iter++);
    }
    this->fileList.clear();

}