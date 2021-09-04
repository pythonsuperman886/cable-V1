cmake_minimum_required(VERSION 3.14 )
project(cable_V1)
set(CMAKE_CXX_STANDARD 17)


set (app_icon icon.rc)
#set_property(SOURCE icon.rc APPEND PROPERTY
#        OBJECT_DEPENDS /home/explore/Downloads/c1.ico)
#set(OpenCV_DIR /home/explore/envs/opencv/build)
#set(CMAKE_PREFIX_PATH  /home/explore/envs/opencv_install/share)

set(CMAKE_PREFIX_PATH  /home/explore/envs/Qt/5.9.8/gcc_64/lib/cmake)
set(Torch_DIR /home/explore/envs/libtorch/share/cmake/Torch)
set(OpenCV_DIR /home/explore/envs/opencv_install2/share/OpenCV)

set(CMAKE_INCLUDE_CURRENT_DIR  ON)

find_package(PythonInterp REQUIRED)
find_package(Torch REQUIRED)
find_package( OpenCV REQUIRED )

FIND_PACKAGE(Qt5Widgets REQUIRED)
FIND_PACKAGE(Qt5Gui REQUIRED)
FIND_PACKAGE(Qt5Core REQUIRED)
FIND_PACKAGE(Qt5Sql REQUIRED)
FIND_PACKAGE(Qt5Network REQUIRED)
FIND_PACKAGE(Qt5Concurrent REQUIRED)
FIND_PACKAGE(Qt5Charts REQUIRED)

find_package(OpenMP REQUIRED)


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
#include_directories(/home/explore/project/mycpp/cable_defect_detect_qt/image_io/include)
#include_directories(/home/explore/project/mycpp/cable_defect_detect_qt/extern/stb_image)
#include_directories(/home/explore/project/mycpp/cable_defect_detect_qt/extern/stb_image_resize)
#include_directories(/home/explore/project/mycpp/cable_defect_detect_qt/extern/stb_image_write)

include_directories( ${OpenCV_INCLUDE_DIRS} )
include_directories( ${Qt_INCLUDE_DIRS} )
include_directories( ${Torch_INCLUDE_DIRS} )
include_directories(${Qt5Widgets_INCLUDE_DIRS})
include_directories(/home/explore/envs/anaconda3/envs/mypytorch/include/python3.6m)
include_directories(/home/explore/envs/MVS-2.1.0_x86_64_20201228/MVS/include/)
link_directories(/home/explore/envs/MVS-2.1.0_x86_64_20201228/MVS/lib/64)
#link_directories(/home/explore/envs/anaconda3/envs/mypytorch/lib)

aux_source_directory(. DIR_SRCS)
add_executable(main ${DIR_SRCS} )
#add_executable(main main.cpp)
#target_link_libraries(main python3.6m pthread )
target_link_libraries(main boost_filesystem "${Boost_LIBRARIES}" "${TORCH_LIBRARIES}" "${OpenCV_LIBS}" Qt5::Widgets Qt5::Charts "${QT_LIBS}" MvCameraControl  OpenMP::OpenMP_CXX  )
set_property(TARGET main PROPERTY CXX_STANDARD 17)

message("${Torch_INCLUDE_DIRS}")
message("${TORCH_LIBRARIES}")