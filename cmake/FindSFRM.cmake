find_path(SFRM_INCLUDE_DIR NAMES ResourceManager.h)
find_library(SFRM_LIBRARY NAMES sfrm)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(SFRM DEFAULT_MSG SFRM_INCLUDE_DIR SFRM_LIBRARY)

if(SFRM_FOUND)
	set(SFRM_INCLUDE_DIRS ${SFRM_INCLUDE_DIR})
	set(SFRM_LIBRARIES ${SFRM_LIBRARY})
endif()

mark_as_advanced(SFRM_INCLUDE_DIR SFRM_LIBRARY)