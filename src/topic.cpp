#include "topic.h"
Topic::Topic(const string &topicName)
    : m_name(topicName)
{}

string Topic::GetName() const
{
    return m_name;
}

void Topic::Publish(const Message &msg)
{
    // 发布消息时复制客户端列表，避免持有锁期间被修改
    unordered_set<MQSparkShPtr> clients_copy;
    {
        lock_guard<mutex> lock(mtx);
        clients_copy = m_clents;
    }
    
    for(const auto& client : clients_copy)
    {
        if(client)
        {
            client->HandleMessage(msg);
        }
    }
}

void Topic::AddMsgIter(const MQSparkShPtr& msg_iter)
{
    lock_guard<mutex> lock(mtx);
    m_clents.emplace(msg_iter);
}

void Topic::DelMsgIter(const MQSparkShPtr& msg_iter)
{
    lock_guard<mutex> lock(mtx);
    m_clents.erase(msg_iter);
}

bool Topic::IsExistClent(const MQSparkShPtr& msg_iter)
{
    lock_guard<mutex> lock(mtx);
    return m_clents.find(msg_iter) != m_clents.end();
}
