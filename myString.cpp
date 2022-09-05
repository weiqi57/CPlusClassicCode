#include <iostream>
#include <cstring>
#include <string>

using namespace std;    // for std::ostream

class MyString {
private:
    int len_;
    char *data_;

public:
    MyString() {
        data_ = nullptr;
        len_ = 0;
    }

    MyString(char *c) {
        if (c == nullptr) {
            data_ = new char[1];
            data_[0] = '\0';
            len_ = 0;
        } else {
            len_ = strlen(c);
            data_ = new char[len_ + 1];
            /*strcpy会连带字符串结束符一起拷贝*/
            strcpy(data_, c);
        }
    }

    // 拷贝构造函数
    MyString(const MyString &other_mystr) {
        len_ = other_mystr.len_;
        data_ = new char[len_ + 1];
        strcpy(data_, other_mystr.data_);
    }

    // 重载复制运算符
    MyString &operator=(const MyString &other_mystr) {
        if (this == &other_mystr) {
            return *this;
        }

        len_ = other_mystr.len_;
        data_ = new char[len_ + 1];
        strcpy(data_, other_mystr.data_);

        return *this;
    }

    // 移动构造函数
    MyString(MyString &&other_mystr) {
        len_ = other_mystr.len_;
        data_ = other_mystr.data_;
        other_mystr.data_ = nullptr;
        other_mystr.len_ = 0;
    }

    // 移动赋值函数
    MyString &operator=(MyString &&other_mystr) {
        if (this == &other_mystr) {
            return *this;
        }
        len_ = other_mystr.len_;
        data_ = other_mystr.data_;
        other_mystr.data_ = nullptr;
        other_mystr.len_ = 0;

        return *this;
    }

    // 析构函数
    ~MyString() {
        if (data_ != nullptr) {
            delete[] data_;
        }
    }

    // 重载<<运算符必须要将该函数定义为友元函数
    // 友元函数可以在类内定义，一般情况下是在类内声明，在类外定义，在类外定义时不用加friend关键字
    friend ostream &operator<<(ostream &os_cout, const MyString &mystr) {
        os_cout << mystr.data_;
        return os_cout;
    }

    friend istream &operator>>(istream &is_cin, MyString &str) {
        char buff[256];
        is_cin >> buff;
        // 调用构造函数2
        str = MyString(buff);
        return is_cin;
    }

    char operator[](int index) {
        if (index > len_ || index < 0) {
            return ' ';
        }
        return *(data_ + index);  // data_[index]
    }

    // abcde -> bcdef   使用时方法：++mystr
    void operator++() {
        for (int i = 0; i < len_; i++) {
            data_[i]++;
        }
    }

    char *getCstring() {
        return data_;
    }
};


int main() {

    MyString str = "abcde";
    cout << str << endl;
    ++str;
    cout << str << endl;
    cout << str[1] << endl;


//    MyString str2;
//    cin >> str2;
//    cout << str2 << endl;
    return 0;
}
