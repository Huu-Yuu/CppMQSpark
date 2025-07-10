# CppMQSpark - 轻量级C++消息队列库

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
[![C++ Standard](https://img.shields.io/badge/C++-11/14-blue.svg)](https://en.cppreference.com/)

## MessageInterface 消息接口类

### 功能概述
- 发布/订阅模式的消息通信
- 支持多主题订阅
- 线程安全的回调处理机制
- 可通过继承扩展自定义消息处理逻辑

### 快速开始

#### 创建实例
```cpp
// 必须通过工厂方法创建实例
MQSparkShPtr mqs = MessageInterface::Create<MessageInterface>();

订阅与回调
// 订阅主题并设置回调
mqs->SubTopic("test");
mqs->RegMsgHandleCallback([](const Message& msg) {
    std::cout << "收到消息: " << msg.content << std::endl;
});

or
    static void MessageHandle(const Message &msg)
    {
        mutex tx;
        tx.lock();
        cout << "Consumer: ----- Get Msg : -----" << endl;
        cout << "topic: " << msg.topic_name << endl;
        cout << "msg: " << msg.content << endl;
        cout << "count = "<< count << endl;
        tx.unlock();
    }
mqs->RegMsgHandleCallback(&MessageHandle);

消息发布
Message msg("Hello", "test");  // 消息内容 + 主题
mqs->PublishMessage(msg);

异常处理
以下情况会抛出 std::invalid_argument：
try {
    mqs->SubTopic("");  // 空主题
} catch (const std::invalid_argument& e) {
    std::cerr << "错误: " << e.what() << std::endl;
}

异常场景	触发条件
无效主题格式	空字符串或包含 *?# 等字符
空回调函数	传入 nullptr
无效消息内容	消息体为空


资源清理
// 取消单个主题订阅
mqs->UnsubTopic("test");

// 取消所有订阅（析构时自动调用）
mqs->UnsubTopicAll();

注意事项
⚠️ ​重要限制​：

必须通过 Create() 静态方法创建实例
多线程环境下需保证回调函数的线程安全性
主题名称建议使用 [a-z0-9_/] 字符集

相关接口
基类定义：MQSparkAbstract
消息结构：Message


## 构建与安装

### 依赖项
- C++11 or C++14 或更新版本
- [CMake](https://cmake.org/) ≥ 3.10

### Linux/macOS
```bash
mkdir build && cd build
cmake ..
make install
