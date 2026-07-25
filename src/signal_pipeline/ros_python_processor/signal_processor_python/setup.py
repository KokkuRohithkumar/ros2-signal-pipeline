from setuptools import find_packages, setup

package_name = "signal_processor_python"

setup(
    name=package_name,
    version="0.0.0",
    packages=find_packages(exclude=["test"]),
    data_files=[
        (
            "share/ament_index/resource_index/packages",
            ["resource/" + package_name],
        ),
        (
            "share/" + package_name,
            ["package.xml"],
        ),
    ],
    install_requires=[
        "setuptools",
    ],
    zip_safe=True,
    maintainer="kokkurohithkumar",
    maintainer_email="your-email@example.com",
    description="ROS2 Python Signal Processor using pybind11 filters",
    license="MIT",
    tests_require=["pytest"],
    entry_points={
        "console_scripts": [
            "processor_node = signal_processor_python.processor_node:main",
        ],
    },
)
