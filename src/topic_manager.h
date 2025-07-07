#ifndef C__MQSPARK_TOPIC_MANAGER_H
#define C__MQSPARK_TOPIC_MANAGER_H
#include "mqspark_abstract.h"
#include <memory>
#include <list>
#include "public_macro.h"
#include "topic.h"
using namespace std;
using namespace MQ;
class MQSparkAbstract;
class TopicManager
{
    SINGLETON(TopicManager)
public:
    bool AddTopic(const string& topic_name, const MQSparkShPtr& msg_iter);
    bool RemoveTopic(const string& topic_name, const MQSparkShPtr& msg_iter);
    bool PublishMsg(const Message& msg);

private:
    list<Topic> topics;
};


#endif//C__MQSPARK_TOPIC_MANAGER_H
