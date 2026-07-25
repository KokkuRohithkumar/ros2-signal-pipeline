from setuptools import find_packages, setup

package_name = 'signal_publisher'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        (
            'share/ament_index/resource_index/packages',
            ['resource/' + package_name]
        ),
        (
            'share/' + package_name,
            ['package.xml']
        ),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='kokkurohithkumar',
    maintainer_email='your-email@example.com',
    description='ROS2 Synthetic Signal Publisher',
    license='MIT',
    extras_require={
        'test': ['pytest'],
    },
    entry_points={
        'console_scripts': [
            'publisher_node = signal_publisher.publisher_node:main',
        ],
    },
)
