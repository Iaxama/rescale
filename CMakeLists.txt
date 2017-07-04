cmake_minimum_required(VERSION 3.7)
project(rescale)

set(CMAKE_CXX_STANDARD 11)

find_package(YARP REQUIRED)
find_package(ICUBcontrib)

list(APPEND CMAKE_MODULE_PATH ${YARP_MODULE_PATH})
include(YarpInstallationHelpers)

include_directories(include
                    ${YARP_INCLUDE_DIRS}
        #            ${OpenCV_INCLUDE_DIRS}
        )

set(SOURCE_FILES main.cpp)
set(HEADER_FILES include/*)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME}
        ${YARP_LIBRARIES}
        #${OpenCV_LIBRARIES}
        )

install(TARGETS ${MODULENAME} DESTINATION bin)
yarp_install(FILES app_${PROJECT_NAME}.xml DESTINATION ${ICUBCONTRIB_APPLICATIONS_INSTALL_DIR})
