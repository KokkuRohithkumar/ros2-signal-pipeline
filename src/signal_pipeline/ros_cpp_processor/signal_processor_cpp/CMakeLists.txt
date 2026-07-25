cmake_minimum_required(VERSION 3.8)
project(signal_processor_cpp)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

# Include your standalone filter library
include_directories(
  include
  ../../standalone_library/include
)

add_executable(signal_processor
  src/signal_processor.cpp
)

ament_target_dependencies(
  signal_processor
  rclcpp
  std_msgs
)

install(TARGETS
  signal_processor
  DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
