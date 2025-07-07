#include "message_interface.h"
#include <stdexcept>
#include "cppmqspark.h"
namespace MQ
{
    MessageInterface::MessageInterface() : spark_ptr(CppMQSpark::GetSharedInstance())
    {
    }
    MQSparkShPtr MessageInterface::CreateInstance()
    {
        return std::make_shared<MessageInterface>();
    }
    void MessageInterface::SubTopic(const string& topic_name)
    {
        if(topic_name.empty())
        {
            throw invalid_argument("主题名称不能为空");
        }
        spark_ptr->ClientSubTopic(topic_name, shared_from_this());
    }
    void MessageInterface::SetMessageHandleCallback(MessageHandle handle)
    {
        if(handle == nullptr)
        {
            throw invalid_argument("消息处理回调函数不能为空");
        }
        if(m_handle_ != nullptr)
        {
            throw invalid_argument("消息处理回调函数只能设置一次");
        }
        m_handle_ = handle;
    }
    void MessageInterface::UnsubTopic(const string &topic_name)
    {
        if(topic_name.empty())
        {
            throw invalid_argument("主题名称不能为空");
        }
        spark_ptr->ClientUnsub(topic_name, shared_from_this());
    }
    void MessageInterface::PublishMessage(const Message &msg)
    {
        if(msg.topic_name.empty() || msg.content.empty())
        {
            throw invalid_argument("主题名称或者消息内容为空");
        }
        spark_ptr->PublishMsg(msg);
    }
    void MessageInterface::HandleMessage(const Message &msg)
    {
        if(m_handle_ != nullptr)
        {
            m_handle_(msg);
        }
    }
}// namespace MQ