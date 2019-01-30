# Create lists of all the source files used by this section of the project
set(INCLUDES
	include/Log.h
	include/Packet.h
	include/Protocol.h)
set(SOURCES
    src/Log.cpp
    src/Packet.cpp)

# Add the include directories
include_directories(include)

# Compile the sources and includes as a library
add_library(${PROJECT_NAME}Protocol
	${SOURCES}
	${INCLUDES})
