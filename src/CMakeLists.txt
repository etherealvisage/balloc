add_definitions(-W -Wall -ansi -pedantic -Wextra -O3 -std=c89)

aux_source_directory(. sources)

add_executable(btest ${sources})
