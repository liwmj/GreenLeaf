#bin/sh

BUILD_OUT_DIR=GreenLeaf_build
BUILD_SRC_DIR=GreenLeaf
BUILD_MAKE_TYPE="Eclipse CDT4 - Unix Makefiles"
BUILD_MAKE_VER=4.2

if [ "$1" == "debug" ]; then
    BUILD_OUT_TYPE=DEBUG
else
    BUILD_OUT_TYPE=RELEASE
fi

cd .. 
rm -rf ${BUILD_OUT_DIR}

mkdir ${BUILD_OUT_DIR}
cd ${BUILD_OUT_DIR}

cmake -G "${BUILD_MAKE_TYPE}" -D CMAKE_BUILD_TYPE=${BUILD_OUT_TYPE} -D_ECLIPSE_VERSION=${BUILD_MAKE_VER} ../${BUILD_SRC_DIR}
make
