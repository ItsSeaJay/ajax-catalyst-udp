# Create lists of all the source files used by this section of the project
set(SOURCES
    src/main.cpp)

# Find SFML
find_package(SFML 2.5 COMPONENTS network REQUIRED)

include_directories(include)

add_library(${PROJECT_NAME}Protocol ${SOURCES})

if(UNIX)
	target_link_libraries(${PROJECT_NAME}Protocol
	                      pthread)
endif(UNIX)
