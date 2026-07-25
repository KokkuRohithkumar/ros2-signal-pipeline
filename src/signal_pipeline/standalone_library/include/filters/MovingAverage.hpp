#ifndef MOVINGAVERAGE_HPP
#define MOVINGAVERAGE_HPP

#include "RingBuffer.hpp"
#include "FilterBase.hpp"

#include <type_traits>
#include <cstdint>

template<typename T, std::size_t WindowSize>
class MovingAverage : public FilterBase<T>
{
private:

    using Accumulator = std::conditional_t<
        std::is_integral_v<T>,
        int64_t,
        double>;

    RingBuffer<T, WindowSize> buffer_;

    Accumulator sum_;

    bool filled_;

public:

    MovingAverage()
        : sum_(0),
          filled_(false)
    {
    }

    T update(T sample, double dt) override
    {
        (void)dt;

        // Remove oldest sample when buffer is full
        if (buffer_.full())
        {
            sum_ -= static_cast<Accumulator>(buffer_.get(0));
        }

        // Insert newest sample
        buffer_.push(sample);

        // Add newest sample to running sum
        sum_ += static_cast<Accumulator>(sample);

        // Update buffer status
        filled_ = buffer_.full();

        // Current number of valid samples
        const std::size_t count = buffer_.size();
        if (count == 0)
        {
            return T{};
        }

        if constexpr (std::is_integral_v<T>)
        {
            return static_cast<T>(
                sum_ / static_cast<Accumulator>(count));
        }
        else
        {
            return static_cast<T>(
                sum_ / static_cast<double>(count));
        }
    }

    void reset() override
    {
        sum_ = 0;
        filled_ = false;
        buffer_ = RingBuffer<T, WindowSize>();
    }

    bool isFilled() const
    {
        return filled_;
    }
};

#endif
