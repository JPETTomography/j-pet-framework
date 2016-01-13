if(NOT CONFIG++_FOUND)
  find_path(CONFIG++_INCLUDE_DIR libconfig.h++)
  find_library(CONFIG++_LIBRARY config++)
  mark_as_advanced(CONFIG++_INCLUDE_DIR CONFIG++_LIBRARY)

  include(FindPackageHandleStandardArgs)
  find_package_handle_standard_args(CONFIG++ DEFAULT_MSG
    CONFIG++_LIBRARY CONFIG++_INCLUDE_DIR)

  set(CONFIG++_INCLUDE_DIRS ${CONFIG++_INCLUDE_DIR})
  set(CONFIG++_LIBRARIES ${CONFIG++_LIBRARY})
endif(NOT CONFIG++_FOUND)
