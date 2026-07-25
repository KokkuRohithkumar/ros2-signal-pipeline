#ifndef MEDIANFILTER_HPP
#define MEDIANFILTER_HPP

#include <array>
#include <cstddef>
#include <cstdint>

/*
===============================================================================
 MedianFilter.hpp

 Features
 --------
 • Fixed-size ring buffer
 • Small fixed array copy
 • Simple insertion sort
 • Returns median value
 • Header-only implementation
 • Template-based
 • No dynamic memory allocation
 • Can be added without modifying existing filter implementations

===============================================================================
*/

namespace signal_pipeline
{

template<typename T, std::size_t WindowSize>
class MedianFilter
{
    static_assert(WindowSize > 0,
                  "WindowSize must be greater than zero.");

public:

    MedianFilter()
        : index_(0),
          count_(0)
    {
        buffer_.fill(T{});
    }

    void reset()
    {
        buffer_.fill(T{});
        index_ = 0;
        count_ = 0;
    }

    T update(T sample)
    {
        // Store newest sample into ring buffer
        buffer_[index_] = sample;

        index_ = (index_ + 1) % WindowSize;

        if (count_ < WindowSize)
            ++count_;

        // Copy only valid samples
        std::array<T, WindowSize> temp{};

        for (std::size_t i = 0; i < count_; ++i)
        {
            temp[i] = buffer_[i];
        }

        // Insertion Sort
        for (std::size_t i = 1; i < count_; ++i)
        {
            T key = temp[i];
            std::size_t j = i;

            while (j > 0 && temp[j - 1] > key)
            {
                temp[j] = temp[j - 1];
                --j;
            }

            temp[j] = key;
        }

        // Return median
        if (count_ % 2 == 1)
        {
            return temp[count_ / 2];
        }
        else
        {
            return static_cast<T>(
                (temp[count_ / 2 - 1] + temp[count_ / 2]) / 2);
        }
    }

    constexpr std::size_t windowSize() const
    {
        return WindowSize;
    }

    std::size_t sampleCount() const
    {
        return count_;
    }

    bool isFull() const
    {
        return count_ == WindowSize;
    }

private:

    std::array<T, WindowSize> buffer_;

    std::size_t index_;

    std::size_t count_;
};

} // namespace signal_pipeline

#endif // MEDIANFILTER_HPP
