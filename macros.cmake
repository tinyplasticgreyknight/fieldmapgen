macro(enable_cpp_11)
  # kludge to enable C++11 mode on older CMake versions
  if(${CMAKE_VERSION} VERSION_LESS "3.1")
	if(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
	  set(CMAKE_CXX_FLAGS "-std=gnu++11 ${CMAKE_CXX_FLAGS}")
	else()
	  message(FATAL_ERROR "don't know how to set C++11 mode for compiler ${CMAKE_CXX_COMPILER_ID} :-(")
	endif()
  else(${CMAKE_VERSION} VERSION_LESS "3.2")
	set(CMAKE_CXX_STANDARD 11)
	set(CMAKE_CXX_STANDARD_REQUIRED ON)
  else()
	# this is the proper way :-)
	target_compile_features(fieldmapgen PRIVATE cxx_deleted_functions)
  endif()
endmacro()

macro(enable_lots_of_warnings)
  if(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -pedantic")
  endif()
endmacro()
