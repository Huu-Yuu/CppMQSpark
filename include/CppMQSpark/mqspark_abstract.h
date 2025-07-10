/*
* CppMQSpark - 轻量级C++消息队列库 | Lightweight C++ Message Queue Library
* 版权所有 (C) 2023 Huu-Yuu | Copyright (C) 2023 Huu-Yuu
*
* 本程序是自由软件：您可以根据自由软件基金会发布的GNU通用公共许可证第3版或（可选）更高版本重新分发或修改它。
* This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 or (at your option) any later version.
*
* 本程序基于使用希望而分发，但**没有任何担保**；甚至没有适销性或特定用途适用性的暗示担保。详见GNU通用公共许可证。
* This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for details.
*/
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
