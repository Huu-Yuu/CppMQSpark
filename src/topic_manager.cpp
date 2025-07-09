#include "topic_manager.h"
#include "topic.h"
#include <iostream>
bool TopicManager::AddTopic(const string& topic_name, const MQSparkShPtr& msg_iter)
{
    for(auto& topic : topics)
    {
        if(topic.GetName() == topic_name)
        {
            if(topic.IsExistClent(msg_iter))
            {
                cerr << "主题已经存在，重复添加无效" << endl;
                return false;
            }
            topic.AddMsgIter(msg_iter);
            return true;
        }
    }
    cout << "添加主题成功: " << topic_name << endl;
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

void TopicManager::DelMsgPtr(const MQSparkShPtr &msg_iter)
{
    for(auto& topic : topics)
    {
        topic.DelMsgIter(msg_iter);
    }
}
