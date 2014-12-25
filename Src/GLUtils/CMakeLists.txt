CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(GLUTILS)

SET(CMAKE_C_COMPILER g++)
SET(CMAKE_CXX_COMPILER g++)

IF (NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE RELEASE)
ENDIF (NOT CMAKE_BUILD_TYPE)

#IF (WIN32)
#ELSE(WIN32)
    IF (CMAKE_SIZEOF_VOID_P MATCHES 8)
    if (CMAKE_BUILD_TYPE MATCHES DEBUG)
            SET(GLUTILS_LIB_DIR ${GLUTILS_SOURCE_DIR}/../../Lib/debug_linux_x64)
            SET(LIBRARY_OUTPUT_PATH ${GLUTILS_SOURCE_DIR}/../../Lib/debug_linux_x64)
#            SET(GLUTILS_SRCS_PLATFORM
#                ${GLUTILS_SOURCE_DIR}/../ThirdParty/botan/botan_all_gcc64.cpp
#            )
#            SET(GLUTILS_HDRS_PLATFORM
#                ${GLUTILS_SOURCE_DIR}/../ThirdParty/botan/botan_all_gcc64.h
#            )
            SET(GLUTILS_LIBS_PLATFORM
                libpthread.so
            )
            MESSAGE("GLUtils is VERSION: debug_linux_x64")

        ELSEIF (CMAKE_BUILD_TYPE MATCHES RELEASE)
            SET(GLUTILS_LIB_DIR
                ${GLUTILS_SOURCE_DIR}/../../Lib/release_linux_x64
                ${GLUTILS_SOURCE_DIR}/../../Bin/linux_x64
            )
            SET(LIBRARY_OUTPUT_PATH ${GLUTILS_SOURCE_DIR}/../../Bin/linux_x64)
#            SET(GLUTILS_SRCS_PLATFORM
#                ${GLUTILS_SOURCE_DIR}/../ThirdParty/botan/botan_all_gcc64.cpp
#            )
#            SET(GLUTILS_HDRS_PLATFORM
#                ${GLUTILS_SOURCE_DIR}/../ThirdParty/botan/botan_all_gcc64.h
#            )
            SET(GLUTILS_LIBS_PLATFORM
                libpthread.so
            )
            MESSAGE("GLUtils is VERSION: release_linux_x64")

        ENDIF (CMAKE_BUILD_TYPE MATCHES DEBUG)
    ELSEIF (CMAKE_SIZEOF_VOID_P MATCHES 4) 
        if (CMAKE_BUILD_TYPE MATCHES DEBUG)
            SET(GLUTILS_LIB_DIR ${GLUTILS_SOURCE_DIR}/../../Lib/debug_linux_x86)
            SET(LIBRARY_OUTPUT_PATH ${GLUTILS_SOURCE_DIR}/../../Lib/debug_linux_x86)
#            SET(GLUTILS_SRCS_PLATFORM
#                ${GLUTILS_SOURCE_DIR}/../ThirdParty/botan/botan_all_gcc32.cpp
#            )
#            SET(GLUTILS_HDRS_PLATFORM
#                ${GLUTILS_SOURCE_DIR}/../ThirdParty/botan/botan_all_gcc32.h
#            )
            SET(GLUTILS_LIBS_PLATFORM
                libpthread.so
            )
            MESSAGE("GLUtils is VERSION: debug_linux_x86")

        ELSEIF (CMAKE_BUILD_TYPE MATCHES RELEASE)
            SET(GLUTILS_LIB_DIR
                ${GLUTILS_SOURCE_DIR}/../../Lib/release_linux_x86
                ${GLUTILS_SOURCE_DIR}/../../Bin/linux_x86
            )
            SET(LIBRARY_OUTPUT_PATH ${GLUTILS_SOURCE_DIR}/../../Bin/linux_x86)
#            SET(GLUTILS_SRCS_PLATFORM
#                ${GLUTILS_SOURCE_DIR}/../ThirdParty/botan/botan_all_gcc32.cpp
#            )
#            SET(GLUTILS_HDRS_PLATFORM
#                ${GLUTILS_SOURCE_DIR}/../ThirdParty/botan/botan_all_gcc32.h
#            )
            SET(GLUTILS_LIBS_PLATFORM
                libpthread.so
            )
            MESSAGE("GLUtils is VERSION: release_linux_x86")

        ENDIF (CMAKE_BUILD_TYPE MATCHES DEBUG)
    ENDIF (CMAKE_SIZEOF_VOID_P MATCHES 8)
#ENDIF (WIN32)

SET(GLUTILS_SRCS
    src/GLUtils.cpp
    src/IOManager.cpp
    src/Datatime.cpp
    src/Logger.cpp
    src/Path.cpp
    src/StringOpertion.cpp
    src/Uuid.cpp
    src/ATENEncryption.cpp
    src/MD5Encryption.cpp
)

SET(GLUTILS_HDRS

)

ADD_DEFINITIONS(-DGLUTILS_LIBRARY)

INCLUDE_DIRECTORIES(
    ${GLUTILS_SOURCE_DIR}/../../Inc/GreenLeaf/ThirdParty
    ${GLUTILS_SOURCE_DIR}/../../Inc
)

LINK_DIRECTORIES(${GLUTILS_LIB_DIR})

ADD_LIBRARY(GLUtils SHARED ${GLUTILS_SRCS} ${GLUTILS_SRCS_PLATFORM} ${GLUTILS_HDRS} ${GLUTILS_HDRS_PLATFORM})
TARGET_LINK_LIBRARIES(GLUtils ${GLUTILS_LIBS_PLATFORM})

MESSAGE(STATUS "GLUtils is BINARY dir: " ${GLUTILS_BINARY_DIR})
MESSAGE(STATUS "GLUtils is SOURCE dir: " ${GLUTILS_SOURCE_DIR})
