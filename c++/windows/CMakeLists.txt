cmake_minimum_required (VERSION 2.8.11)
project (windows_samples)

# MFC Configuration
add_definitions (
  -D_AFXDLL
  -DUNICODE
  -D_UNICODE
  )
set(CMAKE_MFC_FLAG 1)

add_subdirectory (test)

add_executable (windows_samples
  ./source/windows_sampler.cpp
  )

target_include_directories (windows_samples 
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
  )

string(TOLOWER "${PROJECT_SOURCE_DIR}/stage/${CMAKE_PROJECT_NAME}/${CMAKE_VS_PLATFORM_TOOLSET}" var_bin_output_dir)
message(" - Setting binary output directory to: ${var_bin_output_dir}")
set_target_properties(windows_samples
  PROPERTIES 
  LIBRARY_OUTPUT_DIRECTORY ${var_bin_output_dir}
  ARCHIVE_OUTPUT_DIRECTORY ${var_bin_output_dir}
  RUNTIME_OUTPUT_DIRECTORY ${var_bin_output_dir}
  OUTPUT_NAME windows_samples
  )

