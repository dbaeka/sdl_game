# The places to look in
set(FIND_GAME_MATH_PATHS ~/Projects/cpp-libraries/game-math)

# The location of the include folder (and thus the header files)
# find_path uses the paths we defined above as places to look
# Saves the location of the header files in a variable
find_path(GAME_MATH_INCLUDE_DIR Random.h GameMath.h  # The variable to store the path in and the name of the header files
        PATH_SUFFIXES include               # The folder name containing the header files
        PATHS ${FIND_GAME_MATH_PATHS})       # Where to look (defined above)

# The location of the lib folder (and thus the .a file)
# find_library uses the paths we defined above as places to look
# Saves the location of the .a file in a variable
find_library(GAME_MATH_LIBRARY               # The variable to store where it found the .a files
        NAMES game_math                      # The name of the .a file (without the extension and without the 'lib')
        PATH_SUFFIXES lib                   # The folder the .a file is in
        PATHS ${FIND_GAME_MATH_PATHS})               # Where to look (defined above)

set(GAME_MATH_LIBRARIES ${GAME_MATH_LIBRARY})
set(GAME_MATH_INCLUDE_DIRS ${GAME_MATH_INCLUDE_DIR})