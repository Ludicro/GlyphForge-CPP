cmake_minimum_required(VERSION 3.10)
project(GlyphForge)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find packages
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
find_package(ImGui-SFML REQUIRED)

# Source files
set(SOURCES
    src/main.cpp
    src/gui/window.cpp
    src/writer.cpp
    src/bases.cpp
    src/line_shapes.cpp
)

# Header files
set(HEADERS
    include/gui/window.h
    include/writer.h
    include/bases.h
    include/line_shapes.h
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE include)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
    ImGui-SFML::ImGui-SFML
)

# Copy resources to build directory
file(COPY resources DESTINATION ${CMAKE_BINARY_DIR})
