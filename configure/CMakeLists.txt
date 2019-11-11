# Create configure variables and files
string(TIMESTAMP BUILDVERSION "%Y-%m-%d_%H;%M;%S")
set(RELEASE_TYPE "prealpha")
set(GAME_NAME "ZerothOrder")
set(ENGINE_NAME "Melodic")
set(LOG_FOLDER "logs")
set(LOG_EXTENSION ".txt")

if(CMAKE_BUILD_TYPE MATCHES Debug)
	set(ENABLE_VALIDATION_LAYERS "true")
ELSEIF(CMAKE_BUILD_TYPE MATCHES Release)
	set(ENABLE_VALIDATION_LAYERS "false")
ENDIF()

string(CONCAT WINDOW_NAME "(${CMAKE_BUILD_TYPE})" ${GAME_NAME} "_" ${RELEASE_TYPE} "_" ${PROJECT_VERSION})

# Move assets folder to build dir
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})

# Make log directory
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/${LOG_FOLDER})

configure_file(include/config.hpp.in ${CMAKE_CURRENT_SOURCE_DIR}/include/config.hpp)

add_library(configure INTERFACE)

target_include_directories(configure INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)