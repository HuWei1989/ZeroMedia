//
// Created by Administrator on 2024/7/30.
//

#ifndef ZEROMEDIA_MERGEMEDIATHREAD_H
#define ZEROMEDIA_MERGEMEDIATHREAD_H

#include "../core/Config.h"
#include "../core/BaseThread.h"
#include "../core/AndroidLog.h"
#include <sys/stat.h>
#include <string>
#include <vector>
#include <map>

using namespace std;

class MergeMediaThread : public BaseThread {
public:

    vector<string> fileList;

    MergeMediaThread(vector<string> &fileList, string &outFile);

    ~MergeMediaThread();

    void run() override;

    /**
     * 在结束线程前释放线程操作的内存
     * 子线程内操作
     */
    void onStop() override;

private:
    map<string, AVFormatContext *> mediaCtxMap;
    //输出的文件
    string outFilePath;
    //输出文件的上下文
    AVFormatContext *outFormatCtx = nullptr;
    AVPacket *pkt = nullptr;
};


#endif //ZEROMEDIA_MERGEMEDIATHREAD_H
