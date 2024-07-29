//
// Created by Administrator on 2024/7/29.
//

#include "FFJavaCallback.h"

FFJavaCallback::FFJavaCallback() {
    m_jvm = NULL;
    m_pEnv = NULL;
    m_obj = NULL;
    m_pClass = NULL;
    m_fun = NULL;
}

FFJavaCallback::~FFJavaCallback() {
    releaseCall();
}

void FFJavaCallback::releaseCall() {
    if (m_pEnv) {
        if (m_pClass) {
            m_pEnv->DeleteLocalRef(m_pClass);
            m_pClass = NULL;
        }
        if (m_obj) {
            m_pEnv->DeleteLocalRef(m_obj);
            m_obj = NULL;
        }
        m_pEnv = NULL;
    }
}

bool FFJavaCallback::initCall(JNIEnv *pEnv, jobject obj, const char *funName, const char *param) {
    releaseCall();
    m_pClass = pEnv->GetObjectClass(obj);
    if (m_pClass == NULL) {
        return false;
    }

    m_fun = pEnv->GetMethodID(m_pClass, funName, param);
    //m_fun = pEnv->GetMethodID(m_pClass,"fun","()V");
    if (m_fun == NULL) {
        return false;
    }

    m_obj = (*pEnv).NewGlobalRef(obj);
    m_pEnv = pEnv;
    pEnv->GetJavaVM(&m_jvm);
    return true;
}

void FFJavaCallback::playProgress(int currentTime, int totalTime) {
    if (!m_obj) {
        return;
    }
    JNIEnv *env = NULL;
    m_jvm->AttachCurrentThread(&env, 0);
    env->CallVoidMethod(m_obj, m_fun, 0.1f, 10, 100);
    m_jvm->DetachCurrentThread();
}

