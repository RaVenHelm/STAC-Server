#!/bin/bash
BOOST_BUILD_DIR=$1

bash bootstrap.sh

./bjam --disable-icu -q --prefix=$BOOST_BUILD_DIR --without-python \
--without-log --without-mpi --toolset=gcc link=shared \
threading=multi variant=release address-model=64 architecture=x86 \
cxxflags='-std=c++11 -Wno-unused-local-typedefs' \
install
