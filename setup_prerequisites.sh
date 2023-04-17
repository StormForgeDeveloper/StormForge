#!/bin/bash

# Copyright Kyungkun Ko

. ../build/setup_build_env.sh

# for Icu
sudo apt install autoconf autoconf-archive
# for GetText
sudo apt install bison
# for openssl through vcpkg
sudo apt install linux-libc-dev
# for freetype -> freeglut
sudo apt install libxi-dev libgl1-mesa-dev libglu1-mesa-dev mesa-common-dev libxrandr-dev libxxf86vm-dev
# for Vulkan
sudo apt install vulkan-sdk
