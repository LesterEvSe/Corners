#!/bin/bash

distro=$(cat /etc/os-release | grep '^ID=' | awk -F'=' '{print $2}' | tr -d '"')

# The -y flag indicates tha packages are installed automatically,
# withut confirmation
if [[ $distro == "ubuntu" || $distro == "debian" || $distro == "linuxmint" ]]; then
    sudo apt-get update
    sudo apt-get install -y libsfml-dev g++ cmake
    
elif [[ $distro == "centos" || $distro == "rhel" ]]; then
    # epel-release - The EPEL (Extra Packages for Enterprise Linux),
    # which provides additional packages for these distributions.
    sudo yum install -y epel-release
    sudo yum install -y sfml-devel gcc-c++ cmake

elif [[ $distro == "fedora" ]]; then
    sudo dnf install -y sfml-devel gcc-c++ cmake
    
elif [[ $distro == "arch" ]]; then
    # -S - install the package
    # --noconfirm - No need to confirm each package
    sudo pacman -Sy sfml gcc cmake

else
    echo "Unsupported Linux distribution: $distro"
    exit 1
fi

echo "Installation of SFML, g++ and CMake completed successfully."

# go to the upper directory
# if the directory exists, do not create it
# go to it
cd ..
mkdir -p build
cd build

# create and run the makefile
echo "Build the project."
cmake ..
make
