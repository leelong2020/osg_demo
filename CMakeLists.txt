cmake_minimum_required( VERSION 3.10 )
if(NOT CMAKE_MAXIMUM_RECURSION_DEPTH)
  set(CMAKE_MAXIMUM_RECURSION_DEPTH 2000)
endif()

SET(PROJECT_NAME OSG_Demo)
project( ${PROJECT_NAME} )

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)


# Default debug suffix for libraries.
set( CMAKE_DEBUG_POSTFIX "d" )

include_directories("${OSG_ROOT}/include") 
link_directories("${OSG_ROOT}/lib")

ADD_SUBDIRECTORY(src)
AUX_SOURCE_DIRECTORY(src SOURCES)

ADD_EXECUTABLE(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME}
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME}
	Qt5::Widgets
    osgd
    osgViewerd
    osgGAd
    osgDBd
)
