#include <iostream>

template <typename T>
class UniquePtr
{
private:
    T *ptr; // 原始指针

public:
    // 构造函数
    explicit UniquePtr(T *p = nullptr) : ptr(p) {}

    // 禁用拷贝构造函数和拷贝赋值运算符
    UniquePtr(const UniquePtr &) = delete;
    UniquePtr &operator=(const UniquePtr &) = delete;

    // 移动构造函数
    UniquePtr(UniquePtr &&other) noexcept : ptr(other.ptr)
    {
        other.ptr = nullptr;
    }

    // 移动赋值运算符
    UniquePtr &operator=(UniquePtr &&other) noexcept
    {
        if (this != &other)
        {
            delete ptr;      // 释放当前资源
            ptr = other.ptr; // 接管其他指针
            other.ptr = nullptr;
        }
        return *this;
    }

    // 解引用运算符
    T &operator*() const
    {
        return *ptr;
    }

    // 成员访问运算符
    T *operator->() const
    {
        return ptr;
    }

    // 获取原始指针
    T *get() const
    {
        return ptr;
    }

    // 释放所有权并返回原始指针
    T *release()
    {
        T *temp = ptr;
        ptr = nullptr;
        return temp;
    }

    // 重新设置指针，删除旧的指针
    void reset(T *p = nullptr)
    {
        delete ptr;
        ptr = p;
    }

    // 析构函数
    ~UniquePtr()
    {
        delete ptr;
    }
};
