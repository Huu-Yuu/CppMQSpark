# CppMQSpark - Lightweight C++ Message Queue Library

[![License](https://img.shields.io/badge/License-MIT-yellow.svg)](https://www.gnu.org/licenses/gpl-3.0)
[![C++ Standard](https://img.shields.io/badge/C++-11/14-blue.svg)](https://en.cppreference.com/)


## MessageInterface Message Interface Class

### Function Overview
- Publish/Subscribe pattern message communication
- Support for multi-topic subscription
- Thread-safe callback handling mechanism
- Extensible custom message processing logic through inheritance

## 🚀 Performance Highlights

✅ **Low Latency Message Delivery**
- Measured message delivery latency under 5 microseconds
- Efficient event distribution mechanism ensures real-time performance

✅ **Minimal Memory Footprint**
- Core implementation code less than 500 lines
- Zero external dependencies, lightweight design

✅ **Support for Efficient Lambda Callbacks**
- Seamless integration with modern C++ lambda expressions
- Simplified asynchronous message processing logic

✅ **Automatic Resource Cleanup Mechanism**
- Intelligent subscription resource management
- Prevents memory leaks and dangling callbacks

## 🎯 Use Cases

🏗️ **Cross-thread Communication**
- Safe and efficient inter-thread message passing
- Alternative to traditional lock mechanisms

🌐 **Microservice Message Bus**
- Lightweight inter-service communication solution
- Supports distributed system architecture

🎮 **Game Engine Event System**
- Real-time processing of game object events
- Low latency ensures smooth gaming experience

📊 **Real-time Data Processing Pipeline**
- Build low-latency data stream processing systems
- Suitable for financial trading and IoT scenarios

## 📥 Getting Started

```bash
git clone https://github.com/Huu-Yuu/CppMQSpark.git
```

### Quick Start

#### Creating Instances
```cpp
// Must create instances through factory method
// Creating multiple instances enables cross-thread communication
MQSparkShPtr mqs = MessageInterface::Create<MessageInterface>();
```

#### Subscription and Callbacks
```cpp
// Method 1: Setting callback using lambda expression
mqs->SubTopic("test");
mqs->RegMsgHandleCallback([&](const Message& msg) {
    std::cout << "Received message: " << msg.content << std::endl;
});

// Method 2: Setting callback using static function
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

#### Relatively Complete Pseudo Code Example
```cpp
#include "message_interface.h"
using namespace MQ;     // Declare namespace
// Message processing callback
static int count = 0;
static void MessageHandle(const Message &msg)
{
	mutex tx;	// For multi-threading and multiple producers generating messages, recommend using locks
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
	MQSparkShPtr c_ = MessageInterface::Create<MessageInterface>();	// Instantiate an object dedicated to receiving messages
	c_->SubTopic("topic_test");	// Subscribe to topic
	c_->RegMsgHandleCallback(&MessageHandle);
//	c_->UnsubTopicAll();	// Unsubscribe all before destruction
// If this is not called manually, the callback function will still be triggered after c_ object goes out of scope
// If called manually, the set callback function will no longer be triggered
}
// Producer thread function
void producerThread() {
	MQSparkShPtr p_ = MessageInterface::Create<MessageInterface>();	// Instantiate two objects to send messages
	MQSparkShPtr t_ = MessageInterface::Create<MessageInterface>();	
	for (int i = 0; i < 100; ++i)
	{
		Message msg(to_string(i), "topic_test");		// Message type is string, need to convert other message types to str before use
		p_->PublishMessage(msg);
		t_->PublishMessage(msg);
		std::cout << "Produced: " << i << std::endl;
	}
}

int main()
{
    cout << " ================ start ================ " << endl;
    std::thread producer(producerThread);		// Simulate multi-threading
    std::thread consumer(consumerThread);
//    consumerThread();							// Simulate single-threading
//    producerThread();

    producer.join();
    consumer.join();
    cout << " ================ end ================ " << endl;
    return 0;
}

```

#### Other Usage - Encapsulated Usage (Refer to Test Code)
```cpp
#include "message_interface.h"
using namespace MQ;
using namespace std;
// Message processing class
class MQHandle
{
public:
    MQHandle() : mqs(MessageInterface::Create<MessageInterface>())
    {
        mqs->RegMsgHandleCallback(&MessageHandle);	// Initialize and register message callback
    }

    ~MQHandle()
    {
        mqs->UnsubTopicAll();	// Unsubscribe all subscriptions during destruction
        cout << " ------- UnsubTopicAll -------" << endl;
    }

    void Send(const int& i, const string& topic_name)
    {
//        Message msg(to_string(i), topic_name);	// Assemble message
		Message msg;
        msg.content = to_string(i);
        msg.topic_name = topic_name;
        mqs->PublishMessage(msg);
    }

    void UnsubTopic(const string& topic_name)
    {
         mqs->UnsubTopic(topic_name);	// Unsubscribe topic
    }

    void Listen(const string& topic_name)
    {
        mqs->SubTopic(topic_name);	// Subscribe to topic

    }

    static void MessageHandle(const Message &msg)	// Message callback
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

#### Exception Handling
```cpp
try {
    mqs->SubTopic("");  // Empty topic
} catch (const std::invalid_argument& e) {
    std::cerr << "Error: " << e.what() << std::endl;
}
```

| Exception Scenario | Trigger Condition |
|---------------|----------------------------|
| Invalid topic format | Empty string or contains *?# characters |
| Empty callback function | Pass in nullptr |
| Invalid message content | Empty message body |

#### Resource Cleanup
```cpp
// Unsubscribe single topic
mqs->UnsubTopic("test");

// Unsubscribe all subscriptions (must be called manually before destruction, otherwise the set callback will still be triggered)
mqs->UnsubTopicAll();
```

### Important Notes
⚠️ **Important Limitations**:
1. Must create instances through `Create()` static method
2. Multi-threaded environment requires ensuring thread safety of callback functions
3. Topic names recommend using `[a-z0-9_/]` character set

### Related Interfaces
- Base class definition: `MQSparkAbstract`
- Message structure: `Message`

## Building and Installation

### Dependencies
- C++11 or C++14 or newer version
- [CMake](https://cmake.org/) ≥ 3.10 (Lower versions need self-testing)

### Using Build Scripts (Recommended)

#### Linux/macOS
```bash
chmod +x build.sh
./build.sh
```

#### Windows
In Command Prompt (cmd):
```cmd
build.bat
```

In PowerShell:
```powershell
.\build.bat
```

Build scripts automatically:
- Create build directory
- Configure project
- Compile project
- Provide options to run tests
- Provide library installation options on Linux/macOS

### Manual Building

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

### Build Script Description
- **Windows script (build.bat)**: Provides basic build functionality, with option to run tests after completion
  - Run directly in Command Prompt (cmd): `build.bat`
  - In PowerShell, need to use dot operator: `. .\build.bat`
  - PowerShell execution policy may prevent script execution. If this happens, temporarily modify execution policy: `Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope Process`
- **Linux/macOS script (build.sh)**: Checks CMake version requirements, provides build, test, and installation functionality
- Both scripts will prompt whether to run tests after build completion, can choose based on needs

## License Notice
This project uses **MIT License**, which means:
- ✅ **Commercial and private use allowed**: Can be freely used in commercial projects or proprietary software without requiring open source derivatives
- ✅ **Freedom to modify and distribute**: Allows arbitrary modification, copying, and distribution of code, including as part of proprietary software
- ✅ **Non-contagious restrictions**: Reference does not force license changes
- 📜 **Retain copyright notice**: **Only mandatory requirement**: Original copyright notice and license notice must be included in all copies
- ⚠️ **Disclaimer**: Users must clearly state "software provided as is", authors assume no responsibility

[](https://opensource.org/licenses/MIT)


## 📜 License

This project uses **[MIT License](https://opensource.org/licenses/MIT)**, one of the most widely used open source licenses:

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