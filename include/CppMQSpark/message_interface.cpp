#include "message_interface.h"
#include <stdexcept>
#include "cppmqspark.h"
#include <iostream>
namespace MQ
{

    struct MessageInterface::MQImplHide
    {
        SmartSpark spark_ptr;
    };
    MessageInterface::~MessageInterface() = default;
    MessageInterface::MessageInterface()
    {
#if USING_CPP14
        MQImpl_ = make_unique<MQImplHide>();
#elif USING_CPP11 == 201103L
        MQImpl_.reset(new MQImplHide);
#endif
        MQImpl_->spark_ptr = CppMQSpark::GetSharedInstance();
    }

    void MessageInterface::SubTopic(const string& topic_name)
    {
        if(topic_name.empty())
        {
            throw invalid_argument("主题名称不能为空");
        }
        cout << "添加主题: " << topic_name << endl;
        MQImpl_->spark_ptr->ClientSubTopic(topic_name, shared_from_this());
    }
    void MessageInterface::RegMsgHandleCallback(MessageHandle handle)
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
        MQImpl_->spark_ptr->ClientUnsub(topic_name, shared_from_this());
    }

    void MessageInterface::UnsubTopicAll()
    {
        MQImpl_->spark_ptr->DelClient(shared_from_this());
    }

    void MessageInterface::PublishMessage(const Message &msg)
    {
        if(msg.topic_name.empty() || msg.content.empty())
        {
            throw invalid_argument("主题名称或者消息内容为空");
        }
        MQImpl_->spark_ptr->PublishMsg(msg);
    }
    void MessageInterface::HandleMessage(const Message &msg)
    {
        if(m_handle_ != nullptr)
        {
            m_handle_(msg);
        }
    }

}// namespace MQ
