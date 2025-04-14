from setuptools import find_packages
from setuptools import setup

setup(
    name='rft_sensor_serial',
    version='0.0.1',
    packages=find_packages(
        include=('rft_sensor_serial', 'rft_sensor_serial.*')),
)
