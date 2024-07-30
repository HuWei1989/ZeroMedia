//
// Created by Administrator on 2024/7/30.
//

#include "BaseThread.h"


void BaseThread::onStart() {
    pthread_attr_init(&tattr);
    pthread_attr_setdetachstate(&tattr, PTHREAD_CREATE_DETACHED);
    pthread_create(&tid, &tattr, function, this);
    cancelFlag.store(false);
    pthread_attr_destroy(&tattr);
}

void *BaseThread::function(void *arg) {
    auto *thread = static_cast<BaseThread *>(arg);
    //auto *thread = dynamic_cast<BaseThread *>(arg);
    thread->run();
    //delete thread;
    return nullptr;
}

void BaseThread::onStop() {
    //android中无法使用
    //pthread_cancel(tid);
    //pthread_exit()
    if (cancelFlag) {
        cancelFlag.store(true);
    }
}

void BaseThread::run() {
}