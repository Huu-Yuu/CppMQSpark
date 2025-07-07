#include "cppmqspark.h"

CppMQSpark::CppMQSpark() : topic_mgr(TopicManager::GetInstance())
{

}
bool CppMQSpark::ClientSubTopic(const string& topic_name, const MQSparkShPtr& mqs_ptr)
{
    return topic_mgr.AddTopic(topic_name, mqs_ptr);
}
bool CppMQSpark::PublishMsg(const Message &msg)
{
    return topic_mgr.PublishMsg(msg);
}
bool CppMQSpark::ClientUnsub(const string &topic_name, const MQSparkShPtr &mqs_prt)
{
    return topic_mgr.RemoveTopic(topic_name, mqs_prt);
}
CppMQSpark::~CppMQSpark()
{
}
