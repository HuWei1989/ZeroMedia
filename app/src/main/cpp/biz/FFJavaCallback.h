//
// Created by Administrator on 2024/7/29.
//

#ifndef ZEROMEDIA_FFJAVACALLBACK_H
#define ZEROMEDIA_FFJAVACALLBACK_H
using namespace std;
#include <jni.h>

class FFJavaCallback {
public:
    FFJavaCallback();
    ~FFJavaCallback();
    bool initCall(JNIEnv* pEnv,jobject obj,const char* funName,const char* param);

    void playProgress(int currentTime,int totalTime);
private:
    JavaVM *m_jvm;
    JNIEnv* m_pEnv;
    jobject m_obj;
    jclass m_pClass;
    jmethodID m_fun;
   void releaseCall();
};


#endif //ZEROMEDIA_FFJAVACALLBACK_H
