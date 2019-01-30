# Add all the source files for the client
set(SOURCES
    src/main.cpp
    src/Client.cpp)
set(INCLUDES
    include/Client.h)

# Find the appropriate version of SFML
# If the package can't be found, terminate the script
find_package(SFML 2.5 COMPONENTS system graphics window audio network REQUIRED)

# Add the include directory
include_directories(include)
include_directories(../../protocol/include)

# Add an executable to the project
add_executable(${PROJECT_NAME}Client
               ${SOURCES}
               ${INCLUDES})

# Link the appropriate libraries
# SFML
target_link_libraries(${PROJECT_NAME}Client
                      sfml-system
                      sfml-graphics
                      sfml-window
                      sfml-audio
                      sfml-network)

# AjaxCatalystProtocol
target_link_libraries(${EXECUTABLE_NAME}
                      AjaxCatalystProtocol)

if(UNIX)
	target_link_libraries(${PROJECT_NAME}Client pthread)
endif(UNIX)