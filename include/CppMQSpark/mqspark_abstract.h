/*
* CppMQSpark - 轻量级C++消息队列库 | Lightweight C++ Message Queue Library
* 版权所有 (C) 2025 Huu-Yuu | Copyright (C) 2025 Huu-Yuu
*
* 特此授权任何获得本软件者自由使用、修改、合并、发布及分发本软件的权利，
* 惟须满足以下条件：
* 1. 在所有副本中保留上述版权声明及本许可声明
* 2. 本软件按“原样”提供，无任何担保，作者不承担任何责任
*
* Permission is hereby granted to any person obtaining a copy of this software
* to use, modify, merge, publish, distribute the software, subject to:
* 1. Retain above copyright notice and this permission notice
* 2. The software is provided "AS IS" without warranty, authors not liable
*/
#ifndef C__MQSPARK_MQSPARK_ABSTRACT_H
#define C__MQSPARK_MQSPARK_ABSTRACT_H

#include <functional>
#include <memory>
#include <string>
#include <utility>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
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
        CppMessage(const CppMessage&) = default;
        CppMessage(CppMessage&&) = default;
        CppMessage& operator=(const CppMessage&) = default;
        CppMessage& operator=(CppMessage&&) = default;
        
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
        
        MQSparkAbstract();
        virtual ~MQSparkAbstract();
        
        virtual void SubTopic(const string &topic_name) = 0;            ///< 订阅主题
        virtual void RegMsgHandleCallback(MessageHandle handle) = 0;    ///< 注册消息处理回调函数
        virtual void UnsubTopic(const string &topic_name) = 0;          ///< 取消订阅主题
        virtual void UnsubTopicAll() = 0;                               ///< 注销全部主题
        virtual void PublishMessage(const Message &msg) = 0;            ///< 发布消息
        
        // 处理消息的重载版本
        virtual void HandleMessage(const Message &msg);                 ///< 处理消息（拷贝版本）
        virtual void HandleMessage(Message&& msg);                      ///< 处理消息（移动版本）

    protected:
        MessageHandle m_handle_;
        
    private:
        void messageProcessLoop();
        
        queue<Message> m_msg_queue;
        mutex m_msg_mutex;
        condition_variable m_msg_cv;
        thread m_worker_thread;
        bool m_stop_flag;
        
        MQSparkAbstract(const MQSparkAbstract&) = delete;
        MQSparkAbstract& operator=(const MQSparkAbstract&) = delete;
        
        // 移动语义支持
        MQSparkAbstract(MQSparkAbstract&&) noexcept = default;
        MQSparkAbstract& operator=(MQSparkAbstract&&) noexcept = default;
    };

}

#endif//C__MQSPARK_MQSPARK_ABSTRACT_H
