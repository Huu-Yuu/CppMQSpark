#include "topic_manager.h"
#include "topic.h"

bool TopicManager::AddTopic(const string& topic_name, const MQSparkShPtr& msg_iter)
{
    for(auto& topic : topics)
    {
        if(topic.GetName() == topic_name)
        {
            if(topic.IsExistClent(msg_iter))
            {
                return false;
            }
            topic.AddMsgIter(msg_iter);
            return true;
        }
    }
    Topic topic(topic_name);
    topic.AddMsgIter(msg_iter);
    topics.emplace_back(topic);
    return true;
}

bool TopicManager::RemoveTopic(const string& topic_name, const MQSparkShPtr& msg_iter)
{
    for(auto& topic : topics)
    {
        if(topic.GetName() == topic_name)
        {
            topic.DelMsgIter(msg_iter);
            return true;
        }
    }
    return false;
}
bool TopicManager::PublishMsg(const Message &msg)
{
    for(auto& topic : topics)
    {
        if(topic.GetName() == msg.topic_name)
        {
            topic.Publish(msg);
            return true;
        }
    }
    return false;
}
