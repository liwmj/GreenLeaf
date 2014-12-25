CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(GLDISKIO)

SET(CMAKE_C_COMPILER g++)
SET(CMAKE_CXX_COMPILER g++)

IF (NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE RELEASE)
ENDIF (NOT CMAKE_BUILD_TYPE)

#IF (WIN32)
#ELSE(WIN32)
    IF (CMAKE_SIZEOF_VOID_P MATCHES 8)
        if (CMAKE_BUILD_TYPE MATCHES DEBUG)
            SET(GLDISKIO_LIB_DIR ${GLDISKIO_SOURCE_DIR}/../../Lib/debug_linux_x64)
            SET(LIBRARY_OUTPUT_PATH ${GLDISKIO_SOURCE_DIR}/../../Lib/debug_linux_x64)
            SET(GLDISKIO_LIBS_PLATFORM
                libpthread.so
            )
            MESSAGE("GLDiskIO is VERSION: debug_linux_x64")

        ELSEIF (CMAKE_BUILD_TYPE MATCHES RELEASE)
            SET(GLDISKIO_LIB_DIR
                ${GLDISKIO_SOURCE_DIR}/../../Lib/release_linux_x64
                ${GLDISKIO_SOURCE_DIR}/../../Bin/linux_x64
            )
            SET(LIBRARY_OUTPUT_PATH ${GLDISKIO_SOURCE_DIR}/../../Bin/linux_x64)
            SET(GLDISKIO_LIBS_PLATFORM
                libpthread.so
            )
            MESSAGE("GLDiskIO is VERSION: release_linux_x64")

        ENDIF (CMAKE_BUILD_TYPE MATCHES DEBUG)
    ELSEIF (CMAKE_SIZEOF_VOID_P MATCHES 4)
        if (CMAKE_BUILD_TYPE MATCHES DEBUG)
            SET(GLDISKIO_LIB_DIR ${GLDISKIO_SOURCE_DIR}/../../Lib/debug_linux_x86)
            SET(LIBRARY_OUTPUT_PATH ${GLDISKIO_SOURCE_DIR}/../../Lib/debug_linux_x86)
            SET(GLDISKIO_LIBS_PLATFORM
                libpthread.so
            )
            MESSAGE("GLDiskIO is VERSION: debug_linux_x86")

        ELSEIF (CMAKE_BUILD_TYPE MATCHES RELEASE)
            SET(GLDISKIO_LIB_DIR
                ${GLDISKIO_SOURCE_DIR}/../../Lib/release_linux_x86
                ${GLDISKIO_SOURCE_DIR}/../../Bin/linux_x86
            )
            SET(LIBRARY_OUTPUT_PATH ${GLDISKIO_SOURCE_DIR}/../../Bin/linux_x86)
            SET(GLDISKIO_LIBS_PLATFORM
                libpthread.so
            )
            MESSAGE("GLDiskIO is VERSION: release_linux_x86")

        ENDIF (CMAKE_BUILD_TYPE MATCHES DEBUG)
    ENDIF (CMAKE_SIZEOF_VOID_P MATCHES 8)
#ENDIF (WIN32)

SET(GLDISKIO_SRCS
    src/GLDiskIO.cpp
    src/IniParse.cpp
    src/XmlParse.cpp
    src/JsonParse.cpp
)

SET(GLDISKIO_HDRS

)

ADD_DEFINITIONS(-DGLDISKIO_LIBRARY)

INCLUDE_DIRECTORIES(
    ${GLDISKIO_SOURCE_DIR}/../../Inc/GreenLeaf/ThirdParty
    ${GLDISKIO_SOURCE_DIR}/../../Inc
)

LINK_DIRECTORIES(${GLDISKIO_LIB_DIR})

ADD_LIBRARY(GLDiskIO SHARED ${GLDISKIO_SRCS} ${GLDISKIO_HDRS})
TARGET_LINK_LIBRARIES(GLDiskIO ${GLDISKIO_LIBS_PLATFORM})
ADD_DEPENDENCIES(GLDiskIO GLUtils)

MESSAGE(STATUS "GLDiskIO is BINARY dir:" ${GLDISKIO_BINARY_DIR})
MESSAGE(STATUS "GLDiskIO is SOURCE dir:" ${GLDISKIO_SOURCE_DIR})
