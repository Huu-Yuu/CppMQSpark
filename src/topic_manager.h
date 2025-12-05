#ifndef C__MQSPARK_TOPIC_MANAGER_H
#define C__MQSPARK_TOPIC_MANAGER_H
#include "mqspark_abstract.h"
#include <memory>
#include <list>
#include <unordered_map>
#include <mutex>
#include "public_macro.h"
#include "topic.h"
using namespace std;
using namespace MQ;

class TopicManager
{
    SINGLETON(TopicManager)
public:
    bool AddTopic(const string& topic_name, const MQSparkShPtr& msg_iter);
    bool RemoveTopic(const string& topic_name, const MQSparkShPtr& msg_iter);
    bool PublishMsg(const Message& msg);
    void DelMsgPtr(const MQSparkShPtr& msg_iter);
private:
    unordered_map<string, unique_ptr<Topic>> topics;
    mutex mtx;
};


#endif//C__MQSPARK_TOPIC_MANAGER_H
