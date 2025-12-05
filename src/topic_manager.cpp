#include "topic_manager.h"
#include "topic.h"
#include <iostream>
bool TopicManager::AddTopic(const string& topic_name, const MQSparkShPtr& msg_iter)
{
    lock_guard<mutex> lock(mtx);
    auto it = topics.find(topic_name);
    if(it != topics.end())
    {
        if(it->second->IsExistClent(msg_iter))
        {
            cerr << "主题已经存在，重复添加无效" << endl;
            return false;
        }
        it->second->AddMsgIter(msg_iter);
        return true;
    }
    cout << "添加主题成功: " << topic_name << endl;
    // 创建unique_ptr并插入到map中
    auto topic_ptr = make_unique<Topic>(topic_name);
    topic_ptr->AddMsgIter(msg_iter);
    topics.emplace(topic_name, std::move(topic_ptr));
    return true;
}

bool TopicManager::RemoveTopic(const string& topic_name, const MQSparkShPtr& msg_iter)
{
    lock_guard<mutex> lock(mtx);
    auto it = topics.find(topic_name);
    if(it != topics.end())
    {
        it->second->DelMsgIter(msg_iter);
        return true;
    }
    return false;
}
bool TopicManager::PublishMsg(const Message &msg)
{
    lock_guard<mutex> lock(mtx);
    auto it = topics.find(msg.topic_name);
    if(it != topics.end())
    {
        it->second->Publish(msg);
        return true;
    }
    return false;
}

void TopicManager::DelMsgPtr(const MQSparkShPtr &msg_iter)
{
    lock_guard<mutex> lock(mtx);
    for(auto& topic : topics)
    {
        topic.second->DelMsgIter(msg_iter);
    }
}
