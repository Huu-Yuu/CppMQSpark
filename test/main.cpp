#include "producer.h"
#include "consumer.h"
#include <thread>
#include <iostream>

int Consumer::count = 0;
int Producer::count = 0;
using namespace std;



// 生产者线程函数
void producerThread() {
    Producer p_;
    Producer d_;
    Producer c_;
    for (int i = 0; i < 100; ++i)
    {
        p_.Send(i , "test");
        d_.Send(i,"d_test");
        c_.Send(i, "c_test");
        std::cout << "Produced: " << i << std::endl;
//        std::this_thread::sleep_for(std::chrono::milliseconds(10)); // 控制生产速度
    }

}
// 消费者线程函数
void consumerThread() {
    Consumer c_;
    c_.Listen("test");
    c_.Listen("d_test");
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    c_.UnsubTopic("test");
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    c_.UnsubTopic("d_test");
}

int main()
{
    cout << " ================ start ================ " << endl;
    std::thread producer(producerThread);
    std::thread consumer(consumerThread);
//    consumerThread();
//    producerThread();

    producer.join();
    consumer.join();
    cout << " ================ end ================ " << endl;
    return 0;
}
