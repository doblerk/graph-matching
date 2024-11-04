cmake_minimum_required(VERSION 3.10)

# Project name
project(graph-matching VERSION 1.0 
                DESCRIPTION "TO DEFINE"
                LANGUAGES CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find Boost libraries
set(BOOST_ROOT "${PROJECT_SOURCE_DIR}/third_party/boost")
set(BOOST_INCLUDEDIR "${PROJECT_SOURCE_DIR}/third_party/boost")
set(BOOST_LIBRARYDIR "${PROJECT_SOURCE_DIR}/third_party/boost/stage/lib")

find_library(BOOST_REGEX_LIB boost_regex HINTS ${BOOST_LIBRARYDIR})
find_library(BOOST_GRAPH_LIB boost_graph HINTS ${BOOST_LIBRARYDIR})

if (NOT BOOST_REGEX_LIB OR NOT BOOST_GRAPH_LIB)
    message(FATAL_ERROR "Required Boost libraries not found in ${BOOST_LIBRARYDIR}")
endif()

# Find OR-tool libraries
set(OR_TOOLS_ROOT "${PROJECT_SOURCE_DIR}/third_party/or-tools")
set(OR_TOOLS_INCLUDEDIR "${PROJECT_SOURCE_DIR}/third_party/or-tools/include")
set(OR_TOOLS_LIBRARYDIR "${PROJECT_SOURCE_DIR}/third_party/or-tools/lib")

find_library(OR_TOOLS_LIB ortools PATHS ${OR_TOOLS_LIBRARYDIR} NO_DEFAULT_PATH)

if (NOT OR_TOOLS_LIB)
    message(FATAL_ERROR "OR-Tools library not found in ${OR_TOOLS_LIBRARYDIR}")
endif()

# Find cnpy libraries
set(CNPY_ROOT "${PROJECT_SOURCE_DIR}/third_party/cnpy")

add_subdirectory(${CNPY_ROOT})
# add_library(cnpy STATIC ${CNPY_ROOT}/cnpy.cpp)
# target_include_directories(cnpy PUBLIC ${CNPY_INCLUDEDIR})

# find_library(CNPY_LIB cnpy PATHS ${CNPY_LIBRARYDIR} NO_DEFAULT_PATH)

# if (NOT CNPY_LIB)
#     message(FATAL_ERROR "CNPY library not found in ${CNPY_LIBRARYDIR}")
# endif()

# Find hdf5 libraries
set(HDF5_ROOT "${PROJECT_SOURCE_DIR}/third_party/hdf5")
set(HDF5_INCLUDEDIR "${PROJECT_SOURCE_DIR}/third_party/hdf5/include")
set(HDF5_LIBRARYDIR "${PROJECT_SOURCE_DIR}/third_party/hdf5/lib")

find_library(HDF5_LIB hdf5 PATHS ${HDF5_LIBRARYDIR} NO_DEFAULT_PATH)
find_library(HDF5_CPP_LIB hdf5_cpp PATHS ${HDF5_LIBRARYDIR} NO_DEFAULT_PATH)

if (NOT HDF5_LIB OR NOT HDF5_CPP_LIB)
    message(FATAL_ERROR "HDF5 libraries not found in ${HDF5_LIBRARYDIR}")
endif()

# Find OpenMP library
find_package(OpenMP REQUIRED)

# Find Google-Test library
add_subdirectory("third_party/googletest")
include_directories("third_party/googletest/googletest/include")
add_executable(node_assignment_test "tests/node_assignment_test.cpp")
target_include_directories(node_assignment_test PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(node_assignment_test gtest gtest_main pthread linear_assignment)

# Add the source files
set(SOURCES
	src/main.cpp
	src/edit_cost/EditCost.cpp
	src/linear_assignment/NodeAssignment.cpp
	src/graph_loader/GraphLoader.cpp
)

# Add the header files
set(HEADERS
	include/edit_cost/EditCost.h
	include/linear_assignment/NodeAssignment.h
	include/graph_loader/GraphLoader.h
)

# Add directories
include_directories(${PROJECT_SOURCE_DIR}/include ${BOOST_INCLUDEDIR} ${OR_TOOLS_INCLUDEDIR} ${CNPY_ROOT} ${HDF5_INCLUDEDIR})

# Create the executable
add_executable(graph-matching ${SOURCES} ${HEADERS})

target_link_libraries(graph-matching 
	PRIVATE
	${BOOST_LIB}
	${BOOST_REGEX_LIB}
    ${BOOST_GRAPH_LIB}
	${OR_TOOLS_LIB}
	cnpy
	${HDF5_LIB}
	${HDF5_CPP_LIB}
)

# Create an object library for each source file
add_library(edit_cost STATIC ${PROJECT_SOURCE_DIR}/src/edit_cost/EditCost.cpp ${PROJECT_SOURCE_DIR}/include/edit_cost/EditCost.h)
target_include_directories(edit_cost PUBLIC ${BOOST_INCLUDEDIR})
target_link_libraries(edit_cost PUBLIC ${BOOST_LIB})

add_library(graph_loader STATIC ${PROJECT_SOURCE_DIR}/src/graph_loader/GraphLoader.cpp ${PROJECT_SOURCE_DIR}/include/graph_loader/GraphLoader.h)
target_include_directories(graph_loader PUBLIC ${BOOST_INCLUDEDIR})
target_link_libraries(graph_loader PUBLIC ${BOOST_LIB})

add_library(linear_assignment STATIC ${PROJECT_SOURCE_DIR}/src/linear_assignment/NodeAssignment.cpp ${PROJECT_SOURCE_DIR}/include/linear_assignment/NodeAssignment.h)
target_include_directories(linear_assignment PUBLIC ${OR_TOOLS_INCLUDEDIR}, ${EIGEN_INCLUDEDIR})
target_link_libraries(linear_assignment PUBLIC ${BOOST_LIB} ${OR_TOOLS_LIB})

if(OpenMP_CXX_FOUND)
    target_link_libraries(graph-matching PRIVATE OpenMP::OpenMP_CXX)
    target_link_libraries(edit_cost PRIVATE OpenMP::OpenMP_CXX)
    target_link_libraries(graph_loader PRIVATE OpenMP::OpenMP_CXX)
    target_link_libraries(linear_assignment PRIVATE OpenMP::OpenMP_CXX)
endif()