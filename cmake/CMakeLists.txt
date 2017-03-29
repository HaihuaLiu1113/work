PROJECT(DOGEN)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
AUX_SOURCE_DIRECTORY(../code RoomServer_srcs)


#set(CMAKE_INCLUDE_PATH "/usr/local/include")
#SET(EXECUTABLE_OUTPUT_PATH "/home/admin/work/debug")#设置编译路径
INCLUDE_DIRECTORIES(
	
	/usr/local/include 
	../iegad_framework/libiegad/iegad/
	../pugixml/src/
	
)

FIND_LIBRARY(RUNTIME_LIB rt /usr/lib  /usr/local/lib /usr/lib64 NO_DEFAULT_PATH)
link_libraries( ${RUNTIME_LIB})

include_directories(${PROJECT_SOURCE_DIR}../pugixml)
#LINK_DIRECTORIES(/usr/local/lib )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
ADD_EXECUTABLE(RoomServer ${RoomServer_srcs})
TARGET_LINK_LIBRARIES(RoomServer boost_thread boost_system boost_signals pthread pugixml glog uuid mysqlcppconn )



