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

#ifndef C__MQSPARK_MESSAGE_INTERFACE_H
#define C__MQSPARK_MESSAGE_INTERFACE_H
#include "mqspark_abstract.h"
#include <memory>
#include <list>
namespace MQ
{

    using MQSparkShPtr = shared_ptr<MQSparkAbstract>;
    /**
     * @brief 消息接口类
     * @note 可以直接使用该类发送消息和订阅主题，设置回调函数来处理订阅到的消息内容
     * 也可以继承该类或者 MQSparkAbstract 类作为基类来派生自己的消息类
     * * * ### 使用方式
     * @code{.cpp}
     * // 1. 创建实例（必须通过工厂方法）
     * MQSparkShPtr mqs = MessageInterface::Create<MessageInterface>();
     *
     * // 2. 订阅主题并设置回调
     * mqs->SubTopic("test");
     * mqs->RegMsgHandleCallback([](const Message& msg) {
     *     std::cout << "收到消息: " << msg.content << std::endl;
     * });
     *
     * // 3. 发布消息
     * Message msg("Hello", "test");
     * mqs->PublishMessage(msg);
     *
     * // 4. 资源释放（可选）
     * mqs->UnsubTopicAll();
     * @endcode
     * @throw std::invalid_argument 在以下情况会抛出该异常：
     * - 当订阅的主题格式不符合要求时（如空主题或包含非法字符）
     * - 当回调函数指针为空时
     * - 当消息内容无效时（如发送空消息）
     * @warning 必须通过Create()创建实例,多线程调用需自行保证回调函数线程安全
     * @see MQSparkAbstract 基类接口规范
     * **/
    class MessageInterface : public MQSparkAbstract
    {
    public:
        MessageInterface();
        ~MessageInterface() override;
        
        // 移动语义支持
        MessageInterface(MessageInterface&&) noexcept = default;
        MessageInterface& operator=(MessageInterface&&) noexcept = default;
        
        // 禁用拷贝
        MessageInterface(const MessageInterface&) = delete;
        MessageInterface& operator=(const MessageInterface&) = delete;
        
        /**
         * @brief 订阅指定主题
         * @param topic_name 主题名称
         * @note 重复订阅同一主题仅生效一次
         */
        void SubTopic(const string& topic_name) override;

        /**
         * @brief 注册全局消息处理回调
         * @param handle 回调函数原型：void(const Message&)
         * @code{.cpp}
         * // 回调示例：
         * mqs->RegMsgHandleCallback([](const Message& msg) {
         *     if (msg.topic == "alert") ProcessAlert(msg);
         * });
         * @endcode
         */
        void RegMsgHandleCallback(MessageHandle handle) override;

        /**
         * @brief 取消订阅指定主题
         * @param topic_name 要取消的主题（不存在时静默忽略）
         * @throw std::invalid_argument 空主题会抛出错误
         */
        void UnsubTopic(const string& topic_name) override;

        /**
         * @brief 取消所有订阅
         * @note 析构前手动调用,否则注册的回调函数会一直触发
         */
        void UnsubTopicAll() override;

        /**
         * @brief 发布消息到指定主题
         * @param msg 消息对象（必须包含有效topic）
         * @code{.cpp}
         * // 发布示例：
         * Message msg;
         * msg.topic = "system";
         * msg.content = "reboot";
         * mqs->PublishMessage(msg);
         * @endcode
         */
        void PublishMessage(const Message& msg) override;
        
        /**
         * @brief 发布消息到指定主题（移动版本）
         * @param msg 消息对象（必须包含有效topic）
         */
        void PublishMessage(Message&& msg);

    protected:
        /**
         * @brief 消息处理虚函数（供派生类覆盖）
         * @param msg 接收到的消息
         * @note 基类默认实现会将消息传递给注册的回调函数
         */
        void HandleMessage(const Message& msg) override;
        
        /**
         * @brief 消息处理虚函数（移动版本，供派生类覆盖）
         * @param msg 接收到的消息
         */
        virtual void HandleMessage(Message&& msg);
        
    private:
        struct MQImplHide;  ///< 前置声明 PIMPL模式隐藏实现细节
        unique_ptr<MQImplHide> MQImpl_;   ////< 核心实现指针
    };

}// namespace MQ

#endif//C__MQSPARK_MESSAGE_INTERFACE_H
