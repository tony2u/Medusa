# Install script for directory: C:/Work/Engine/External/mysql-connector-c

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

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Readme" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/." TYPE FILE OPTIONAL FILES
    "C:/Work/Engine/External/mysql-connector-c/COPYING"
    "C:/Work/Engine/External/mysql-connector-c/LICENSE.mysql"
    )
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Readme" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/." TYPE FILE FILES "C:/Work/Engine/External/mysql-connector-c/README")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Documentation" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/docs" TYPE FILE FILES
    "C:/Work/Engine/External/mysql-connector-c/Docs/INFO_SRC"
    "C:/Work/Engine/External/mysql-connector-c/Docs/INFO_BIN"
    "C:/Work/Engine/External/mysql-connector-c/Docs/ChangeLog"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/Work/Engine/External/mysql-connector-c/zlib/cmake_install.cmake")
  include("C:/Work/Engine/External/mysql-connector-c/extra/yassl/cmake_install.cmake")
  include("C:/Work/Engine/External/mysql-connector-c/extra/yassl/taocrypt/cmake_install.cmake")
  include("C:/Work/Engine/External/mysql-connector-c/include/cmake_install.cmake")
  include("C:/Work/Engine/External/mysql-connector-c/dbug/cmake_install.cmake")
  include("C:/Work/Engine/External/mysql-connector-c/strings/cmake_install.cmake")
  include("C:/Work/Engine/External/mysql-connector-c/vio/cmake_install.cmake")
  include("C:/Work/Engine/External/mysql-connector-c/regex/cmake_install.cmake")
  include("C:/Work/Engine/External/mysql-connector-c/mysys/cmake_install.cmake")
  include("C:/Work/Engine/External/mysql-connector-c/mysys_ssl/cmake_install.cmake")
  include("C:/Work/Engine/External/mysql-connector-c/libmysql/cmake_install.cmake")
  include("C:/Work/Engine/External/mysql-connector-c/extra/cmake_install.cmake")
  include("C:/Work/Engine/External/mysql-connector-c/scripts/cmake_install.cmake")
  include("C:/Work/Engine/External/mysql-connector-c/tests/cmake_install.cmake")
  include("C:/Work/Engine/External/mysql-connector-c/support-files/cmake_install.cmake")
  include("C:/Work/Engine/External/mysql-connector-c/packaging/WiX/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "C:/Work/Engine/External/mysql-connector-c/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
