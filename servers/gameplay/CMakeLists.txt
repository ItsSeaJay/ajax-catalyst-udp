# Set the name of the executable for use later on
set(EXECUTABLE_NAME
	${PROJECT_NAME}GameplayServer) # Should be `AjaxCatalystGameplayServer`

# Create lists of all the source files used by this section of the project
set(SOURCES
	src/main.cpp
	src/GameplayServer.cpp
	src/Connection.cpp)
set(INCLUDES
	include/GameplayServer.h
	include/Connection.h)

# Find SFML
find_package(SFML 2.5 COMPONENTS system graphics window network REQUIRED)

# Add the include directories for this executable
include_directories(include)
include_directories(${PROJECT_SOURCE_DIR}/protocol/include)

# Compile the sources and
add_executable(${EXECUTABLE_NAME}
               ${SOURCES}
               ${INCLUDES})

# Link the necessary libraries to the above executable file
# SFML
target_link_libraries(${EXECUTABLE_NAME}
                      sfml-system
                      sfml-graphics
                      sfml-window
                      sfml-network)

# AjaxCatalystProtocol
target_link_libraries(${EXECUTABLE_NAME}
                      AjaxCatalystProtocol)

# Also remember to link the pthread dependancy on Unix systems for concurrency
if(UNIX)
	target_link_libraries(${EXECUTABLE_NAME} pthread)
endif(UNIX)