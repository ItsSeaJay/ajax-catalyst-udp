# Add all the source files for the client
set(SOURCES
    src/main.cpp)

# Find the appropriate version of SFML
# If the package can't be found, terminate the script
find_package(SFML 2.5 COMPONENTS network REQUIRED)

# Add an executable to the project
add_executable(${PROJECT_NAME}Client
               ${SOURCES})

# Link the appropriate libraries
target_link_libraries(${PROJECT_NAME}Client sfml-network)

if(UNIX)
	target_link_libraries(${PROJECT_NAME}Client pthread)
endif(UNIX)