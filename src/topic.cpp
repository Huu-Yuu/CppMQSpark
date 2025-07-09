#include "topic.h"
Topic::Topic(const string &topicName)
{
    m_name = topicName;
}
string Topic::GetName() const
{
    return m_name;
}
void Topic::Publish(const Message &msg)
{
    for(const auto& clent : m_clents)
    {
        if(clent)
        {
            clent->HandleMessage(msg);
        }
    }
}
void Topic::AddMsgIter(const MQSparkShPtr& msg_iter)
{
    m_clents.emplace_back(msg_iter);
}

void Topic::DelMsgIter(const MQSparkShPtr& msg_iter)
{
    if(IsExistClent(msg_iter))
    {
        m_clents.remove(msg_iter);
    }
}

bool Topic::IsExistClent(const MQSparkShPtr& msg_iter)
{
    for(const auto& clent : m_clents)
    {
        if(clent == msg_iter)
            return true;
    }
    return false;
}
