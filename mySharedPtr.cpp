#include <iostream>

using namespace std;

template <typename T>
class myShreadPtr {
   public:
    myShreadPtr() : _ptr(nullptr), _count(nullptr) {}
    myShreadPtr(T* ptr) {
        _ptr = ptr;
        _count = new int(1);  //! 初始化引用计数
    }
    // 拷贝构造函数
    myShreadPtr(myShreadPtr& cpySptr) {
        ++(*cpySptr._count);
        _ptr = cpySptr._ptr;
        _count = cpySptr._count;
    }
    // 重载赋值运算符
    myShreadPtr& operator=(myShreadPtr& equSptr) {
        if (*this == equSptr) {
            return *this;
        }
        --(*_count);
        if (*(_count) == 0) {
            delete _ptr;
            delete _count;
        }
        ++(*equSptr._count);
        _ptr = equSptr._ptr;
        _count = equSptr._count;
        return *this;
    }

    ~myShreadPtr() {
        --(*_count);
        if (*_count == 0) {
            delete _ptr;
            delete _count;
        }
    }

    T& operator*() { return *_ptr; }

    T* operator->() { return _ptr; }

    int getCount() { return *_count; }

   private:
    // 引用计数
    int* _count;
    // 原指针
    T* _ptr;
};

int main() {
    std::cout << "Hello, World!" << std::endl;
    myShreadPtr<int> smartPtr1(new int(66));
    myShreadPtr<int> smartPtr2 = smartPtr1;
    myShreadPtr<int> smartPtr3(smartPtr1);

    cout << "smartPtr1.getCount=" << smartPtr1.getCount() << endl;
    cout << "smartPtr2.getCount=" << smartPtr2.getCount() << endl;
    cout << "smartPtr3.getCount=" << smartPtr3.getCount() << endl;

    return 0;
}
