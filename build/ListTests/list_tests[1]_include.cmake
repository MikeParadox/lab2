if(EXISTS "/home/mikhail/programming/cs/dsa/labs/Lab-02/build/ListTests/list_tests[1]_tests.cmake")
  include("/home/mikhail/programming/cs/dsa/labs/Lab-02/build/ListTests/list_tests[1]_tests.cmake")
else()
  add_test(list_tests_NOT_BUILT list_tests_NOT_BUILT)
endif()
