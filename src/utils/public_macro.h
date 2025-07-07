#ifndef C__MQSPARK_PUBLIC_MACRO_H
#define C__MQSPARK_PUBLIC_MACRO_H

// 基础单例宏（返回引用）
#define SINGLETON(ClassName)                          \
private:                                              \
    ClassName() = default;                            \
    ~ClassName() = default;                           \
    ClassName(const ClassName &) = delete;            \
    ClassName &operator=(const ClassName &) = delete; \
                                                      \
public:                                               \
    static ClassName &GetInstance()                   \
    {                                                 \
        static ClassName instance;                    \
        return instance;                              \
    }

// 增强版：同时支持引用和智能指针（需继承 std::enable_shared_from_this）
#define SMART_SINGLETON(ClassName)                                                  \
public:                                                                             \
    ClassName();                                                                    \
    ~ClassName();                                                                   \
                                                                                    \
private:                                                                            \
    ClassName(const ClassName &) = delete;                                          \
    ClassName &operator=(const ClassName &) = delete;                               \
                                                                                    \
public:                                                                             \
    static ClassName &GetInstance()                                                 \
    {                                                                               \
        static std::shared_ptr<ClassName> instance = std::make_shared<ClassName>(); \
        return *instance;                                                           \
    }                                                                               \
    static std::shared_ptr<ClassName> GetSharedInstance()                           \
    {                                                                               \
        static std::shared_ptr<ClassName> instance = std::make_shared<ClassName>(); \
        return instance;                                                            \
    }
#endif//C__MQSPARK_PUBLIC_MACRO_H
