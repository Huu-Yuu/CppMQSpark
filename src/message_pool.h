#ifndef C__MQSPARK_MESSAGE_POOL_H
#define C__MQSPARK_MESSAGE_POOL_H

#include "mqspark_abstract.h"
#include <queue>
#include <mutex>
#include <memory>

namespace MQ
{
    class MessagePool
    {
    public:
        static MessagePool& GetInstance()
        {
            static MessagePool instance;
            return instance;
        }
        
        // 从池中获取消息对象
        std::unique_ptr<Message> Acquire()
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            
            if (m_pool.empty())
            {
                // 池为空，创建新对象
                return std::make_unique<Message>();
            }
            
            // 从池中获取对象
            auto msg = std::move(m_pool.front());
            m_pool.pop();
            return msg;
        }
        
        // 从池中获取消息对象并初始化
        std::unique_ptr<Message> Acquire(std::string content, std::string topic_name)
        {
            auto msg = Acquire();
            msg->content = std::move(content);
            msg->topic_name = std::move(topic_name);
            return msg;
        }
        
        // 将消息对象放回池中
        void Release(std::unique_ptr<Message> msg)
        {
            if (!msg)
            {
                return;
            }
            
            // 重置消息内容
            msg->content.clear();
            msg->topic_name.clear();
            
            std::lock_guard<std::mutex> lock(m_mutex);
            
            // 限制池的最大大小，避免内存泄漏
            if (m_pool.size() < m_max_size)
            {
                m_pool.push(std::move(msg));
            }
        }
        
        // 设置池的最大大小
        void SetMaxSize(size_t max_size)
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            m_max_size = max_size;
            
            // 如果当前池大小超过新的最大值，释放多余的对象
            while (m_pool.size() > m_max_size)
            {
                m_pool.pop();
            }
        }
        
        // 获取当前池大小
        size_t GetSize() const
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            return m_pool.size();
        }
        
    private:
        MessagePool() : m_max_size(1000) {}
        ~MessagePool() = default;
        
        MessagePool(const MessagePool&) = delete;
        MessagePool& operator=(const MessagePool&) = delete;
        
        std::queue<std::unique_ptr<Message>> m_pool;
        mutable std::mutex m_mutex;
        size_t m_max_size;
    };
}

#endif//C__MQSPARK_MESSAGE_POOL_H
