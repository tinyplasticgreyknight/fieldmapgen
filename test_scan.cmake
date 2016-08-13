include(files.cmake)

set(TEST_INDEX_FILENAME "${CMAKE_CURRENT_BINARY_DIR}/CTestTestfile.cmake")
set(TEST_CASE_REGEX "^.*TEST_CASE\\((.+)\\).*$")

macro(clear_existing_tests)
  file(WRITE ${TEST_INDEX_FILENAME} "")
endmacro()

macro(test_case name suitename)
  set(test_line "add_test(${name} ${suitename} \"${name}\")")
  file(APPEND ${TEST_INDEX_FILENAME} "${test_line}\n")
endmacro()

macro(scan_for_tests filename suitename)
  file(READ ${filename} file_contents)
  string(REPLACE "\n" ";" file_lines "${file_contents}")

  foreach(line ${file_lines})
	if("${line}" MATCHES ${TEST_CASE_REGEX})
	  string(REGEX REPLACE ${TEST_CASE_REGEX} "\\1" test_name ${line})
	  test_case(${test_name} ${suitename})
	endif()
  endforeach()
endmacro()

clear_existing_tests()
foreach(filename ${TEST_SUITE_FILES})
  scan_for_tests(${filename} testsuite)
endforeach()
