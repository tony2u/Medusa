# Install script for directory: C:/Work/Engine/External/mysql-connector-c/include

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/LibMySQL")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "C:/Work/Engine/External/mysql-connector-c/include/mysql.h"
    "C:/Work/Engine/External/mysql-connector-c/include/mysql_com.h"
    "C:/Work/Engine/External/mysql-connector-c/include/mysql_time.h"
    "C:/Work/Engine/External/mysql-connector-c/include/my_list.h"
    "C:/Work/Engine/External/mysql-connector-c/include/my_alloc.h"
    "C:/Work/Engine/External/mysql-connector-c/include/typelib.h"
    "C:/Work/Engine/External/mysql-connector-c/include/my_dbug.h"
    "C:/Work/Engine/External/mysql-connector-c/include/m_string.h"
    "C:/Work/Engine/External/mysql-connector-c/include/my_sys.h"
    "C:/Work/Engine/External/mysql-connector-c/include/my_xml.h"
    "C:/Work/Engine/External/mysql-connector-c/include/mysql_embed.h"
    "C:/Work/Engine/External/mysql-connector-c/include/my_pthread.h"
    "C:/Work/Engine/External/mysql-connector-c/include/decimal.h"
    "C:/Work/Engine/External/mysql-connector-c/include/errmsg.h"
    "C:/Work/Engine/External/mysql-connector-c/include/my_global.h"
    "C:/Work/Engine/External/mysql-connector-c/include/my_getopt.h"
    "C:/Work/Engine/External/mysql-connector-c/include/sslopt-longopts.h"
    "C:/Work/Engine/External/mysql-connector-c/include/my_dir.h"
    "C:/Work/Engine/External/mysql-connector-c/include/sslopt-vars.h"
    "C:/Work/Engine/External/mysql-connector-c/include/sslopt-case.h"
    "C:/Work/Engine/External/mysql-connector-c/include/sql_common.h"
    "C:/Work/Engine/External/mysql-connector-c/include/keycache.h"
    "C:/Work/Engine/External/mysql-connector-c/include/m_ctype.h"
    "C:/Work/Engine/External/mysql-connector-c/include/my_compiler.h"
    "C:/Work/Engine/External/mysql-connector-c/include/mysql_com_server.h"
    "C:/Work/Engine/External/mysql-connector-c/include/my_byteorder.h"
    "C:/Work/Engine/External/mysql-connector-c/include/byte_order_generic.h"
    "C:/Work/Engine/External/mysql-connector-c/include/byte_order_generic_x86.h"
    "C:/Work/Engine/External/mysql-connector-c/include/little_endian.h"
    "C:/Work/Engine/External/mysql-connector-c/include/big_endian.h"
    "C:/Work/Engine/External/mysql-connector-c/include/mysql_version.h"
    "C:/Work/Engine/External/mysql-connector-c/include/my_config.h"
    "C:/Work/Engine/External/mysql-connector-c/include/mysqld_ername.h"
    "C:/Work/Engine/External/mysql-connector-c/include/mysqld_error.h"
    "C:/Work/Engine/External/mysql-connector-c/include/sql_state.h"
    )
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mysql" TYPE DIRECTORY FILES "C:/Work/Engine/External/mysql-connector-c/include/mysql/" REGEX "/[^/]*\\.h$" REGEX "/psi\\_abi[^/]*$" EXCLUDE)
endif()

