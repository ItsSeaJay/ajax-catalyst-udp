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
find_package(SFML 2.5 COMPONENTS system graphics network REQUIRED)

include_directories(include)

add_executable(${EXECUTABLE_NAME}
               ${SOURCES}
               ${INCLUDES})

# Link SFML to the above executable
target_link_libraries(${EXECUTABLE_NAME}
                      sfml-system
                      sfml-graphics
                      sfml-network)

# Also remember to link the pthread dependancy on Unix systems for concurrency
if(UNIX)
	target_link_libraries(${EXECUTABLE_NAME} pthread)
endif(UNIX)