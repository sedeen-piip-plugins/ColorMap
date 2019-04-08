PROJECT( ColorMap )
CMAKE_MINIMUM_REQUIRED( VERSION 3.8 )
# Enable C++17 features
SET(CMAKE_CXX_STANDARD 17)

# Define project description variables
SET( DISPLAY_NAME_TEXT "ColorMap 5.4.1.20190327" CACHE STRING "Name of the plugin as it should be displayed in Sedeen Viewer")
SET( SUPPORT_URL_TEXT "http://pathcore.com/support/plugin/info/${PROJECT_NAME}" CACHE STRING "Location users can find help with the plugin" )
SET( DEVELOPER_TEXT "Sunnybrook Research Institute" CACHE STRING "Name of the author or organization that created the plugin" )

# Load the Sedeen dependencies
SET(PROGRAMFILESX86 "PROGRAMFILES\(X86\)")
FIND_PACKAGE( SEDEENSDK REQUIRED 
                HINTS ../../.. 
                  "$ENV{${PROGRAMFILESX86}}/Sedeen Viewer SDK/v5.4.1.20190327/msvc2017"
                  "$ENV{PROGRAMFILES}/Sedeen Viewer SDK/v5.4.1.20190327/msvc2017" )

# Load the included OpenCV libs
FIND_PACKAGE(SEDEENSDK_OPENCV REQUIRED
             HINTS ../../..
                  "$ENV{${PROGRAMFILESX86}}/Sedeen Viewer SDK/v5.4.1.20190327/msvc2017"
                  "$ENV{PROGRAMFILES}/Sedeen Viewer SDK/v5.4.1.20190327/msvc2017" )

INCLUDE_DIRECTORIES(${INCLUDE_DIRECTORIES} ${SEDEENSDK_INCLUDE_DIR}
                    ${SEDEENSDK_OPENCV_INCLUDE_DIR})

LINK_DIRECTORIES(${LINK_DIRECTORIES} ${SEDEENSDK_LIBRARY_DIR}
                 ${SEDEENSDK_OPENCV_LIBRARY_DIR})

# Build the plugin as a library
ADD_LIBRARY( ${PROJECT_NAME} MODULE ColorMap.h ColorMap.cpp MeshGridBuilder.h MeshGridBuilder.cpp )

# Link the library against the Sedeen libraries
# NOTE: The QT libraries must be linked first.
TARGET_LINK_LIBRARIES( ${PROJECT_NAME} ${SEDEENSDK_LIBRARIES}
                               ${SEDEENSDK_OPENCV_LIBRARIES})

#Create or update the .info file in the build directory
STRING( TIMESTAMP DATE_CREATED_TEXT "%Y-%m-%d" )
CONFIGURE_FILE( "infoTemplate.info.in" "${PROJECT_NAME}.info" )

# Set the install destination directory
IF( NOT PLUGIN_DESTINATION_DIR )
  IF( ${SEDEEN_FOUND} )
	SET( TEMPPLUGINDIR "${PATHCORE_DIR}/plugins/cpp/piip/${PROJECT_NAME}" )
  ELSE()
	SET( TEMPPLUGINDIR "PLUGIN_DESTINATION_DIR-NOTFOUND" )
	MESSAGE( SEND_ERROR "PLUGIN_DESTINATION_DIR not found. Set this to the target installation directory of the plugin within Sedeen Viewer (e.g. $ENV{PROGRAMFILES}/Sedeen Viewer/plugins/cpp/piip/${PROJECT_NAME}).")
  ENDIF()
  SET(PLUGIN_DESTINATION_DIR ${TEMPPLUGINDIR} CACHE PATH "Installation directory for the plugin within Sedeen Viewer")
ENDIF()

# Install the plugin in the sedeen plugins directory
IF(${SEDEEN_FOUND})
  INSTALL(TARGETS ${PROJECT_NAME}
          LIBRARY DESTINATION "${PLUGIN_DESTINATION_DIR}")
  INSTALL(FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.info"
          DESTINATION "${PLUGIN_DESTINATION_DIR}")
ENDIF()
