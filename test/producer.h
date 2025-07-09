#ifndef PRODUCER_H
#define PRODUCER_H
#include "message_interface.h"
#include <iostream>
#include <string>
using namespace MQ;
using namespace std;
class Producer
{
public:
    Producer()
    {
        init();
    }

    void init()
    {
        mqs = MessageInterface::Create<MessageInterface>();
        mqs->RegMsgHandleCallback(&MessageHandle);
    }

    void Send(const int& i, const string& topic_name)
    {
        string i_str = to_string(i);
        Message msg;
        msg.content = i_str;
        msg.topic_name = topic_name;
        mqs->PublishMessage(msg);
    }

    static void MessageHandle(const Message &msg)
    {
        count ++;
        cout << "Producer: ----- Get Msg : -----" << endl;
        cout << "topic: " << msg.topic_name << endl;
        cout << "msg: " << msg.content << endl;
        cout << "count = "<< count << endl;
    }
private:
    static int count;
    MQSparkShPtr mqs;
};



#endif
