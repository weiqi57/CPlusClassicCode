#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
#include <list>

template <typename T>
class threadpool {
   public:
    threadpool(int thread_number, int request_number);
    ~threadpool();
    static void* worker(void* arg);
    void run();
    bool append(T* request);

   private:
    pthread_t* threadArray;
    int threadNumber;
    int maxRequestNumber;
    pthread_mutex_t mutex;
    sem_t semthreads;
    std::list<T*> worklist;
};

template <typename T>
threadpool<T>::threadpool(int thread_number, int request_number) {
    pthread_mutex_init(&mutex, NULL);
    sem_init(&semthreads, 0, 0);

    threadArray = new pthread_t[thread_number];

    for (int i = 0; i < thread_number; i++) {
        pthread_create(&threadArray[i], NULL, worker, this);

        // pthread_detach(threadArray + i);  //error! 应该传变量，而不是指针
        pthread_detach(threadArray[i]);
    }

}

template <typename T>
threadpool<T>::~threadpool() {
    pthread_mutex_destroy(&mutex);
    sem_destroy(&semthreads);
    delete[] threadArray;
}

template <typename T>
void* threadpool<T>::worker(void* arg) {
    threadpool* pool = (threadpool*)arg;
    pool->run;
    return NULL;
}

template <typename T>
void threadpool<T>::run() {
    while (1) {
        pthread_mutex_lock(&mutex);
        sem_wait(&semthreads);

        if (worklist.empty()) {
            pthread_mutex_unlock(&mutex);
            continue;
        }
        T* request = worklist.front();
        worklist.pop_front();

        pthread_mutex_unlock(&mutex);

        request->process;
    }
}

template <typename T>
bool threadpool<T>::append(T* request) {
    pthread_mutex_lock(&mutex);

    if (worklist.size() >= maxRequestNumber) {
        pthread_mutex_unlock(&mutex);
        return false;
    }
    worklist.push_back(request);
    pthread_mutex_unlock(&mutex);
    sem_post(&semthreads);

    return true;
}


int main(){
    return 0;
}