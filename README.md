# CppMQSpark - 轻量级C++消息队列库

[![License](https://img.shields.io/badge/License-MIT-yellow.svg)](https://www.gnu.org/licenses/gpl-3.0)
[![C++ Standard](https://img.shields.io/badge/C++-11/14-blue.svg)](https://en.cppreference.com/)

**🇺🇸 English Version Available: [README_EN.md](README_EN.md)** | **🇺🇸 可点击查看英文版文档**


## MessageInterface 消息接口类

### 功能概述
- 发布/订阅模式的消息通信
- 支持多主题订阅
- 线程安全的回调处理机制
- 可通过继承扩展自定义消息处理逻辑

## 🚀 性能亮点

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

## 🎯 使用场景

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

## 📥 获取方式

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
mqs->PublishMessage(msg2;
```

#### 相对完整的伪代码示例
```cpp
#include "message_interface.h"
using namespace MQ;     //声明命名空间
// 消息处理回调
static int count = 0;
static void MessageHandle(const Message &msg)
{
	mutex tx;	// 多线程和多个生产者产生消息，建议加锁
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
	MQSparkShPtr c_ = MessageInterface::Create<MessageInterface>();	// 实例化一个对象，专门接收消息
	c_->SubTopic("topic_test");	// 订阅主题
	c_->RegMsgHandleCallback(&MessageHandle);
//	c_->UnsubTopicAll();	// 解除所有订阅析构前使用，如果此处没有手动调用，会导致c_ 对象离开作用域后，回调函数还是会被消息触发，如果手动调用，则设置的回调函数不会再被触发
}
// 生产者线程函数
void producerThread() {
	MQSparkShPtr p_ = MessageInterface::Create<MessageInterface>();	// 实例化两个对象，发送消息
	MQSparkShPtr t_ = MessageInterface::Create<MessageInterface>();	
	for (int i = 0; i < 100; ++i)
	{
		Message msg(to_string(i), "topic_test");		// 消息类型是string，需要将其他消息转换成str后使用
		p_->PublishMessage(msg);
		t_->PublishMessage(msg);
		std::cout << "Produced: " << i << std::endl;
	}
}

int main()
{
    cout << " ================ start ================ " << endl;
    std::thread producer(producerThread);		// 模拟多线程
    std::thread consumer(consumerThread);
//    consumerThread();							// 模拟单线程
//    producerThread();

    producer.join();
    consumer.join();
    cout << " ================ end ================ " << endl;
    return 0;
}

```

#### 其他用法 - 封装后使用 （参照测试代码）
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
        mqs->RegMsgHandleCallback(&MessageHandle);	// 初始化注册消息回调
    }

    ~MQHandle()
    {
        mqs->UnsubTopicAll();	// 析构时注销所有订阅
        cout << " ------- UnsubTopicAll -------" << endl;
    }

    void Send(const int& i, const string& topic_name)
    {
//        Message msg(to_string(i), topic_name);	// 组装消息
		Message msg;
        msg.content = to_string(i);
        msg.topic_name = topic_name;
        mqs->PublishMessage(msg);
    }

    void UnsubTopic(const string& topic_name)
    {
         mqs->UnsubTopic(topic_name);	// 注销主题
    }

    void Listen(const string& topic_name)
    {
        mqs->SubTopic(topic_name);	// 订阅主题

    }

    static void MessageHandle(const Message &msg)	// 消息回调
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
}
```

#### 异常处理
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

#### 资源清理
```cpp
// 取消单个主题订阅
mqs->UnsubTopic("test");

// 取消所有订阅（需要在析构之前手动调用，否则设置的回调还会被触发）
mqs->UnsubTopicAll();
```

### 注意事项
⚠️ **重要限制**：
1. 必须通过 `Create()` 静态方法创建实例
2. 多线程环境下需保证回调函数的线程安全性
3. 主题名称建议使用 `[a-z0-9_/]` 字符集

### 相关接口
- 基类定义：`MQSparkAbstract`
- 消息结构：`Message`

## 构建与安装

### 依赖项
- C++11 或 C++14 或更新版本
- [CMake](https://cmake.org/) ≥ 3.10 （更低版本需要自行测试）

### 使用构建脚本（推荐）

#### Linux/macOS
```bash
chmod +x build.sh
./build.sh
```

#### Windows
在 Command Prompt (cmd) 中：
```cmd
build.bat
```

在 PowerShell 中：
```powershell
.\build.bat
```

构建脚本会自动：
- 创建构建目录
- 配置项目
- 编译项目
- 提供运行测试的选项
- 在Linux/macOS上提供安装库的选项

### 手动构建

#### Linux/macOS
```bash
mkdir build && cd build
cmake ..
make install
```

#### Windows
```powershell
cmake -B build -G "Visual Studio 16 2019"
cmake --build build --config Release
```

### 构建脚本说明
- **Windows脚本 (build.bat)**: 提供基础的构建功能，完成后可以选择运行测试
  - 在Command Prompt (cmd)中直接运行：`build.bat`
  - 在PowerShell中需要使用点运算符运行：`. .\build.bat`
  - PowerShell的执行策略可能会阻止脚本运行，如遇此情况，可临时修改执行策略：`Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope Process`
- **Linux/macOS脚本 (build.sh)**: 检查CMake版本要求，提供构建、测试和安装功能
- 两个脚本都会在构建完成后提示是否运行测试，可根据需要选择
## 许可证须知
本项目采用 **MIT 许可证**，这意味着：
- ✅ **允许商用和私有化使用**：可自由用于商业项目或闭源软件，无需开源衍生作品。
- ✅ **修改和分发自由**：允许任意修改、复制、分发代码，包括作为专有软件的一部分。
- ✅ **无传染性限制**：引用不会强制要求改变许可证。
- 📜 **保留版权声明**：**唯一强制要求**：所有副本中必须包含原始版权声明和许可声明。
- ⚠️ **免责条款**：使用者需明确"软件按原样提供"，作者不承担任何责任。

[](https://opensource.org/licenses/MIT)


## 📜 许可证

本项目采用 **[MIT 许可证](https://opensource.org/licenses/MIT)**，这是最广泛使用的开源许可证之一：

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