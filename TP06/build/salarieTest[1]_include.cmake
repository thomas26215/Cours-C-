if(EXISTS "/home/thomas/Desktop/programmation/C++/Cours/TP06/build/salarieTest[1]_tests.cmake")
  include("/home/thomas/Desktop/programmation/C++/Cours/TP06/build/salarieTest[1]_tests.cmake")
else()
  add_test(salarieTest_NOT_BUILT salarieTest_NOT_BUILT)
endif()
