CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(GLDBIO)

SET(CMAKE_C_COMPILER g++)
SET(CMAKE_CXX_COMPILER g++)

IF (NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE RELEASE)
ENDIF (NOT CMAKE_BUILD_TYPE)

#IF (WIN32)
#ELSE(WIN32)
    IF (CMAKE_SIZEOF_VOID_P MATCHES 8)
        if (CMAKE_BUILD_TYPE MATCHES DEBUG)
            SET(GLDBIO_LIB_DIR ${GLDBIO_SOURCE_DIR}/../../Lib/debug_linux_x64)
            SET(LIBRARY_OUTPUT_PATH ${GLDBIO_SOURCE_DIR}/../../Lib/debug_linux_x64)
            SET(GLDBIO_LIBS_PLATFORM
                libpthread.so
                libmysqlclient.so.18
                libodbc.so.1
            )
            MESSAGE("GLDBIO is VERSION: debug_linux_x64")
			
        ELSEIF (CMAKE_BUILD_TYPE MATCHES RELEASE)
            SET(GLDBIO_LIB_DIR
                ${GLDBIO_SOURCE_DIR}/../../Lib/release_linux_x64
                ${GLDBIO_SOURCE_DIR}/../../Bin/linux_x64
            )
            SET(LIBRARY_OUTPUT_PATH ${GLDBIO_SOURCE_DIR}/../../Bin/linux_x64)
            SET(GLDBIO_LIBS_PLATFORM
                libpthread.so
                libmysqlclient.so.18
                libodbc.so.1
            )
            MESSAGE("GLDBIO is VERSION: release_linux_x64")

        ENDIF (CMAKE_BUILD_TYPE MATCHES DEBUG)
    ELSEIF (CMAKE_SIZEOF_VOID_P MATCHES 4)
        if (CMAKE_BUILD_TYPE MATCHES DEBUG)
            SET(GLDBIO_LIB_DIR ${GLDBIO_SOURCE_DIR}/../../Lib/debug_linux_x86)
            SET(LIBRARY_OUTPUT_PATH ${GLDBIO_SOURCE_DIR}/../../Lib/debug_linux_x86)
            SET(GLDBIO_LIBS_PLATFORM
                libpthread.so
            )
            MESSAGE("GLDBIO is VERSION: debug_linux_x86")

        ELSEIF (CMAKE_BUILD_TYPE MATCHES RELEASE)
            SET(GLDBIO_LIB_DIR
                ${GLDBIO_SOURCE_DIR}/../../Lib/release_linux_x86
                ${GLDBIO_SOURCE_DIR}/../../Bin/linux_x86
            )
            SET(LIBRARY_OUTPUT_PATH ${GLDBIO_SOURCE_DIR}/../../Bin/linux_x86)
            SET(GLDBIO_LIBS_PLATFORM
                libpthread.so
            )
            MESSAGE("GLDBIO is VERSION: release_linux_x86")

        ENDIF (CMAKE_BUILD_TYPE MATCHES DEBUG)
    ENDIF (CMAKE_SIZEOF_VOID_P MATCHES 8)
#ENDIF (WIN32)

SET(GLDBIO_SRCS
    src/GLDBIO.cpp
    src/MySqlConnectionPool.cpp
    src/OracleConnectionPool.cpp
    src/MSSqlConnectionPool.cpp
)

SET(GLDBIO_HDRS

)

ADD_DEFINITIONS(-DGLDBIO_LIBRARY)

INCLUDE_DIRECTORIES(
    ${GLDBIO_SOURCE_DIR}/../../Inc/GreenLeaf/ThirdParty
    ${GLDBIO_SOURCE_DIR}/../../Inc/GreenLeaf/ThirdParty/odbc
    ${GLDBIO_SOURCE_DIR}/../../Inc
)

LINK_DIRECTORIES(${GLDBIO_LIB_DIR})

ADD_LIBRARY(GLDBIO SHARED ${GLDBIO_SRCS} ${GLDBIO_HDRS})
TARGET_LINK_LIBRARIES(GLDBIO ${GLDBIO_LIBS_PLATFORM})
ADD_DEPENDENCIES(GLDBIO GLUtils)

MESSAGE(STATUS "GLDBIO is BINARY dir:" ${GLDBIO_BINARY_DIR})
MESSAGE(STATUS "GLDBIO is SOURCE dir:" ${GLDBIO_SOURCE_DIR})
