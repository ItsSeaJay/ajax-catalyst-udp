# Ensure that this file can only be run with modern CMake versions
cmake_minimum_required(VERSION 3.0)

# Tell CMake what the project is called
project(AjaxCatalyst)

# Add subdirectories for each executable file
add_subdirectory(client)
add_subdirectory(servers)