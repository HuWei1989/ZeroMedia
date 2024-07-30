//
// Created by Administrator on 2024/7/30.
//

#include "MergeMediaThread.h"

MergeMediaThread::MergeMediaThread(vector<string> *fileList) : BaseThread() {

}

void MergeMediaThread::run() {
    if (cancelFlag.load()) {
        goto finish;
    }
    finish:
    return;
}