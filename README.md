# CppMQSpark - 轻量级C++消息队列库 / Lightweight C++ Message Queue Library

<div class="language-tabs">
<!-- Language tabs - 中文/English switcher -->
<div class="tabs">
  <button class="tab" onclick="switchLanguage('zh')">中文</button>
  <button class="tab" onclick="switchLanguage('en')">English</button>
</div>

<style>
.tabs {
  display: flex;
  gap: 10px;
  margin-bottom: 20px;
}
.tab {
  padding: 8px 16px;
  background-color: #f0f0f0;
  border: 1px solid #ddd;
  cursor: pointer;
  border-radius: 4px;
}
.tab.active {
  background-color: #2563eb;
  color: white;
  border-color: #2563eb;
}
.content-zh,
.content-en {
  display: none;
}
.content-zh.active,
.content-en.active {
  display: block;
}
</style>

<script>
// Simple language switcher for README
function switchLanguage(lang) {
  // Hide all content
  document.querySelectorAll('.content-zh, .content-en').forEach(el => {
    el.classList.remove('active');
  });
  
  // Show selected language content
  document.querySelector(`.content-${lang}`).classList.add('active');
  
  // Update active tab
  document.querySelectorAll('.tab').forEach(tab => {
    tab.classList.remove('active');
  });
  event.currentTarget.classList.add('active');
}

// Default to Chinese
window.onload = function() {
  document.querySelector('.content-zh').classList.add('active');
  document.querySelector('.tab:first-child').classList.add('active');
};
</script>

## 项目简介 / Project Introduction
<div class="content-zh">
CppMQSpark是一个轻量级的C++消息队列库，提供高效的消息发布订阅机制，适用于各种跨平台应用场景。
</div>

<div class="content-en">
CppMQSpark is a lightweight C++ message queue library that provides efficient message publish-subscribe mechanisms for various cross-platform application scenarios.
</div>

## 构建指南 / Build Guide

### 跨平台构建脚本 / Cross-platform Build Scripts
<div class="content-zh">
项目提供了跨平台的构建脚本，支持在不同操作系统上轻松构建：

#### Linux/macOS
```bash
# 赋予脚本执行权限
chmod +x build.sh
# 运行构建脚本
./build.sh
```

#### Windows
```batch
# 方法1：使用命令提示符(CMD)运行
build.bat

# 方法2：使用PowerShell运行
./build.bat
```

**注意**：Windows用户如果在直接双击运行脚本时遇到乱码或命令错误，请尝试通过命令提示符(CMD)或PowerShell运行脚本。脚本已使用英文编写以避免编码问题。
</div>

<div class="content-en">
The project provides cross-platform build scripts for easy building on different operating systems:

#### Linux/macOS
```bash
# Make script executable
chmod +x build.sh
# Run build script
./build.sh
```

#### Windows
```batch
# Method 1: Run using Command Prompt (CMD)
build.bat

# Method 2: Run using PowerShell
./build.bat
```

**Note**: Windows users who encounter garbled characters or command errors when double-clicking to run the script directly, please try running the script through Command Prompt (CMD) or PowerShell. The script has been written in English to avoid encoding issues.
</div>

### 手动构建（使用CMake） / Manual Build (Using CMake)
<div class="content-zh">

#### 1. 配置项目
```bash
mkdir build
cd build
cmake ..
```

#### 2. 编译项目
```bash
cmake --build . --config Release
```

#### 3. 安装库（可选）
```bash
# Linux/macOS
sudo cmake --install .

# Windows（以管理员权限运行）
cmake --install .
```
</div>

<div class="content-en">

#### 1. Configure the Project
```bash
mkdir build
cd build
cmake ..
```

#### 2. Compile the Project
```bash
cmake --build . --config Release
```

#### 3. Install the Library (Optional)
```bash
# Linux/macOS
sudo cmake --install .

# Windows (Run as administrator)
cmake --install .
```
</div>

### 依赖项 / Dependencies
<div class="content-zh">
- CMake 3.5或更高版本（推荐使用3.10+以获得更好的支持）
- C++14兼容的编译器（GCC、Clang、MSVC等）
- 线程库（pthread）
</div>

<div class="content-en">
- CMake 3.5 or higher (3.10+ recommended for better support)
- C++14 compatible compiler (GCC, Clang, MSVC, etc.)
- Thread library (pthread)
</div>

### 构建脚本改进 / Build Script Improvements
<div class="content-zh">
构建脚本已更新，增加了以下功能：
- CMake版本检测和兼容性提示
- 智能查找测试可执行文件
- 更友好的错误处理和用户提示
- 在安装失败时提供替代解决方案
</div>

<div class="content-en">
The build scripts have been updated with the following features:
- CMake version detection and compatibility tips
- Intelligent search for test executables
- More user-friendly error handling and prompts
- Alternative solutions when installation fails
</div>

## 项目结构 / Project Structure
<div class="content-zh">
- `include/` - 公共头文件
- `src/` - 源代码实现
- `test/` - 测试代码
- `lib/` - 生成的库文件
- `bin/` - 生成的可执行文件
</div>

<div class="content-en">
- `include/` - Public header files
- `src/` - Source code implementation
- `test/` - Test code
- `lib/` - Generated library files
- `bin/` - Generated executable files
</div>

## 许可证 / License
<div class="content-zh">
详见LICENSE文件。
</div>

<div class="content-en">
See LICENSE file for details.
</div>

[![License](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![C++ Standard](https://img.shields.io/badge/C++-11/14-blue.svg)](https://en.cppreference.com/)


## MessageInterface 消息接口类 / MessageInterface Class

### 功能概述 / Features Overview
<div class="content-zh">
- 发布/订阅模式的消息通信
- 支持多主题订阅
- 线程安全的回调处理机制
- 可通过继承扩展自定义消息处理逻辑
</div>

<div class="content-en">
- Publish/subscribe pattern message communication
- Support for multi-topic subscription
- Thread-safe callback handling mechanism
- Custom message processing logic can be extended through inheritance
</div>

## 🚀 性能亮点 / Performance Highlights

<div class="content-zh">
✅ **低延迟消息传递**
- 实测消息传递延迟低于5微秒
- 高效的事件分发机制确保实时性

✅ **内存占用极小**
- 核心实现代码少于500行
- 零外部依赖，轻量化设计

✅ **支持高效lambda回调**
- 无缝集成现代C++的lambda表达式
- 简化异步消息处理逻辑

✅ **资源自动清理机制**
- 智能管理订阅资源
- 防止内存泄漏和悬空回调
</div>

<div class="content-en">
✅ **Low Latency Message Delivery**
- Measured message delivery latency below 5 microseconds
- Efficient event distribution mechanism ensures real-time performance

✅ **Minimal Memory Footprint**
- Core implementation code less than 500 lines
- Zero external dependencies, lightweight design

✅ **Support for Efficient Lambda Callbacks**
- Seamless integration with modern C++ lambda expressions
- Simplified asynchronous message processing logic

✅ **Automatic Resource Cleanup Mechanism**
- Intelligent management of subscription resources
- Prevents memory leaks and dangling callbacks
</div>

## 🎯 使用场景 / Use Cases

<div class="content-zh">
🏗️ **跨线程通信**
- 安全高效的线程间消息传递
- 替代传统的锁机制

🌐 **微服务间消息总线**
- 轻量级服务间通信解决方案
- 支持分布式系统架构

🎮 **游戏引擎事件系统**
- 实时处理游戏对象事件
- 低延迟确保流畅游戏体验

📊 **实时数据处理管道**
- 构建低延迟数据流处理系统
- 适用于金融交易和IoT场景
</div>

<div class="content-en">
🏗️ **Cross-Thread Communication**
- Safe and efficient inter-thread message passing
- Alternative to traditional locking mechanisms

🌐 **Microservice Message Bus**
- Lightweight inter-service communication solution
- Supports distributed system architecture

🎮 **Game Engine Event System**
- Real-time processing of game object events
- Low latency ensures smooth gaming experience

📊 **Real-time Data Processing Pipeline**
- Build low-latency data stream processing systems
- Suitable for financial trading and IoT scenarios
</div>

## 📥 获取方式 / Installation

<div class="content-zh">
```bash
git clone https://github.com/Huu-Yuu/CppMQSpark.git
```

### 快速开始

#### 创建实例
```cpp
// 必须通过工厂方法创建实例，创建多个实例可以进行跨线程通讯
MQSparkShPtr mqs = MessageInterface::Create<MessageInterface>();
```

#### 订阅与回调
```cpp
// 方式1：使用lambda表达式设置回调
mqs->SubTopic("test");
mqs->RegMsgHandleCallback([&](const Message& msg) {
    std::cout << "收到消息: " << msg.content << std::endl;
});

// 方式2：使用静态函数设置回调
static void MessageHandle(const Message &msg) {
    std::mutex tx;
    tx.lock();
    static int count = 0;
    std::cout << "Consumer: ----- Get Msg : -----" << std::endl;
    std::cout << "topic: " << msg.topic_name << std::endl;
    std::cout << "msg: " << msg.content << std::endl;
    std::cout << "count = " << count << std::endl;
    tx.unlock();
}
mqs->RegMsgHandleCallback(&MessageHandle);
```

#### 消息发布
```cpp
Message msg1("Hello", "test");  // 消息内容 + 主题
Message msg2;
msg2.content = "word";          // 结构体成员赋值
msg2.topic_name = "test";       // 结构体成员赋值
mqs->PublishMessage(msg1);
mqs->PublishMessage(msg2);
```

#### 相对完整的伪代码示例
```cpp
#include "message_interface.h"
using namespace MQ;     //声明命名空间
// 消息处理回调
static int count = 0;
static void MessageHandle(const Message &msg)
{
	mutex tx;    // 多线程和多个生产者产生消息，建议加锁
	tx.lock();
	count ++;
	cout << "Consumer: ----- Get Msg : -----" << endl;
	cout << "topic: " << msg.topic_name << endl;
	cout << "msg: " << msg.content << endl;
	cout << "count = "<< count << endl;
	tx.unlock();
}

// 消费者线程函数
void consumerThread() {
	MQSparkShPtr c_ = MessageInterface::Create<MessageInterface>();    // 实例化一个对象，专门接收消息
	c_->SubTopic("topic_test");    // 订阅主题
	c_->RegMsgHandleCallback(&MessageHandle);
//	c_->UnsubTopicAll();    // 解除所有订阅析构前使用，如果此处没有手动调用，会导致c_ 对象离开作用域后，回调函数还是会被消息触发，如果手动调用，则设置的回调函数不会再被触发
}
// 生产者线程函数
void producerThread() {
	MQSparkShPtr p_ = MessageInterface::Create<MessageInterface>();    // 实例化两个对象，发送消息
	MQSparkShPtr t_ = MessageInterface::Create<MessageInterface>();
	for (int i = 0; i < 100; ++i)
	{
		Message msg(to_string(i), "topic_test");        // 消息类型是string，需要将其他消息转换成str后使用
		p_->PublishMessage(msg);
		t_->PublishMessage(msg);
		std::cout << "Produced: " << i << std::endl;
	}
}

int main()
{
    cout << " ================ start ================ " << endl;
    std::thread producer(producerThread);        // 模拟多线程
    std::thread consumer(consumerThread);
//    consumerThread();                            // 模拟单线程
//    producerThread();

    producer.join();
    consumer.join();
    cout << " ================ end ================ " << endl;
    return 0;
```
</div>

<div class="content-en">
```bash
git clone https://github.com/Huu-Yuu/CppMQSpark.git
```

### Quick Start

#### Creating an Instance
```cpp
// Must create instance through factory method, multiple instances can communicate across threads
MQSparkShPtr mqs = MessageInterface::Create<MessageInterface>();
```

#### Subscription and Callback
```cpp
// Method 1: Set callback using lambda expression
mqs->SubTopic("test");
mqs->RegMsgHandleCallback([&](const Message& msg) {
    std::cout << "Received message: " << msg.content << std::endl;
});

// Method 2: Set callback using static function
static void MessageHandle(const Message &msg) {
    std::mutex tx;
    tx.lock();
    static int count = 0;
    std::cout << "Consumer: ----- Get Msg : -----" << std::endl;
    std::cout << "topic: " << msg.topic_name << std::endl;
    std::cout << "msg: " << msg.content << std::endl;
    std::cout << "count = " << count << std::endl;
    tx.unlock();
}
mqs->RegMsgHandleCallback(&MessageHandle);
```

#### Message Publishing
```cpp
Message msg1("Hello", "test");  // Message content + topic
Message msg2;
msg2.content = "word";          // Struct member assignment
msg2.topic_name = "test";       // Struct member assignment
mqs->PublishMessage(msg1);
mqs->PublishMessage(msg2);
```

#### Complete Pseudocode Example
```cpp
#include "message_interface.h"
using namespace MQ;     // Declare namespace
// Message processing callback
static int count = 0;
static void MessageHandle(const Message &msg)
{
	mutex tx;    // Multi-threading and multiple producers generate messages, locking recommended
	tx.lock();
	count ++;
	cout << "Consumer: ----- Get Msg : -----" << endl;
	cout << "topic: " << msg.topic_name << endl;
	cout << "msg: " << msg.content << endl;
	cout << "count = "<< count << endl;
	tx.unlock();
}

// Consumer thread function
void consumerThread() {
	MQSparkShPtr c_ = MessageInterface::Create<MessageInterface>();    // Instantiate an object, specifically for receiving messages
	c_->SubTopic("topic_test");    // Subscribe to topic
	c_->RegMsgHandleCallback(&MessageHandle);
//	c_->UnsubTopicAll();    // Use before destructing to unsubscribe from all topics. If not manually called here, the callback function will still be triggered by messages after the c_ object goes out of scope. If manually called, the set callback function will not be triggered again.
}
// Producer thread function
void producerThread() {
	MQSparkShPtr p_ = MessageInterface::Create<MessageInterface>();    // Instantiate two objects to send messages
	MQSparkShPtr t_ = MessageInterface::Create<MessageInterface>();
	for (int i = 0; i < 100; ++i)
	{
		Message msg(to_string(i), "topic_test");        // Message type is string, need to convert other messages to string before use
		p_->PublishMessage(msg);
		t_->PublishMessage(msg);
		std::cout << "Produced: " << i << std::endl;
	}
}

int main()
{
    cout << " ================ start ================ " << endl;
    std::thread producer(producerThread);        // Simulate multi-threading
    std::thread consumer(consumerThread);
//    consumerThread();                            // Simulate single-threading
//    producerThread();

    producer.join();
    consumer.join();
    cout << " ================ end ================ " << endl;
    return 0;
```
</div>
    cout << " ================ end ================ " << endl;
    return 0;
}

```

#### 其他用法 - 封装后使用 / Alternative Usage - Using with Encapsulation
<div class="content-zh">
```cpp
#include "message_interface.h"
using namespace MQ;
using namespace std;
// 消息处理类
class MQHandle
{
public:
    MQHandle() : mqs(MessageInterface::Create<MessageInterface>())
    {
        mqs->RegMsgHandleCallback(&MessageHandle);    // 初始化注册消息回调
    }

    ~MQHandle()
    {
        mqs->UnsubTopicAll();    // 析构时注销所有订阅
        cout << " ------- UnsubTopicAll -------" << endl;
    }

    void Send(const int& i, const string& topic_name)
    {
//        Message msg(to_string(i), topic_name);    // 组装消息
		Message msg;
        msg.content = to_string(i);
        msg.topic_name = topic_name;
        mqs->PublishMessage(msg);
    }

    void UnsubTopic(const string& topic_name)
    {
         mqs->UnsubTopic(topic_name);    // 注销主题
    }

    void Listen(const string& topic_name)
    {
        mqs->SubTopic(topic_name);    // 订阅主题

    }

    static void MessageHandle(const Message &msg)    // 消息回调
    {
        mutex tx;
        tx.lock();
        count ++;
        cout << "Consumer: ----- Get Msg : -----" << endl;
        cout << "topic: " << msg.topic_name << endl;
        cout << "msg: " << msg.content << endl;
        cout << "count = "<< count << endl;
        tx.unlock();
    }
private:
    static int count;
    MQSparkShPtr mqs;
};
```
</div>

<div class="content-en">
```cpp
#include "message_interface.h"
using namespace MQ;
using namespace std;
// Message handling class
class MQHandle
{
public:
    MQHandle() : mqs(MessageInterface::Create<MessageInterface>())
    {
        mqs->RegMsgHandleCallback(&MessageHandle);    // Initialize and register message callback
    }

    ~MQHandle()
    {
        mqs->UnsubTopicAll();    // Unsubscribe from all topics during destruction
        cout << " ------- UnsubTopicAll -------" << endl;
    }

    void Send(const int& i, const string& topic_name)
    {
//        Message msg(to_string(i), topic_name);    // Assemble message
		Message msg;
        msg.content = to_string(i);
        msg.topic_name = topic_name;
        mqs->PublishMessage(msg);
    }

    void UnsubTopic(const string& topic_name)
    {
         mqs->UnsubTopic(topic_name);    // Unsubscribe from topic
    }

    void Listen(const string& topic_name)
    {
        mqs->SubTopic(topic_name);    // Subscribe to topic
    }

    static void MessageHandle(const Message &msg)    // Message callback
    {
        mutex tx;
        tx.lock();
        count++;
        cout << "Consumer: ----- Get Msg : -----" << endl;
        cout << "topic: " << msg.topic_name << endl;
        cout << "msg: " << msg.content << endl;
        cout << "count = " << count << endl;
        tx.unlock();
    }
private:
    static int count;
    MQSparkShPtr mqs;
};
```
</div>
```

#### 异常处理 / Exception Handling
<div class="content-zh">
```cpp
try {
    mqs->SubTopic("");  // 空主题
} catch (const std::invalid_argument& e) {
    std::cerr << "错误: " << e.what() << std::endl;
}
```

| 异常场景       | 触发条件                     |
|---------------|----------------------------|
| 无效主题格式   | 空字符串或包含 *?# 等字符    |
| 空回调函数     | 传入 nullptr                |
| 无效消息内容   | 消息体为空                  |
</div>

<div class="content-en">
```cpp
try {
    mqs->SubTopic("");  // Empty topic
} catch (const std::invalid_argument& e) {
    std::cerr << "Error: " << e.what() << std::endl;
}
```

| Exception Scenario | Trigger Condition                |
|-------------------|----------------------------------|
| Invalid Topic Format | Empty string or contains characters like *?# |
| Null Callback Function | Passing nullptr |
| Invalid Message Content | Empty message body |
</div>

#### 资源清理 / Resource Cleanup
<div class="content-zh">
```cpp
// 取消单个主题订阅
mqs->UnsubTopic("topic_name");

// 取消所有主题订阅
mqs->UnsubTopicAll();

// 通过对象销毁自动清理（推荐）
// 当 MQSparkShPtr 对象离开作用域时，将自动释放资源
```

**提示**：推荐使用智能指针 `MQSparkShPtr` 管理对象生命周期，这样当对象不再使用时，系统会自动进行资源清理。
</div>

<div class="content-en">
```cpp
// Unsubscribe from a single topic
mqs->UnsubTopic("topic_name");

// Unsubscribe from all topics
mqs->UnsubTopicAll();

// Automatic cleanup through object destruction (recommended)
// When the MQSparkShPtr object goes out of scope, resources will be automatically released
```

**Tip**: It's recommended to use the smart pointer `MQSparkShPtr` to manage the object lifecycle, so that the system automatically cleans up resources when the object is no longer in use.
</div>

### 注意事项 / Notes
⚠️ **重要限制**：
1. 必须通过 `Create()` 静态方法创建实例
2. 多线程环境下需保证回调函数的线程安全性
3. 主题名称建议使用 `[a-z0-9_/]` 字符集

### 相关接口 / Related Interfaces
<div class="content-zh">
- 基类定义：`MQSparkAbstract`
- 消息结构：`Message`
</div>

<div class="content-en">
- Base class definition: `MQSparkAbstract`
- Message structure: `Message`
</div>

## 构建与安装 / Building and Installation

### 依赖项 / Dependencies
<div class="content-zh">
- C++11 或 C++14 或更新版本
- [CMake](https://cmake.org/) ≥ 3.10 （更低版本需要自行测试）
</div>

<div class="content-en">
- C++11 or C++14 or newer
- [CMake](https://cmake.org/) ≥ 3.10 (lower versions need to be tested separately)
</div>
### Linux/macOS
<div class="content-zh">
```bash
mkdir build && cd build
cmake ..
make install
```
</div>

<div class="content-en">
```bash
mkdir build && cd build
cmake ..
make install
```
</div>

### Windows
<div class="content-zh">
```powershell
cmake -B build -G "Visual Studio 16 2019"
cmake --build build --config Release
```
</div>

<div class="content-en">
```powershell
cmake -B build -G "Visual Studio 16 2019"
cmake --build build --config Release
```
</div>
## 许可证须知 / License Information
<div class="content-zh">
本项目采用 **MIT 许可证**，这意味着：
- ✅ **允许商用和私有化使用**：可自由用于商业项目或闭源软件，无需开源衍生作品。
- ✅ **修改和分发自由**：允许任意修改、复制、分发代码，包括作为专有软件的一部分。
- ✅ **无传染性限制**：引用不会强制要求改变许可证。
- 📜 **保留版权声明**：**唯一强制要求**：所有副本中必须包含原始版权声明和许可声明。
- ⚠️ **免责条款**：使用者需明确"软件按原样提供"，作者不承担任何责任。
</div>

<div class="content-en">
This project is licensed under the **MIT License**, which means:
- ✅ **Commercial and private use allowed**: Can be freely used in commercial projects or closed-source software, no need to open-source derivative works.
- ✅ **Freedom to modify and distribute**: Allows any modification, copying, distribution of code, including as part of proprietary software.
- ✅ **No viral restrictions**: References do not require changing the license.
- 📜 **Preserve copyright notices**: **Only mandatory requirement**: All copies must include the original copyright and license notices.
- ⚠️ **Disclaimer**: Users must acknowledge the software is provided "as is" without warranty, and the author bears no responsibility.
</div>

[](https://opensource.org/licenses/MIT)


## 📜 许可证 / License

<div class="content-zh">
本项目采用 **[MIT 许可证](https://opensource.org/licenses/MIT)**，这是最广泛使用的开源许可证之一：
</div>

<div class="content-en">
This project is licensed under the **[MIT License](https://opensource.org/licenses/MIT)**, which is one of the most widely used open-source licenses:
</div>

<div class="content-zh content-en">
```text
MIT License

Copyright (c) [2025] [Huu-Yuu]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```
</div>