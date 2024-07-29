//
// Created by Administrator on 2024/7/18.
//

#include <jni.h>
#include "android/log.h"
#include "core/AndroidLog.h"
#include "core/Config.h"
#include <sys/stat.h>
#include <unistd.h>
#include <fstream>
#include <sys/stat.h>
#include <cstdlib>
#include <string>
#include "biz/FFJavaCallback.h"

using namespace std;
#ifdef __cplusplus
extern "C" {
#endif

FFJavaCallback theJAVACall;

void JstringToChar(JNIEnv *env, jstring jstr, string &s) {
    if (jstr == NULL) {
        return;
    }
    char *rtn = NULL;
    jclass clsstring = env->FindClass("java/lang/String");
    jstring strencode = env->NewStringUTF("GB2312");
    jmethodID mid = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
    jbyteArray barr = (jbyteArray) env->CallObjectMethod(jstr, mid, strencode);
    jsize alen = env->GetArrayLength(barr);
    jbyte *ba = env->GetByteArrayElements(barr, JNI_FALSE);

    if (alen > 0) {
        rtn = (char *) malloc(alen + 1);
        memcpy(rtn, ba, alen);
        rtn[alen] = 0;
    }
    env->ReleaseByteArrayElements(barr, ba, 0);
    s = rtn;
    free(rtn);
}


JNIEXPORT jint JNICALL Java_org_windmill_zeromedia_core_Jni_initMedia
        (JNIEnv *jEnv, jobject jCls) {
    int ret = 0;

    return ret;
}


extern "C"
JNIEXPORT jint JNICALL
Java_org_windmill_zeromedia_core_Jni_loadFile(JNIEnv *env, jobject thiz, jstring path) {
    int ret = 0;
    struct stat buffer;
    AVFormatContext *ifmt_ctx;
    const char *filePath = env->GetStringUTFChars(path, 0);
    if (stat(filePath, &buffer) == 0) {
        ret = ERROR_FILE_MISSING;
        return (jint) ret;
    }
//    if((ret = avformat_open_input(&ifmt_ctx, filePath, NULL, NULL)) < 0){
//        LogE("Cannot open input file\n");
//        return ret;
//    }
    env->ReleaseStringUTFChars(path, filePath);
    return (jint) ret;
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_org_windmill_zeromedia_core_Jni_setMediaCallback(JNIEnv *env, jobject thiz, jobject callback) {
    if (!theJAVACall.initCall(env, thiz, "messageCallback", "(I[B)V")) {
        return false;
    }
    return true;
}

#ifdef __cplusplus
}
#endif


