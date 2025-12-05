#include "mqspark_abstract.h"

namespace MQ
{
    MQSparkAbstract::MQSparkAbstract()
        : m_stop_flag(false)
        , m_worker_thread(&MQSparkAbstract::messageProcessLoop, this)
    {}
    
    MQSparkAbstract::~MQSparkAbstract()
    {
        // 停止工作线程
        {
            lock_guard<mutex> lock(m_msg_mutex);
            m_stop_flag = true;
        }
        m_msg_cv.notify_one();
        
        if(m_worker_thread.joinable())
        {
            m_worker_thread.join();
        }
    }
    
    void MQSparkAbstract::HandleMessage(const Message &msg)
    {
        // 将消息加入队列，异步处理
        {
            lock_guard<mutex> lock(m_msg_mutex);
            m_msg_queue.emplace(msg);
        }
        m_msg_cv.notify_one();
    }
    
    void MQSparkAbstract::HandleMessage(Message&& msg)
    {
        // 将消息移动加入队列，减少拷贝
        {
            lock_guard<mutex> lock(m_msg_mutex);
            m_msg_queue.emplace(std::move(msg));
        }
        m_msg_cv.notify_one();
    }
    
    void MQSparkAbstract::messageProcessLoop()
    {
        while(true)
        {
            Message msg;
            {
                unique_lock<mutex> lock(m_msg_mutex);
                m_msg_cv.wait(lock, [this](){ 
                    return m_stop_flag || !m_msg_queue.empty(); 
                });
                
                if(m_stop_flag && m_msg_queue.empty())
                {
                    break;
                }
                
                if(!m_msg_queue.empty())
                {
                    msg = std::move(m_msg_queue.front());
                    m_msg_queue.pop();
                }
            }
            
            // 处理消息
            if(m_handle_ != nullptr)
            {
                try
                {
                    m_handle_(msg);
                }
                catch(const std::exception& e)
                {
                    // 忽略消息处理回调中的异常，避免影响其他消息处理
                    (void)e;
                }
            }
        }
    }
}
