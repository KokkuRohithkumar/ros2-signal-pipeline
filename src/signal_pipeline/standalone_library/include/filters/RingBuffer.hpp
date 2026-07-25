#ifndef RINGBUFFER_HPP
#define RINGBUFFER_HPP

#include <array>
#include <cstddef>

template<typename T, std::size_t Size>
class RingBuffer
{
public:

    RingBuffer()
        : head_(0),
          count_(0)
    {
    }

    void push(const T& value)
    {
        buffer_[head_] = value;

        head_ = (head_ + 1) % Size;

        if(count_ < Size)
            count_++;
    }

    T get(std::size_t index) const
    {
        std::size_t pos =
            (head_ + Size - count_ + index) % Size;

        return buffer_[pos];
    }

    std::size_t size() const
    {
        return count_;
    }

    bool full() const
    {
        return count_ == Size;
    }

private:

    std::array<T, Size> buffer_;

    std::size_t head_;

    std::size_t count_;
};

#endif
