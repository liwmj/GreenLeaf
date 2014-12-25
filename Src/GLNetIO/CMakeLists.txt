CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(GLNETIO)

SET(CMAKE_C_COMPILER g++)
SET(CMAKE_CXX_COMPILER g++)

IF (NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE RELEASE)
ENDIF (NOT CMAKE_BUILD_TYPE)

#IF (WIN32)
#ELSE(WIN32)
    IF (CMAKE_SIZEOF_VOID_P MATCHES 8)
        if (CMAKE_BUILD_TYPE MATCHES DEBUG)
            SET(GLNETIO_LIB_DIR ${GLNETIO_SOURCE_DIR}/../../Lib/debug_linux_x64)
            SET(LIBRARY_OUTPUT_PATH ${GLNETIO_SOURCE_DIR}/../../Lib/debug_linux_x64)
            SET(GLNETIO_LIBS_PLATFORM
                #libboost_system-gcc48-mt-sd-1_56.a
                #libboost_thread-gcc48-mt-sd-1_56.a
                libpthread.so
            )
            MESSAGE("GLNetIO is VERSION: debug_linux_x64")

        ELSEIF (CMAKE_BUILD_TYPE MATCHES RELEASE)
            SET(GLNETIO_LIB_DIR
                ${GLNETIO_SOURCE_DIR}/../../Lib/release_linux_x64
                ${GLNETIO_SOURCE_DIR}/../../Bin/linux_x64
            )
            SET(LIBRARY_OUTPUT_PATH ${GLNETIO_SOURCE_DIR}/../../Bin/linux_x64)
            SET(GLNETIO_LIBS_PLATFORM
                #libboost_system-gcc48-mt-s-1_56.a
                #libboost_thread-gcc48-mt-s-1_56.a
                libpthread.so
            )
            MESSAGE("GLNetIO is VERSION: release_linux_x64")

        ENDIF (CMAKE_BUILD_TYPE MATCHES DEBUG)
    ELSEIF (CMAKE_SIZEOF_VOID_P MATCHES 4)
        if (CMAKE_BUILD_TYPE MATCHES DEBUG)
            SET(GLNETIO_LIB_DIR ${GLNETIO_SOURCE_DIR}/../../Lib/debug_linux_x86)
            SET(LIBRARY_OUTPUT_PATH ${GLNETIO_SOURCE_DIR}/../../Lib/debug_linux_x86)
            SET(GLNETIO_LIBS_PLATFORM
                libpthread.so
            )
            MESSAGE("GLNetIO is VERSION: debug_linux_x86")

        ELSEIF (CMAKE_BUILD_TYPE MATCHES RELEASE)
            SET(GLNETIO_LIB_DIR
                ${GLNETIO_SOURCE_DIR}/../../Lib/release_linux_x86
                ${GLNETIO_SOURCE_DIR}/../../Bin/linux_x86
            )
            SET(LIBRARY_OUTPUT_PATH ${GLNETIO_SOURCE_DIR}/../../Bin/linux_x86)
            SET(GLNETIO_LIBS_PLATFORM
                libpthread.so
            )
            MESSAGE("GLNetIO is VERSION: release_linux_x86")

        ENDIF (CMAKE_BUILD_TYPE MATCHES DEBUG)
    ENDIF (CMAKE_SIZEOF_VOID_P MATCHES 8)
#ENDIF (WIN32)

SET(GLNETIO_SRCS
    src/GLNetIO.cpp
    src/TcpAcceptor.cpp
    src/TcpConnection.cpp
    src/UdpEndPoint.cpp
    src/HttpRequest.cpp
    src/ParseRequestData.cpp
    src/BundleResponseData.cpp
    src/ActiveTcpConnection.cpp
    src/Connections.cpp
    src/Sessions.cpp
    src/SessionManager.cpp
)

SET(GLNETIO_HDRS

)

ADD_DEFINITIONS(-DGLNETIO_LIBRARY)

INCLUDE_DIRECTORIES(
    ${GLNETIO_SOURCE_DIR}/../../Inc/GreenLeaf/ThirdParty
    ${GLNETIO_SOURCE_DIR}/../../Inc
)

LINK_DIRECTORIES(${GLNETIO_LIB_DIR})

ADD_LIBRARY(GLNetIO SHARED ${GLNETIO_SRCS} ${GLNETIO_HDRS})
TARGET_LINK_LIBRARIES(GLNetIO ${GLNETIO_LIBS_PLATFORM})
ADD_DEPENDENCIES(GLNetIO GLUtils)

MESSAGE(STATUS "GLNetIO is BINARY dir:" ${GLNETIO_BINARY_DIR})
MESSAGE(STATUS "GLNetIO is SOURCE dir:" ${GLNETIO_SOURCE_DIR})
