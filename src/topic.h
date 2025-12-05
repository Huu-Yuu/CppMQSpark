#ifndef C__MQSPARK_TOPIC_H
#define C__MQSPARK_TOPIC_H
#include <memory>
#include "message_interface.h"
#include <unordered_set>
#include <mutex>
using namespace std;
using namespace MQ;

/*
 * @brief: 主题
 * */
class Topic
{
    public:
        explicit Topic(const string& topicName);
        string GetName() const;
        void AddMsgIter(const MQSparkShPtr& msg_iter);
        void Publish(const Message& msg);
        void DelMsgIter(const MQSparkShPtr& msg_iter);
        bool IsExistClent(const MQSparkShPtr& msg_iter);
    private:
        string m_name;
        unordered_set<MQSparkShPtr> m_clents;
        mutex mtx;
};


#endif//C__MQSPARK_TOPIC_H
