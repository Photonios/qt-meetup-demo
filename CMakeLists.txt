cmake_minimum_required(VERSION 3.5)

project(image-converter)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS 
    Core
    Gui
    Quick
    Qml
	Widgets
)

find_package(
	PkgConfig
)

pkg_search_module(CURL REQUIRED libcurl)
pkg_search_module(IMAGEMAGICK REQUIRED ImageMagick)
pkg_search_module(IMAGEMAGICKPP REQUIRED ImageMagick++) 

link_directories(
    /usr/lib/x86_64-linux-gnu/
)

add_executable(image-converter
    main.cpp
	mainwindow.h
	mainwindow.cpp
)

target_link_libraries(image-converter
	PRIVATE
		Qt5::Core
      	Qt5::Gui
      	Qt5::Qml
     	Qt5::Quick
		Qt5::Widgets
		${CURL_LIBRARIES}
		${IMAGEMAGICK_LIBRARIES}
		${IMAGEMAGICKPP_LIBRARIES}
)

target_include_directories(image-converter
	PRIVATE
		${CURL_INCLUDE_DIRS}
		${IMAGEMAGICK_INCLUDE_DIRS}
		${IMAGEMAGICKPP_INCLUDE_DIRS}
)

target_compile_options(image-converter
	PRIVATE
		${CURL_CFLAGS_OTHER}
		${IMAGEMAGICK_CLAG_OTHER}
		${IMAGEMAGICKPP_CLAG_OTHER}
)

file(COPY "main.qml" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

