# Create lists of all the source files used by this section of the project
set(SOURCES
	src/main.cpp
	src/GameplayServer.cpp
	src/Connection.cpp)
set(INCLUDES
	include/GameplayServer.h
	include/Connection.h)

# Find SFML
find_package(SFML 2.5 COMPONENTS system network REQUIRED)

include_directories(include)

add_executable(${PROJECT_NAME}GameplayServer
               ${SOURCES}
               ${INCLUDES})

target_link_libraries(${PROJECT_NAME}GameplayServer
                      sfml-system
                      sfml-network)

if(UNIX)
	target_link_libraries(${PROJECT_NAME}GameplayServer pthread)
endif(UNIX)