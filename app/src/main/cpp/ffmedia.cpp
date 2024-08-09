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
#include <cstdlib>
#include <string>
#include "biz/FFJavaCallback.h"
#include <vector>
#include "biz/MergeMediaThread.h"
#include "core/BaseThread.h"

using namespace std;
#ifdef __cplusplus
extern "C" {
#endif

FFJavaCallback theJAVACall;

//合并操作
MergeMediaThread *mergeThread = NULL;

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

extern "C"
JNIEXPORT jint JNICALL Java_org_windmill_zeromedia_core_Jni_initMedia
        (JNIEnv *jEnv, jobject jCls) {
    int ret = 0;
    ret = avformat_network_init();
    return ret;
}


extern "C"
JNIEXPORT jint JNICALL
Java_org_windmill_zeromedia_core_Jni_loadFile(JNIEnv *env, jobject thiz, jobject arrayList) {
    int ret = 0;
    jclass arrayListClass = env->GetObjectClass(arrayList);
    jmethodID sizeMethod = env->GetMethodID(arrayListClass, "size", "()I");
    jmethodID getMethod = env->GetMethodID(arrayListClass, "get", "(I)Ljava/lang/Object;");
    // 获取 ArrayList 的大小
    jint size = env->CallIntMethod(arrayList, sizeMethod);
    LogE("文件大小：%d", size);
    // 创建一个 C++ 的 std::vector<std::string>
    vector<string> fileList;
    fileList.clear();
    fileList.shrink_to_fit();
    for (int i = 0; i < size; i++) {
        jobject element = env->CallObjectMethod(arrayList, getMethod, i);
        const char *str = env->GetStringUTFChars((jstring) element, NULL);
        int len = strlen(str) + 1;
        //地址没发生变化
        char *path = (char *) malloc(len);
        memcpy(path, str, len);
        fileList.push_back(string(path));
        env->ReleaseStringUTFChars((jstring) element, str);
        env->DeleteLocalRef(element);
    }
    string dstFile = "";
    //开始线程的处理
    mergeThread = new MergeMediaThread(fileList, dstFile);
    mergeThread->onStart();
    LogE("主线程=%d", std::this_thread::get_id());
    if (arrayListClass) {
        env->DeleteLocalRef(arrayListClass);
        arrayListClass = NULL;
    }
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

extern "C"
JNIEXPORT jboolean JNICALL
Java_org_windmill_zeromedia_core_Jni_mergeMedia(JNIEnv *env, jobject thiz, jobject path_list) {
    return true;
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_org_windmill_zeromedia_core_Jni_stopMergeMedia(JNIEnv *env, jobject thiz) {
    if (mergeThread) {
        mergeThread->onStop();
    }
    return true;
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_org_windmill_zeromedia_core_Jni_segMedia(JNIEnv *env, jobject thiz, jobject path_list) {
    // TODO: implement segMedia()
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_org_windmill_zeromedia_core_Jni_stopSegMedia(JNIEnv *env, jobject thiz) {
    return false;
}

#ifdef __cplusplus
}
#endif


