cmake_minimum_required(VERSION 3.20.2)

project(paint3D_Final)

#=============== INCLUSION OF QT ===============
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH "F:/Qt5_build/qtbase")
find_package(OpenGL)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5OpenGl REQUIRED)
find_package(Qt5Xml REQUIRED)
find_package(Qt5Widgets REQUIRED)

#================ INCLUSION OF VTK ================
set(VTK_DIR $ENV{VTK_DIR})
SET(CMAKE_VERBOSE_MAKEFILE ON)
find_package(VTK REQUIRED)



#=============== INCLUSION OF PROJECT CODE ===============
set(FORMS_DIR "${CMAKE_SOURCE_DIR}/forms")
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")

include_directories(${FORMS_DIR})
include_directories(${INCLUDE_DIR})
include_directories(${SOURCE_DIR})

file(GLOB_RECURSE SOURCES
	"${FORMS_DIR}/*.ui"
	"${INCLUDE_DIR}/*.h"
	"${SOURCE_DIR}/*.cpp"
)



# Add the forms directory to the AUTOUIC search paths
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_AUTOUIC_SEARCH_PATHS} ${FORMS_DIR})

add_executable(paint3D_Final WIN32 ${SOURCES})

#==================== ADD THE TARGET INCLUDE ===================
target_include_directories(paint3D_Final PRIVATE ${FORMS_DIR})
target_include_directories(paint3D_Final PRIVATE ${INCLUDE_DIR})
target_include_directories(paint3D_Final PRIVATE ${SOURCE_DIR})

#===================== LINKING LIBRARIES =======================#
target_link_libraries( paint3D_Final Qt5::OpenGL)
target_link_libraries( paint3D_Final Qt5::Xml)
target_link_libraries( paint3D_Final Qt5::Widgets)
target_link_libraries( paint3D_Final ${QT_LIBRARIES} ${OPENGL_LIBRARIES})
target_link_libraries(paint3D_Final ${VTK_LIBRARIES})
# vtk_module_autoinit is needed
vtk_module_autoinit(
	TARGETS paint3D_Final
	MODULES ${VTK_LIBRARIES}
)








