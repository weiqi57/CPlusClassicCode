#include <iostream>
#include <deque>
#include <vector>

using namespace std;

// 第二个模板参数默认使用deque，要使用vector也行
template<class T, class Container=deque<T> >
class myStack {
public:
    void push(const T &x) {
        con_.push_back(x);
    }

    void pop() {
        con_.pop_back();
    }

    T &top() {
        return con_.back();
    }

    bool empty() {
        return con_.empty();
    }

    int size() {
        return con_.size();
    }

private:
    Container con_;
};

template<class T, class Container=deque<T>>
class myQueue {
public:
    void push(const T &x) {
        con_.push_back(x);
    }

    void pop() {
        con_.pop_front();
    }

    T &front() {
        return con_.front();
    }

    T &back() {
        return con_.back();
    }

    bool empty() {
        return con_.empty();
    }

    int size() {
        return con_.size();
    }


private:
    Container con_;
};


int main() {
    myStack<int, vector<int>> s;
    s.push(1);
    s.push(2);
    s.push(3);
    cout << s.top() << endl;
    s.pop();
    cout << s.top() << endl;
    cout << s.size() << endl;


    return 0;
}
