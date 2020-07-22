#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <thread>
#include <functional>
#include <queue>
#include <condition_variable>
#include <mutex>
#include <memory>
#include <future>
#include <cassert>


class ThreadPool {
public:
    ThreadPool(int count);

    ~ThreadPool();

    template<typename F, typename... Args>
    auto enqueue(F&& f, Args&&... args)
        -> std::future<typename std::result_of<F(Args...)>::type>;

private:
    //worker
    std::vector<std::thread> m_workers;

    //task queue
    std::queue<std::function<void()>> m_tasks;

    std::mutex m_taskQueueMutex;

    std::condition_variable m_condition;

    bool m_stop;
};

ThreadPool::ThreadPool(int count) : m_stop(false) 
{
    for (int i = 0; i < count; i++) {
        m_workers.emplace_back([this](){
            while (true) {
                std::function<void()> task;
                {
                    std::unique_lock<std::mutex> lock(this->m_taskQueueMutex);
                    this->m_condition.wait(lock, [this](){ 
                        return this->m_stop || !this->m_tasks.empty(); 
                    });
                    if (this->m_stop && this->m_tasks.empty()) {
                        return;
                    }

                    task = std::move(this->m_tasks.front());
                    this->m_tasks.pop();
                }
                task();
            }
        });
    }
}

template<typename F, typename... Args>
auto ThreadPool::enqueue(F&& f, Args&&... args)
    -> std::future<typename std::result_of<F(Args...)>::type>
{
    typedef typename std::result_of<F(Args...)>::type returnType;

    auto task = std::make_shared<std::packaged_task<returnType()> >(
        std::bind(std::forward<F>(f), std::forward<Args>(args)...));

    std::future<returnType> res = task->get_future();
    {
        std::unique_lock<std::mutex> lock(this->m_taskQueueMutex);
        if (m_stop) {
            assert("error");
        }
        m_tasks.emplace([task](){
            (*task)();
        });
        
    }
    m_condition.notify_one();
    return res;
}

ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(this->m_taskQueueMutex);
        m_stop = true;
    }

    m_condition.notify_all();
    for (std::thread &worker : m_workers) {
        worker.join();
    }
}

#endif