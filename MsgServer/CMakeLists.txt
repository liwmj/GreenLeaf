CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(MSGSERVER)

SET(CMAKE_C_COMPILER g++)
SET(CMAKE_CXX_COMPILER g++)

IF (NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE RELEASE)
ENDIF (NOT CMAKE_BUILD_TYPE)

#IF (WIN32)
#ELSE(WIN32)
    IF (CMAKE_SIZEOF_VOID_P MATCHES 8)
        if (CMAKE_BUILD_TYPE MATCHES DEBUG)
            SET(MSGSERVER_LIB_DIR ${MSGSERVER_SOURCE_DIR}/../Lib/debug_linux_x64)
            SET(EXECUTABLE_OUTPUT_PATH ${MSGSERVER_SOURCE_DIR}/../Lib/debug_linux_x64)
            SET(MSGSERVER_LIBS_PLATFORM
                libGLUtils.so
                libGLDiskIO.so
                libGLNetIO.so
                libGLDBIO.so
                libpthread.so
                libmysqlclient.so.18
                libodbc.so.1

                libboost_system-gcc48-mt-sd-1_56.a
                libboost_thread-gcc48-mt-sd-1_56.a
                libboost_filesystem-gcc48-mt-sd-1_56.a
            )
            MESSAGE("MsgServer is VERSION: debug_linux_x64")

        ELSEIF (CMAKE_BUILD_TYPE MATCHES RELEASE)
            SET(MSGSERVER_LIB_DIR
                ${MSGSERVER_SOURCE_DIR}/../Lib/release_linux_x64
                ${MSGSERVER_SOURCE_DIR}/../Bin/linux_x64
            )
            SET(EXECUTABLE_OUTPUT_PATH ${MSGSERVER_SOURCE_DIR}/../Bin/linux_x64)
            SET(MSGSERVER_LIBS_PLATFORM
                libGLUtils.so
                libGLDiskIO.so
                libGLNetIO.so
                libGLDBIO.so
                libpthread.so
                libmysqlclient.so.18
                libodbc.so.1

                libboost_system-gcc48-mt-s-1_56.a
                libboost_thread-gcc48-mt-s-1_56.a
                libboost_filesystem-gcc48-mt-s-1_56.a
			)
            MESSAGE("MsgServer is VERSION: release_linux_x64")

        ENDIF (CMAKE_BUILD_TYPE MATCHES DEBUG)
    ELSEIF (CMAKE_SIZEOF_VOID_P MATCHES 4)
        if (CMAKE_BUILD_TYPE MATCHES DEBUG)
            SET(MSGSERVER_LIB_DIR ${MSGSERVER_SOURCE_DIR}/../Lib/debug_linux_x86)
            SET(EXECUTABLE_OUTPUT_PATH ${MSGSERVER_SOURCE_DIR}/../Lib/debug_linux_x86)
            SET(MSGSERVER_LIBS_PLATFORM
                libpthread.so
            )
            MESSAGE("MsgServer is VERSION: debug_linux_x86")

        ELSEIF (CMAKE_BUILD_TYPE MATCHES RELEASE)
            SET(MSGSERVER_LIB_DIR
                ${MSGSERVER_SOURCE_DIR}/../Lib/release_linux_x86
                ${MSGSERVER_SOURCE_DIR}/../Bin/linux_x86
            )
            SET(EXECUTABLE_OUTPUT_PATH ${MSGSERVER_SOURCE_DIR}/../Bin/linux_x86)
            SET(MSGSERVER_LIBS_PLATFORM
                libpthread.so
            )
            MESSAGE("MsgServer is VERSION: release_linux_x86")

        ENDIF (CMAKE_BUILD_TYPE MATCHES DEBUG)
    ENDIF (CMAKE_SIZEOF_VOID_P MATCHES 8)
#ENDIF (WIN32)

SET(MSGSERVER_SRCS
    src/main.cpp
    src/MsgServer.cpp
    src/MsgServerImpl.cpp
    src/UserManager.cpp
    src/DataCacheManager.cpp
    src/HandlerManager.cpp
    src/HandlerCommon.cpp
    src/handlers/CCLHandler.cpp
)

SET(MSGSERVER_HDRS

)

INCLUDE_DIRECTORIES(
    ${MSGSERVER_SOURCE_DIR}/../Inc/GreenLeaf/ThirdParty
    ${MSGSERVER_SOURCE_DIR}/../Inc
    ${MSGSERVER_SOURCE_DIR}/inc
)

LINK_DIRECTORIES(${MSGSERVER_LIB_DIR})

ADD_EXECUTABLE(MsgServer ${MSGSERVER_SRCS} ${MSGSERVER_HDRS})
TARGET_LINK_LIBRARIES(MsgServer ${MSGSERVER_LIBS_PLATFORM})
ADD_DEPENDENCIES(MsgServer GLDBIO GLNetIO GLDiskIO GLUtils)

MESSAGE(STATUS "MsgServer is BINARY dir:" ${MSGSERVER_BINARY_DIR})
MESSAGE(STATUS "MsgServer is SOURCE dir:" ${MSGSERVER_SOURCE_DIR})
