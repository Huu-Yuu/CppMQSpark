#ifndef C__MQSPARK_MESSAGE_INTERFACE_H
#define C__MQSPARK_MESSAGE_INTERFACE_H
#include "mqspark_abstract.h"
#include <memory>
class CppMQSpark;
using SmartSpark = shared_ptr<CppMQSpark>;
namespace MQ
{

    /**
     * @brief 消息接口类
     * @note 可以直接使用该类发送消息和订阅主题，设置回调函数来处理订阅到的消息内容
     * 也可以继承该类或者 MQSparkAbstract 类作为基类来派生自己的消息类
     * @throw std::invalid_argument 在以下情况会抛出该异常：
     * - 当订阅的主题格式不符合要求时（如空主题或包含非法字符）
     * - 当回调函数指针为空时
     * - 当消息内容无效时（如发送空消息）
     * **/
    class MessageInterface : public MQSparkAbstract
    {
    public:
        MessageInterface();
        MQSparkShPtr CreateInstance() override;
        void SubTopic(const string& topic_name) override;
        void SetMessageHandleCallback(MessageHandle handle) override;
        void UnsubTopic(const string& topic_name) override;
        void PublishMessage(const Message& msg) override;
        void HandleMessage(const Message& msg) override;
    private:
        SmartSpark spark_ptr;
    };

}// namespace MQ

#endif//C__MQSPARK_MESSAGE_INTERFACE_H
