add_executable( grab grab.cpp)
target_link_libraries( grab PRIVATE pylon::pylon )
target_link_libraries( grab PRIVATE ${OpenCV_LIBS} )
install( TARGETS grab )