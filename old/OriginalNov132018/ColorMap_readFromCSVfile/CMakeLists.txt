project( ColorMap )
cmake_minimum_required(VERSION 2.8)
cmake_policy(SET CMP0053 OLD)

# Load the Sedeen dependencies
find_package(SEDEENSDK REQUIRED
             HINTS ../../..
                   "D:/Sedeen Viewer SDK/v5.3.1.30/msvc2017"
                   "$ENV{PROGRAMFILES}/Sedeen Viewer SDK/v5.3.1.30/msvc2017" )


include_directories(${SEDEENSDK_INCLUDE_DIR}
                    ${SEDEENSDK_OPENCV_INCLUDE_DIR})

link_directories(${SEDEENSDK_LIBRARY_DIR}
                 ${SEDEENSDK_OPENCV_LIBRARY_DIR})

# Enable C++17 features
set(CMAKE_CXX_STANDARD 17)

# Build the plugin as a library
add_library(ColorMap MODULE ColorMapBuilder.cpp ColorMapBuilder.h MeshGridBuilder.cpp MeshGridBuilder.h)

# Link the library against the Sedeen libraries
# NOTE: The QT libraries must be linked first.
target_link_libraries(ColorMap ${SEDEENSDK_LIBRARIES}
                                     ${SEDEENSDK_OPENCV_LIBRARIES})

# Install the plugin in the sedeen plugins directory
if(${PATHCORE_FOUND})
  install(TARGETS ColorMap
          LIBRARY DESTINATION "${PATHCORE_DIR}/plugins")
endif()
