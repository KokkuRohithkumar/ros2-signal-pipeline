#include <pybind11/pybind11.h>

#include "filters/MovingAverage.hpp"
#include "filters/MedianFilter.hpp"
#include "filters/LowPassFilter.hpp"

namespace py = pybind11;

// Template aliases exposed to Python
using MovingAverageFloat = MovingAverage<float, 5>;
using MovingAverageInt   = MovingAverage<int, 5>;

using MedianFilterFloat = signal_pipeline::MedianFilter<float, 5>;
using MedianFilterInt   = signal_pipeline::MedianFilter<int, 5>;

PYBIND11_MODULE(signal_pipeline, m)
{
    m.doc() = "Python bindings for Signal Pipeline filters";

    // ==========================================================
    // MovingAverage<float,5>
    // ==========================================================
    py::class_<MovingAverageFloat>(m, "MovingAverageFloat")
        .def(py::init<>())
        .def("update",
             &MovingAverageFloat::update,
             py::arg("sample"),
             py::arg("dt"))
        .def("reset",
             &MovingAverageFloat::reset)
        .def("isFilled",
             &MovingAverageFloat::isFilled);

    // ==========================================================
    // MovingAverage<int,5>
    // ==========================================================
    py::class_<MovingAverageInt>(m, "MovingAverageInt")
        .def(py::init<>())
        .def("update",
             &MovingAverageInt::update,
             py::arg("sample"),
             py::arg("dt"))
        .def("reset",
             &MovingAverageInt::reset)
        .def("isFilled",
             &MovingAverageInt::isFilled);

    // ==========================================================
    // MedianFilter<float,5>
    // ==========================================================
    py::class_<MedianFilterFloat>(m, "MedianFilterFloat")
        .def(py::init<>())
        .def("update",
             &MedianFilterFloat::update)
        .def("reset",
             &MedianFilterFloat::reset)
        .def("windowSize",
             &MedianFilterFloat::windowSize)
        .def("sampleCount",
             &MedianFilterFloat::sampleCount)
        .def("isFull",
             &MedianFilterFloat::isFull);

    // ==========================================================
    // MedianFilter<int,5>
    // ==========================================================
    py::class_<MedianFilterInt>(m, "MedianFilterInt")
        .def(py::init<>())
        .def("update",
             &MedianFilterInt::update)
        .def("reset",
             &MedianFilterInt::reset)
        .def("windowSize",
             &MedianFilterInt::windowSize)
        .def("sampleCount",
             &MedianFilterInt::sampleCount)
        .def("isFull",
             &MedianFilterInt::isFull);

    // ==========================================================
    // LowPassFilter
    // ==========================================================
    py::class_<signal_pipeline::LowPassFilter>(m, "LowPassFilter")
        .def(py::init<float>(),
             py::arg("cutoff_frequency_hz") = 1.0f)
        .def("update",
             &signal_pipeline::LowPassFilter::update,
             py::arg("input"),
             py::arg("dt"))
        .def("reset",
             &signal_pipeline::LowPassFilter::reset,
             py::arg("value") = 0.0f)
        .def("setCutoffFrequency",
             &signal_pipeline::LowPassFilter::setCutoffFrequency)
        .def("getCutoffFrequency",
             &signal_pipeline::LowPassFilter::getCutoffFrequency);

    // ==========================================================
    // LowPassFilterQ15
    // ==========================================================
    py::class_<signal_pipeline::LowPassFilterQ15>(m, "LowPassFilterQ15")
        .def(py::init<uint16_t>(),
             py::arg("alpha_q15") = 16384)
        .def("update",
             &signal_pipeline::LowPassFilterQ15::update)
        .def("reset",
             &signal_pipeline::LowPassFilterQ15::reset,
             py::arg("value") = 0)
        .def("computeAlpha",
             &signal_pipeline::LowPassFilterQ15::computeAlpha)
        .def("setAlphaQ15",
             &signal_pipeline::LowPassFilterQ15::setAlphaQ15)
        .def("getAlphaQ15",
             &signal_pipeline::LowPassFilterQ15::getAlphaQ15);
}
