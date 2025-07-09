#ifndef C__MQSPARK_MQSPARK_ABSTRACT_H
#define C__MQSPARK_MQSPARK_ABSTRACT_H

#include <functional>
#include <memory>
#include <string>
#include <utility>
using namespace std;

namespace MQ
{
    typedef struct CppMessage
    {
        CppMessage()= default;
        CppMessage(string cont, string topic)
        {
            content = std::move(cont);
            topic_name = std::move(topic);
        }
        string content;
        string topic_name;
    } Message;

    using MessageHandle = std::function<void(const Message &msg)>;

    class MQSparkAbstract : public std::enable_shared_from_this<MQSparkAbstract>
    {
    public:
        template<typename T, typename... Args>
        static std::shared_ptr<T> Create(Args&&... args)
        {
            static_assert(std::is_base_of<MQSparkAbstract, T>::value, "T 必须继承自 MQSparkAbstract");
            auto ptr = std::make_shared<T>(std::forward<Args>(args)...);
            return ptr;
        }
        MQSparkAbstract() = default;
        virtual ~MQSparkAbstract() = default;
        virtual void SubTopic(const string &topic_name) = 0;            ///< 订阅主题
        virtual void RegMsgHandleCallback(MessageHandle handle) = 0;    ///< 注册消息处理回调函数
        virtual void UnsubTopic(const string &topic_name) = 0;          ///< 取消订阅主题
        virtual void UnsubTopicAll() = 0;                               ///< 注销全部主题
        virtual void PublishMessage(const Message &msg) = 0;            ///< 发布消息
        virtual void HandleMessage(const Message &msg)                  ///< 处理消息
        {
            if(m_handle_ != nullptr)
            {
                m_handle_(msg);
            }
        }

    protected:
        MessageHandle m_handle_;
    private:

//        MQSparkAbstract() = default;
        MQSparkAbstract(const MQSparkAbstract&) = delete;
        MQSparkAbstract& operator=(const MQSparkAbstract&) = delete;
    };

}// namespace MQ

#endif//C__MQSPARK_MQSPARK_ABSTRACT_H
