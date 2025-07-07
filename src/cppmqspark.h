#ifndef C__MQSPARK_CPPMQSPARK_H
#define C__MQSPARK_CPPMQSPARK_H
#include "topic_manager.h"
#include <memory>
#include "public_macro.h"
class CppMQSpark : public std::enable_shared_from_this<CppMQSpark>
{
    SMART_SINGLETON(CppMQSpark)
public:
    bool ClientSubTopic(const string& topic_name, const MQSparkShPtr& mqs_ptr);
    bool PublishMsg(const Message& msg);
    bool ClientUnsub(const string& topic_name, const MQSparkShPtr& mqs_prt);
private:
    TopicManager& topic_mgr;
};


#endif//C__MQSPARK_CPPMQSPARK_H
