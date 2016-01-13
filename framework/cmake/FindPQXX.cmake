if(NOT PQXX_FOUND)
  find_path(PQXX_INCLUDE_DIR pqxx/pqxx)
  find_library(PQXX_LIBRARY pqxx)
  mark_as_advanced(PQXX_INCLUDE_DIR PQXX_LIBRARY)

  include(FindPackageHandleStandardArgs)
  find_package_handle_standard_args(PQXX DEFAULT_MSG
    PQXX_LIBRARY PQXX_INCLUDE_DIR)

  set(PQXX_INCLUDE_DIRS ${PQXX_INCLUDE_DIR})
  set(PQXX_LIBRARIES ${PQXX_LIBRARY})
endif(NOT PQXX_FOUND)
