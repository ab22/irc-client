project (client)

set (APP_VERSION_MAX 1)
set (APP_VERSION_MIN 0)
set (APP_VERSION_PATCH 22)

# To include the pthread lib.
find_package (Threads REQUIRED)

# Include boost libraries.
find_package(
	Boost 1.63.0
	COMPONENTS system date_time regex wserialization serialization thread
	REQUIRED
)

include_directories(${Boost_INCLUDE_DIR})
file (GLOB SOURCES "./*.cpp")
add_executable(client ${SOURCES})
target_link_libraries(client ${Boost_LIBRARIES})

install (TARGETS client DESTINATION bin)
