add_executable( enumerate enumerate.cpp)
target_link_libraries( enumerate PRIVATE pylon::pylon )
target_link_libraries( enumerate PRIVATE ${OpenCV_LIBS} )
install( TARGETS enumerate )