#ifndef CONSUMER_H
#define CONSUMER_H
#include "message_interface.h"
#include <memory>
#include <iostream>
#include <mutex>
using namespace MQ;
using namespace std;

class Consumer
{
public:
    Consumer() : mqs(MessageInterface::Create<MessageInterface>())
    {
        mqs->RegMsgHandleCallback(&MessageHandle);
    }

    ~Consumer()
    {
//        mqs->UnsubTopicAll();
        cout << " ------- UnsubTopicAll -------" << endl;
    }

    void Send(const int& i, const string& topic_name)
    {
        string i_str = to_string(i);
        Message msg(i_str, topic_name);
        mqs->PublishMessage(msg);
    }

    void UnsubTopic(const string& topic_name)
    {
         mqs->UnsubTopic(topic_name);
    }

    void Listen(const string& topic_name)
    {
        mqs->SubTopic(topic_name);

    }

    static void MessageHandle(const Message &msg)
    {
        mutex tx;
        tx.lock();
        count ++;
        cout << "Consumer: ----- Get Msg : -----" << endl;
        cout << "topic: " << msg.topic_name << endl;
        cout << "msg: " << msg.content << endl;
        cout << "count = "<< count << endl;
        tx.unlock();
    }
private:
    static int count;
    MQSparkShPtr mqs;
};


#endif
