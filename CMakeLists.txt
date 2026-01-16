cmake_minimum_required(VERSION 3.27)
project(BIFANG)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_BUILD_TYPE "Debug")
#SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
#SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

include_directories(runtime/antlr4-runtime)
include_directories(runtime/magic_enum/include)
include_directories(BIFANGLexer BIFANGParser)



file(GLOB_RECURSE SRC CONFIGURE_DEPENDS src/*.cpp src/*.c)
file(GLOB_RECURSE INCLUDE CONFIGURE_DEPENDS
        include/*.hpp include/Backend/*.hpp include/Pass/*.hpp
        include/*.h  include/Backend/*.h include/Pass/*.h)
file(GLOB_RECURSE ANTLR4_RUNTIME runtime/antlr4-runtime/*.cpp)
file(GLOB_RECURSE BIFANGLexer BIFANGLexer/*.cpp)
file(GLOB_RECURSE BIFANGParser BIFANGParser/*.cpp)

add_executable(${PROJECT_NAME} ${SRC} ${ANTLR4_RUNTIME} ${BIFANGLexer} ${BIFANGParser}
        )
target_include_directories(${PROJECT_NAME} PUBLIC include)
