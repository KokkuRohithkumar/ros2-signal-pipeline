#ifndef LOWPASSFILTER_HPP
#define LOWPASSFILTER_HPP

#include <cstdint>
#include <cmath>

/*
===============================================================================
 LowPassFilter.hpp

 Features
 --------
 • First-order IIR Low Pass Filter
 • Alpha recomputed every sample using actual dt
 • Floating-point implementation
 • Integer fixed-point (Q15) implementation
 • No floating-point operations inside integer update()
 • Header-only library

 Equation
 --------
 y[n] = y[n-1] + alpha * (x[n] - y[n-1])

 alpha = dt / (RC + dt)

 RC = 1 / (2*pi*cutoff_frequency)

===============================================================================
*/

namespace signal_pipeline
{

//=============================================================================
// Floating Point Version
//=============================================================================
class LowPassFilter
{
public:

    explicit LowPassFilter(float cutoff_frequency_hz = 1.0f)
        : cutoff_frequency_(cutoff_frequency_hz),
          previous_output_(0.0f),
          initialized_(false)
    {
    }

    void setCutoffFrequency(float cutoff_frequency_hz)
    {
        cutoff_frequency_ = cutoff_frequency_hz;
    }

    float getCutoffFrequency() const
    {
        return cutoff_frequency_;
    }

    void reset(float value = 0.0f)
    {
        previous_output_ = value;
        initialized_ = false;
    }

    float update(float input, float dt)
    {
        if (dt <= 0.0f)
            return previous_output_;

        if (!initialized_)
        {
            previous_output_ = input;
            initialized_ = true;
            return previous_output_;
        }

        constexpr float PI = 3.14159265358979323846f;

        float rc = 1.0f / (2.0f * PI * cutoff_frequency_);

        // Recompute alpha every sample
        float alpha = dt / (rc + dt);

        previous_output_ += alpha * (input - previous_output_);

        return previous_output_;
    }

private:

    float cutoff_frequency_;
    float previous_output_;
    bool initialized_;
};

//=============================================================================
// Integer Fixed-Point Version (Q15)
//=============================================================================
class LowPassFilterQ15
{
public:

    /*
        alpha_q15 = alpha * 32768

        Example:

        float alpha = 0.18

        alpha_q15 = 0.18 * 32768 ≈ 5898

        Once calculated,
        update() performs NO floating-point operations.
    */

    explicit LowPassFilterQ15(uint16_t alpha_q15 = 16384)
        : alpha_q15_(alpha_q15),
          previous_output_(0),
          initialized_(false)
    {
    }

    void setAlphaQ15(uint16_t alpha_q15)
    {
        alpha_q15_ = alpha_q15;
    }

    uint16_t getAlphaQ15() const
    {
        return alpha_q15_;
    }

    /*
        Recompute alpha outside the update path.

        This function may use floating-point because it is NOT
        part of the filtering update.
    */
    void computeAlpha(float cutoff_frequency_hz, float dt)
    {
        constexpr float PI = 3.14159265358979323846f;

        float rc = 1.0f / (2.0f * PI * cutoff_frequency_hz);

        float alpha = dt / (rc + dt);

        if (alpha < 0.0f)
            alpha = 0.0f;

        if (alpha > 1.0f)
            alpha = 1.0f;

        alpha_q15_ = static_cast<uint16_t>(alpha * 32768.0f);
    }

    void reset(int32_t value = 0)
    {
        previous_output_ = value;
        initialized_ = false;
    }

    /*
        Integer-only update

        y = y + alpha * (x-y)

        Q15 multiplication:

        alpha_q15 * error >> 15
    */

    int32_t update(int32_t input)
    {
        if (!initialized_)
        {
            previous_output_ = input;
            initialized_ = true;
            return previous_output_;
        }

        int32_t error = input - previous_output_;

        previous_output_ +=
            static_cast<int32_t>(
                (static_cast<int64_t>(alpha_q15_) * error) >> 15);

        return previous_output_;
    }

private:

    uint16_t alpha_q15_;

    int32_t previous_output_;

    bool initialized_;
};

} // namespace signal_pipeline

#endif // LOWPASSFILTER_HPP
