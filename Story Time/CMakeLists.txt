cmake_minimum_required(VERSION 2.8)
project(read)

find_package(qibuild)

# Create a executable named read
# with the source file: main.cpp
#qi_create_bin(read "main.cpp")
qi_create_bin(Storybook "Storybook.cpp")
qi_use_lib(Storybook ALCOMMON ALPROXIES ALAUDIO)

# Add a simple test:
qi_create_test(test_read "test.cpp")
