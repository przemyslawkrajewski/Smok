cmake_minimum_required (VERSION 2.6)
project (Smok)

file(GLOB_RECURSE znalezioneZrodla "src/*.cpp")
file(GLOB_RECURSE znalezioneNaglowki "src/*.h")

set (katalowNaglowkow "")
foreach (naglowek ${znalezioneNaglowki})
    get_filename_component(_dir ${naglowek} PATH)
    list (APPEND katalowNaglowkow ${_dir})
endforeach()
list(REMOVE_DUPLICATES katalowNaglowkow)

include_directories(${katalowNaglowkow})
add_executable (Smok ${znalezioneZrodla})

INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(Smok ${SDL2_LIBRARIES})

file(COPY
    ${CMAKE_CURRENT_SOURCE_DIR}/Grafika
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)
