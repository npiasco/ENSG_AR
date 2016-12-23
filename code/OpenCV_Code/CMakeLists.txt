cmake_minimum_required(VERSION 2.8)
project( DisplayImage )
find_package( OpenCV REQUIRED )

include_directories(
	/usr/local/include/apriltag/
)

set(ALL_LIBS
	${OpenCV_LIBS}
	apriltag
)

add_executable(main main.cpp )
target_link_libraries( main ${ALL_LIBS} )

add_executable(testClass AprilTagReaderTest.cpp AprilTagReader.cpp )
target_link_libraries( testClass ${ALL_LIBS} )

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/calib/")
add_executable(calibration calib/camera_calibration.cpp )
target_link_libraries(calibration ${OpenCV_LIBS})

