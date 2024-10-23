#!/bin/sh

# ====================== #
# - aulos setup script - #
# ====================== #

# Download Buildroot source and extract it into a pretty directory
wget https://buildroot.org/downloads/buildroot-2024.02.1.tar.gz
mkdir buildroot && tar -xf buildroot-2024.02.1.tar.gz -C buildroot --strip-components 1
rm buildroot-2024.02.1.tar.gz
cd buildroot

# Setup the Raspberry Pi defconfig
make raspberrypi4_64_defconfig

# Copy over aulos config changes
cp ../external/board/aulos/aulos.config .config

# Setup the external tree
make BR2_EXTERNAL=../external menuconfig
