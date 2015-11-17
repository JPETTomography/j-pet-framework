# J-PET framework utilitiy CMake functions
#
# Author: Adam Strzelecki <adam.strzelecki@uj.edu.pl>
#
# Description:
#   Provides CMake functions helping setting up the project.

# Generate ROOT dictionaries for given SOURCES, excluding these given after
# EXCLUDE or limiting to these given after INCLUDE
function(generate_root_dictionaries OUT_VAR)
  cmake_parse_arguments(ARG "" "" "SOURCES;EXCLUDE;INCLUDE" ${ARGN})
  # generate ROOT dictionaries for all other source files
  foreach(source ${ARG_SOURCES})
    get_filename_component(name ${source} NAME)
    get_filename_component(ext  ${source} EXT)
    string(REGEX REPLACE ${ext} "LinkDef.h" linkdef ${source})
    string(REGEX REPLACE ${ext} ".h"        header  ${source})
    string(REGEX REPLACE ${ext} ""          name    ${name})
    if(NOT EXISTS ${header})
      continue()
    endif()
    list(FIND ARG_EXCLUDE ${name} index)
    if(index GREATER -1)
      continue()
    endif()
    if(ARG_INCLUDE)
      list(FIND ARG_INCLUDE ${name} index)
      if(index EQUAL -1)
        continue()
      endif()
    endif()
    set(dictionary
      ${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/Dictionaries/${name}Dictionary)
    if(EXISTS ${linkdef})
      root_generate_dictionary(${dictionary} ${header}
        LINKDEF ${linkdef}
        OPTIONS -f
        )
    else()
      root_generate_dictionary(${dictionary} ${header}
        OPTIONS -f
        )
    endif()
    list(APPEND dictionaries ${dictionary}.cxx)
  endforeach()
  SET(${OUT_VAR} ${dictionaries} PARENT_SCOPE)
endfunction()
