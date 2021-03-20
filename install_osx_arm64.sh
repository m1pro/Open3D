#!/usr/bin/env bash
# activate the desired conda env and run from root open3d folder 
set -e

echo "installing pre-requisited"
sudo port install openblas
sudo ln -s /opt/local/include/cblas_openblas.h /opt/local/include/cblas.h
sudo chown root:admin /opt/local/include/cblas.h
brew install libpng

echo "build open3d and install to the current conda env"
pushd build
cmake -DCMAKE_INSTALL_PREFIX=$CONDA_PREFIX ..
make install-pip-package -j8 
popd
