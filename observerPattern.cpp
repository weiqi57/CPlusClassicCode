#include <iostream>
#include <list>

using namespace std;

/*抽象观察者*/
class Observer {
public:
    virtual void Update(int) = 0;
};

/*抽象（被）观察目标*/
class Subject {
public:
    virtual void Attach(Observer *) = 0;  //附加观察者
    virtual void Detach(Observer *) = 0; //移除观察者
    virtual void Notify() = 0; //通知观察者
};

/*具体观察者1*/
class ConcreteObserver1 : public Observer {
public:
    ConcreteObserver1(Subject *pSubject) : m_pSubject(pSubject) {}

    void Update(int value) {
        cout << "ConcreteObserver1 get the update. New State:" << value << endl;
    }

private:
    Subject *m_pSubject;
};

/*具体观察者2*/
class ConcreteObserver2 : public Observer {
public:
    ConcreteObserver2(Subject *pSubject) : m_pSubject(pSubject) {}

    void Update(int value) {
        cout << "ConcreteObserver2 get the update. New State:" << value << endl;
    }

private:
    Subject *m_pSubject;
};

/*具体观察目标*/
class ConcreteSubject : public Subject {
public:
    void Attach(Observer *pObserver);

    void Detach(Observer *pObserver);

    void Notify();

    void SetState(int state) {
        m_iState = state;
    }

private:
    list<Observer *> m_ObserverList;//观察者列表
    int m_iState;
};

//添加一个新的观察者
void ConcreteSubject::Attach(Observer *pObserver) {
    m_ObserverList.push_back(pObserver);
}

//移除一个观察者
void ConcreteSubject::Detach(Observer *pObserver) {
    m_ObserverList.remove(pObserver);
}

//通知所有的观察者
void ConcreteSubject::Notify() {
    std::list<Observer *>::iterator it = m_ObserverList.begin();
    while (it != m_ObserverList.end()) {
        (*it)->Update(m_iState);
        ++it;
    }
}

int main() {
    // Create Subject  目标实例化
    ConcreteSubject *pSubject = new ConcreteSubject();

    // Create Observer  创建观察者
    Observer *pObserver1 = new ConcreteObserver1(pSubject);
    Observer *pObserver2 = new ConcreteObserver2(pSubject);

    // Register the observer
    pSubject->Attach(pObserver1);
    pSubject->Attach(pObserver2);

    // Change the state
    pSubject->SetState(2);

    // 观察目标通知所有观察者
    pSubject->Notify();

    // Unregister the observer
    pSubject->Detach(pObserver1);

    pSubject->SetState(3);
    pSubject->Notify();

    delete pObserver1;
    delete pObserver2;
    delete pSubject;
}