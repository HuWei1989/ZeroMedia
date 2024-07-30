//
// Created by Administrator on 2024/7/30.
//

#ifndef ZEROMEDIA_MERGEMEDIATHREAD_H
#define ZEROMEDIA_MERGEMEDIATHREAD_H

#include "../core/Config.h"
#include "../core/BaseThread.h"
#include <string>
#include <vector>

using namespace std;

class MergeMediaThread : public BaseThread {
public:

    vector<string> cppVector;

    MergeMediaThread(vector<string> *fileList);

    ~MergeMediaThread();

    void run() override;


private:

};


#endif //ZEROMEDIA_MERGEMEDIATHREAD_H
