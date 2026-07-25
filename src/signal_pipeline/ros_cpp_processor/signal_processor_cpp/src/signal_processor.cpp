#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"
#include "std_msgs/msg/float32.hpp"

#include "filters/MovingAverage.hpp"
#include "filters/LowPassFilter.hpp"

using std::placeholders::_1;

class SignalProcessor : public rclcpp::Node
{
public:

    SignalProcessor()
        : Node("signal_processor_cpp"),
          moving_average_int_(),
          moving_average_float_(),
          lowpass_(2.0f)
    {
        int_sub_ = this->create_subscription<std_msgs::msg::Int32>(
            "/signal/int",
            10,
            std::bind(&SignalProcessor::intCallback, this, _1));

        float_sub_ = this->create_subscription<std_msgs::msg::Float32>(
            "/signal/float",
            10,
            std::bind(&SignalProcessor::floatCallback, this, _1));

        RCLCPP_INFO(this->get_logger(),
                    "C++ Signal Processor Started");
    }

private:

    //-----------------------------------
    // Filters
    //-----------------------------------

    MovingAverage<int,5> moving_average_int_;

    MovingAverage<float,5> moving_average_float_;

    signal_pipeline::LowPassFilter lowpass_;

    //-----------------------------------
    // Subscribers
    //-----------------------------------

    rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr int_sub_;

    rclcpp::Subscription<std_msgs::msg::Float32>::SharedPtr float_sub_;

    //-----------------------------------
    // Integer callback
    //-----------------------------------

    void intCallback(
        const std_msgs::msg::Int32::SharedPtr msg)
    {
        int filtered =
            moving_average_int_.update(
                msg->data,
                0.02);

        RCLCPP_INFO(
            this->get_logger(),
            "INT Raw=%d  MovingAverage=%d",
            msg->data,
            filtered);
    }

    //-----------------------------------
    // Float callback
    //-----------------------------------

    void floatCallback(
        const std_msgs::msg::Float32::SharedPtr msg)
    {
        float average =
            moving_average_float_.update(
                msg->data,
                0.02);

        float lowpass =
            lowpass_.update(
                average,
                0.02f);

        RCLCPP_INFO(
            this->get_logger(),
            "FLOAT Raw=%.3f  Avg=%.3f  LowPass=%.3f",
            msg->data,
            average,
            lowpass);
    }
};

int main(int argc,char **argv)
{
    rclcpp::init(argc,argv);

    rclcpp::spin(
        std::make_shared<SignalProcessor>());

    rclcpp::shutdown();

    return 0;
}
