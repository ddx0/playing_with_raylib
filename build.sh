#!/bin/zsh

# simple and lean build script - builds program and installs game library along
#     with pkg-config file for future development use. usually we would install
#     to /usr/local but in order to prevent any possible issues with my
#     generically named code, the default is $HOME/.local. If changed, consider
#     changing logger.pc prefix accordingly.

PREFIX="$HOME/.local"
EXE_OUT_DIR="."       # a bin folder will be created in this dir
PROG_NAME="main"      # change when exe name changes in Makefile
# local build dir
mkdir -p ./{main,logger}/build
mkdir -p $EXE_OUT_DIR/bin
# library stuff
mkdir -p $PREFIX/include
mkdir -p $PREFIX/lib
mkdir -p $PREFIX/lib/pkgconfig
echo "export PKG_CONFIG_PATH=$PREFIX/lib/pkgconfig:$PKG_CONFIG_PATH" > source_me_for_local_pkg.sh
# build
cd ./main && make
cd ../logger
# library installation
cp include/logger.h $PREFIX/include/
cp build/logger.o $PREFIX/lib/
cd ..
cp ./logger.pc $PREFIX/lib/pkgconfig/
# cleanup
cd ./main && make clean