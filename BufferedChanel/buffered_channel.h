#ifndef BUFFEREDCHANEL_BUFFERED_CHANNEL_H
#define BUFFEREDCHANEL_BUFFERED_CHANNEL_H

#include <queue>
#include <mutex>
#include <condition_variable>

template<class T>
class BufferedChannel {
public:
    explicit BufferedChannel(size_t size) : size_(size), is_open_(true) {}

    void Send(T value) {
        std::unique_lock<std::mutex> locker(mutex_);
        cond_var_.wait(locker, [this]() { return (queue_.size() < size_ || !is_open_); });

        if (!is_open_) {
            throw (std::runtime_error("Channel is closed!"));
        }

        queue_.push(value);
        locker.unlock();
        cond_var_.notify_all();
    }

    std::pair<T, bool> Recv() {
        std::unique_lock<std::mutex> locker(this->mutex_);
        cond_var_.wait(locker, [this]() { return (!this->queue_.empty() || !is_open_); });

        if (queue_.empty()) {
            locker.unlock();
            return std::make_pair(T(), false);
        }

        std::pair<T, bool> pair(queue_.front(), true);
        queue_.pop();
        locker.unlock();
        cond_var_.notify_all();
        return pair;
    }

    void Close() {
        std::unique_lock<std::mutex> lock(this->mutex_);
        is_open_ = false;
        lock.unlock();
        cond_var_.notify_all();
    }

private:
    std::queue<T> queue_;
    size_t size_;
    std::mutex mutex_;
    std::condition_variable cond_var_;
    bool is_open_;
};


#endif //BUFFEREDCHANEL_BUFFERED_CHANNEL_H
