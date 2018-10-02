cmake_minimum_required(VERSION 3.9.6)
## Project must go here #
project(ProtocolDeveloper LANGUAGES C VERSION 0.1 )

## Download, build testing Framework ##



##targets
enable_testing()

add_subdirectory(myApps)
add_subdirectory(myLibraries)
add_subdirectory(otherLibraries)
