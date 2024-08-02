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
    auto thread = static_cast<BaseThread *>(arg);
    thread->run();
    thread->onStop();
    //delete thread;
    return nullptr;
}

void BaseThread::onStop() {

}

void BaseThread::onDestroy() {
    int ret = 0;
    //android中无法使用
    //pthread_cancel(tid);
    //pthread_exit()
    if (cancelFlag) {
        cancelFlag.store(true);
    }
    if ((ret = pthread_kill(tid, SIGUSR1)) != 0) {
        printf("Error cancelling thread %d, error = %d (%s) \n", tid, ret, strerror);
    }
}

void BaseThread::thread_exit_handler(int sig) {
//    if (thread != NULL) {
//        thread->onStop();
//    }
    pthread_exit(0);
}

void BaseThread::run() {
    memset(&actions, 0, sizeof(actions));
    sigemptyset(&actions.sa_mask);
    actions.sa_flags = 0;
    actions.sa_handler = thread_exit_handler;
    sigaction(SIGUSR1, &actions, NULL);
    //线程做其它操作
}