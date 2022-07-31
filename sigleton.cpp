#include <iostream>

using namespace std;

//! C++11单例模式，属于懒汉式
class Singleton {
   private:
    Singleton();

    ~Singleton();

    Singleton(const Singleton& s) {}

    Singleton& operator=(const Singleton& s) {}

   public:
    static Singleton& getInstance() {
        //! 局部静态变量在第一次使用时才初始化
        //! 并且C++11标准确保局部静态变量的线程安全问题
        static Singleton instance;
        return instance;
    }
};

//! C++11单例模式，饿汉式
class Singleton2 {
   private:
    static Singleton2 instance;

   private:
    Singleton2();

    ~Singleton2();

    Singleton2(const Singleton2&);

    Singleton2& operator=(const Singleton2&);

   public:
    static Singleton2& getInstance() { return instance; }
};

// initialize defaultly
Singleton2 Singleton2::instance;

int main() {
    Singleton::getInstance();
    Singleton::getInstance();

    Singleton2::getInstance();
    Singleton2::getInstance();

    return 0;
}
