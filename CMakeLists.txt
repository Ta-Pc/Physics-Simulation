cmake_minimum_required(VERSION 3.10)
project(Physics VERSION 1.0)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)

# Add the include directory to the include path
include_directories(${CMake_SOURCE_DIR}/include)

include_directories("C:/Users/makho/projects/C++/Downloaded/Resources/SFML-3.0.0/include")

# link_directories("C:/Users/makho/projects/C++/Downloaded/Resources/SFML-3.0.0/lib")
link_directories("C:/Users/makho/projects/C++/Downloaded/Resources/SFML-3.0.0/lib")

# set sfml cmake directory
set(SFML_DIR "C:/Users/makho/projects/C++/Downloaded/Resources/SFML-3.0.0/lib/cmake/SFML")

# Find OpenGL
find_package(OpenGL REQUIRED)

# Find SFML with correct component names for version 3.0.0
find_package(SFML 3 COMPONENTS 
    System 
    Window 
    Graphics 
    Audio 
    Network 
REQUIRED)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(Physics ${SOURCES})

# link sfml libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    sfml-system
    sfml-window
    sfml-graphics
    sfml-audio
    sfml-network
    OpenGL::GL
)