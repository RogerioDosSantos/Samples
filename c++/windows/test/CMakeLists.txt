cmake_minimum_required (VERSION 2.8.11)
project (WindowsSamplesTest)

add_definitions (-DTESTCODE)

add_executable (windows_samples_test
  ./windows_sample_test.cpp
  )

target_include_directories (windows_samples_test 
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
  )

install (TARGETS windows_samples_test
  DESTINATION bin
  )
