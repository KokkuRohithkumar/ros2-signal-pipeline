#include <iostream>
#include <iomanip>
#include <vector>

#include "filters/MovingAverage.hpp"
#include "filters/LowPassFilter.hpp"
#include "filters/MedianFilter.hpp"

using namespace signal_pipeline;

int main()
{
    //------------------------------------------------------------------
    // Create Filters
    //------------------------------------------------------------------

    MovingAverage<float, 5> movingAverage;

    LowPassFilter lowPass(2.0f);

    MedianFilter<float, 5> median;

    //------------------------------------------------------------------
    // Sample Data
    //------------------------------------------------------------------

    std::vector<float> samples =
    {
        10.0f,
        12.0f,
        15.0f,
        50.0f,   // Outlier
        16.0f,
        18.0f,
        17.0f,
        19.0f,
        20.0f,
        22.0f
    };

    float dt = 0.01f;

    //------------------------------------------------------------------
    // Print Table Header
    //------------------------------------------------------------------

    std::cout << std::fixed << std::setprecision(2);

    std::cout
        << std::left
        << std::setw(12) << "Input"
        << std::setw(15) << "Moving Avg"
        << std::setw(15) << "Low Pass"
        << std::setw(15) << "Median"
        << std::endl;

    std::cout
        << "-------------------------------------------------------------"
        << std::endl;

    //------------------------------------------------------------------
    // Process Samples
    //------------------------------------------------------------------

    for (float sample : samples)
    {
        float movingAverageOutput =
            movingAverage.update(sample, dt);

        float lowPassOutput =
            lowPass.update(sample, dt);

        float medianOutput =
            median.update(sample);

        std::cout
            << std::left
            << std::setw(12) << sample
            << std::setw(15) << movingAverageOutput
            << std::setw(15) << lowPassOutput
            << std::setw(15) << medianOutput
            << std::endl;
    }

    std::cout << "\nFilter test completed successfully.\n";

    return 0;
}
