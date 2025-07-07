#ifndef C__MQSPARK_MQSPARK_ABSTRACT_H
#define C__MQSPARK_MQSPARK_ABSTRACT_H

#include <functional>
#include <memory>
#include <string>
using namespace std;

namespace MQ
{
    typedef struct CppMessage
    {
        string content;
        string topic_name;
    } Message;

    using MessageHandle = std::function<void(const Message &msg)>;
    class MQSparkAbstract;
    using MQSparkShPtr = shared_ptr<MQSparkAbstract>;

    class MQSparkAbstract : public std::enable_shared_from_this<MQSparkAbstract>
    {
    public:
        MQSparkAbstract() = default;
        virtual ~MQSparkAbstract() = default;
        virtual MQSparkShPtr CreateInstance() = 0;                      ///< 创建智能指针实例
        virtual void SubTopic(const string &topic_name) = 0;            ///< 订阅主题
        virtual void SetMessageHandleCallback(MessageHandle handle) = 0;///< 设置消息处理回调函数
        virtual void UnsubTopic(const string &topic_name) = 0;          ///< 取消订阅主题
        virtual void PublishMessage(const Message &msg) = 0;            ///< 发布消息
        virtual void HandleMessage(const Message &msg) = 0;             ///< 处理消息

    protected:
        MessageHandle m_handle_;
    };

}// namespace MQ

#endif//C__MQSPARK_MQSPARK_ABSTRACT_H
