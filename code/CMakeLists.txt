cmake_minimum_required(VERSION 2.8)
project( AR_ENSG )
set(CMAKE_CXX_FLAGS "-std=c++11")

find_package(OpenCV REQUIRED)
find_package(OpenGL REQUIRED)

add_subdirectory (external)

include_directories(
	/usr/local/include/apriltag/
	external/glfw-3.1.2/include/GLFW/
	external/glfw-3.1.2/include/
	external/glm-0.9.7.1/
	external/glew-1.13.0/include/
	external/assimp-3.0.1270/include/
	opencv_code/
	opengl_code/
	.
)

set(ALL_LIBS
	${OpenCV_LIBS}
	${OPENGL_LIBRARY}
	glfw
	GLEW_1130
	assimp
	apriltag
	SOIL
)

add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)

add_executable(main main.cpp 
		opengl_code/Shader.cpp 
		opengl_code/shaders/default.vertexshader 
		opengl_code/shaders/default.fragmentshader
		opencv_code/AprilTagReader.cpp
		)
target_link_libraries( main ${ALL_LIBS} )

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/opencv_code/")
add_executable(mainCV opencv_code/mainCV.cpp )
target_link_libraries(mainCV ${OpenCV_LIBS} apriltag)

add_executable(testClass opencv_code/AprilTagReaderTest.cpp opencv_code/AprilTagReader.cpp )
target_link_libraries( testClass ${OpenCV_LIBS} apriltag)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/opencv_code/calib/")
add_executable(calibration opencv_code/calib/camera_calibration.cpp )
target_link_libraries(calibration ${OpenCV_LIBS})




