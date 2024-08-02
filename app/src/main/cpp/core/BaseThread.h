//
// Created by Administrator on 2024/7/30.
//

#ifndef ZEROMEDIA_BASETHREAD_H
#define ZEROMEDIA_BASETHREAD_H

#include <pthread.h>
#include <csignal>
#include <unistd.h>
#include <memory.h>
#include <signal.h>
#include <atomic>

class BaseThread {
public:

    virtual void onStart();

    virtual void run();

    virtual void onStop();

    virtual void onDestroy();

    static void *function(void *);

    typedef void *(*Func)(void *);

    Func callback = nullptr;

    std::atomic<bool> cancelFlag;

protected:



    pthread_t tid;

    pthread_attr_t tattr;

    static void thread_exit_handler(int sig);

    struct sigaction actions;

};


#endif //ZEROMEDIA_BASETHREAD_H
