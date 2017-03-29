PROJECT(DOGEN)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
AUX_SOURCE_DIRECTORY(. RoomServer_srcs)
#ADD_EXECUTABLE(test_ie ${RoomServer_srcs})

#include(CheckCXXCompilerFlag)

#set(CMAKE_INCLUDE_PATH "/usr/local/include")
#SET(EXECUTABLE_OUTPUT_PATH "/home/admin/work/debug")#设置编译路径
INCLUDE_DIRECTORIES(
	../iegad_framework/libiegad/iegad/
	../pugixml/src/
	/usr/local/include 
	
)

include_directories(${PROJECT_SOURCE_DIR}../pugixml)
#LINK_DIRECTORIES(/usr/local/lib 
#		/usr/lib64
#		)
FIND_LIBRARY(RUNTIME_LIB rt /usr/lib  /usr/local/lib /usr/lib64 NO_DEFAULT_PATH)
link_libraries( ${RUNTIME_LIB})

include(CheckCXXCompilerFlag)
#CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
#CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
#if(COMPILER_SUPPORTS_CXX11)
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#elseif(COMPILER_SUPPORTS_CXX0X)
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
#else()
#        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
#endif()
#add_compile_options(-std=c++11)
ADD_EXECUTABLE(test_ie ${RoomServer_srcs})
TARGET_LINK_LIBRARIES(test_ie boost_thread boost_system boost_signals pthread pugixml glog uuid)
#ADD_EXECUTABLE(test_ie ${RoomServer_srcs})
