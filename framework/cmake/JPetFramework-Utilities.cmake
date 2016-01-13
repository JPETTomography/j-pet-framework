# J-PET framework utilitiy CMake functions
#
# Author: Adam Strzelecki <adam.strzelecki@uj.edu.pl>
#
# Description:
#   Provides CMake functions helping setting up the project.

# function generate_root_dictionaries(output_variable
#                                     SOURCES source1.cpp ...
#                                     EXCLUDE name1 ...
#                                     INCLUDE name1)
#
# Generate ROOT dictionaries for given SOURCES, excluding these given after
# EXCLUDE or limiting to these given after INCLUDE.
#
function(generate_root_dictionaries OUT_VAR)
  cmake_parse_arguments(ARG "" "" "SOURCES;EXCLUDE;INCLUDE" ${ARGN})
  # generate ROOT dictionaries for all other source files
  foreach(source ${ARG_SOURCES})
    get_filename_component(name ${source} NAME)
    get_filename_component(ext  ${source} EXT)
    string(REGEX REPLACE ${ext} "LinkDef.h" linkdef ${source})
    string(REGEX REPLACE ${ext} ".h"        header  ${source})
    string(REGEX REPLACE ${ext} ""          name    ${name})
    set(skip FALSE)
    # check if there is corresponding header file to the source file
    if(NOT EXISTS ${header})
      set(skip TRUE) # skip generation
    elseif(ARG_INCLUDE)
      # if INCLUDE was specified, allow only names specified on the list
      list(FIND ARG_INCLUDE ${name} index)
      if(index EQUAL -1)
        set(skip TRUE)
      endif()
    else()
      # otherwise check if name was excluded
      list(FIND ARG_EXCLUDE ${name} index)
      if(index GREATER -1)
        set(skip TRUE)
      endif()
    endif()
    if(NOT skip)
      # output dictionary file will be kept in CMake build folder
      file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/Dictionaries)
      set(dictionary
        ${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/Dictionaries/${name}Dictionary)
      get_directory_property(incdirs INCLUDE_DIRECTORIES)
      set_directory_properties(PROPERTIES INCLUDE_DIRECTORIES "${incdirs};/")
      string(REGEX REPLACE ^/ "" header "${header}")
      if(EXISTS ${linkdef})
        string(REGEX REPLACE ^/ "" linkdef "${linkdef}")
        root_generate_dictionary(${dictionary} ${header}
          LINKDEF ${linkdef}
          OPTIONS -p
          )
      else()
        root_generate_dictionary(${dictionary} ${header}
          OPTIONS -p
          )
      endif()
      set_directory_properties(PROPERTIES INCLUDE_DIRECTORIES "${incdirs}")
      list(APPEND dictionaries ${dictionary}.cxx)
    endif()
  endforeach()
  # return generated dictionary sources to given variable
  set(${OUT_VAR} ${dictionaries} PARENT_SCOPE)
endfunction()
