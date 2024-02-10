# cmake_minimum_required(VERSION  3.5 FATAL_ERROR)
# project(CourseWorkConstrPO LANGUAGES CXX)

# file(GLOB CPPS "*.cpp")
# include_directories("~/Desktop/git_projects/CourseWorkConstrPO/SFMLibrary/SFML-2.6.1/include/SFML" "~/Desktop/git_projects/CourseWorkConstrPO/SFML/src/Headers")

# set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc")
# # set(SFML_STATIC_LIBRARIES TRUE)

# add_executable(CourseWorkConstrPO.out ${CPPS})

# set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
# set(SFML_DIR "~/Desktop/git_projects/CourseWorkConstrPO/SFMLibrary/SFML-2.6.1/lib/cmake/SFML")

# find_package(SFML REQUIRED graphics network audio window system)
# target_link_libraries(CourseWorkConstrPO.out sfml-graphics sfml-window sfml-system)

cmake_minimum_required(VERSION 3.16)
project(CourseWorkConstrPO LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

file(GLOB CPPS "*.cpp")

# include_directories("~/Desktop/git_projects/CourseWorkConstrPO/SFML/src/Headers")
add_executable(CourseWorkConstrPO ${CPPS})

target_include_directories(
    ${CMAKE_PROJECT_NAME}
    PRIVATE
        Headers
)

target_link_libraries(CourseWorkConstrPO PRIVATE sfml-graphics sfml-window sfml-system) 
target_compile_features(CourseWorkConstrPO PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET CourseWorkConstrPO
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:CMakeSFMLProject>
        VERBATIM)
endif()

add_custom_target(
    copy_assets ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/../assets"
        "${CMAKE_BINARY_DIR}/bin/assets"
    COMMENT "Copy assets from ${PROJECT_SOURCE_DIR}/../assets to ${CMAKE_BINARY_DIR}/bin/assets"
)
add_dependencies(${CMAKE_PROJECT_NAME} copy_assets)

add_custom_target(
    copy_settings ALL
    COMMAND ${CMAKE_COMMAND} -E copy
        "${PROJECT_SOURCE_DIR}/../Settings.json"
        "${CMAKE_BINARY_DIR}/bin"
    COMMENT "Copy assets from ${PROJECT_SOURCE_DIR}/../Settings.json to ${CMAKE_BINARY_DIR}/bin"
)
add_dependencies(${CMAKE_PROJECT_NAME} copy_settings)

install(TARGETS CourseWorkConstrPO)
