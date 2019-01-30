# Set the name of the executable for use later on
set(EXECUTABLE_NAME
    ${PROJECT_NAME}Client) # Should be `AjaxCatalystClient`

# Add all the source files for the client
set(SOURCES
    src/main.cpp
    src/Client.cpp)
set(INCLUDES
    include/Client.h)

# Find the appropriate version of SFML
# If the package can't be found, terminate the script
find_package(SFML 2.5 COMPONENTS system graphics window audio network REQUIRED)

# Add the include directories for this executable
include_directories(include)
include_directories(../../protocol/include)

# Add an executable to the project
add_executable(${EXECUTABLE_NAME}
               ${SOURCES}
               ${INCLUDES})

# Link the appropriate libraries
# SFML
target_link_libraries(${EXECUTABLE_NAME}
                      sfml-system
                      sfml-graphics
                      sfml-window
                      sfml-audio
                      sfml-network)

# AjaxCatalystProtocol
target_link_libraries(${EXECUTABLE_NAME}
                      AjaxCatalystProtocol)

# Also remember to link the pthread dependancy on Unix systems for concurrency
if(UNIX)
	target_link_libraries(${EXECUTABLE_NAME} pthread)
endif(UNIX)