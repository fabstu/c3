set (CMAKE_BUILD_TYPE Debug)
add_executable(cities cities.cpp)
add_custom_command(
    TARGET cities
    PRE_BUILD
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/../merge_std2.sh cities

    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Merging headers for cities"
)
add_executable(tetris tetris.cpp)
add_custom_command(
    TARGET tetris
    PRE_BUILD
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/../merge_std2.sh tetris

    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Merging headers for tetris"
)
add_executable(kingdoms kingdoms.cpp)
add_custom_command(
    TARGET kingdoms
    PRE_BUILD
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/../merge_std2.sh kingdoms

    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Merging headers for kingdoms"
)
add_executable(foodstall foodstall.cpp)
add_custom_command(
    TARGET foodstall
    PRE_BUILD
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/../merge_std2.sh foodstall

    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Merging headers for foodstall"
)
add_executable(mmcmsf mmcmsf.cpp)
add_custom_command(
    TARGET mmcmsf
    PRE_BUILD
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/../merge_std2.sh mmcmsf std_flow.h

    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Merging headers for mmcmsf"
)
