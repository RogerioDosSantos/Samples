cmake_minimum_required (VERSION 2.8)

set(var_binary_name "serialization")

# Configuration
string(TOLOWER "${config_project_name}" var_project_name)
string(TOLOWER "${config_stage_dir}" var_stage_dir)
string(TOLOWER "${config_platform}" var_platform)
string(TOLOWER "${config_third_party_dir}" var_third_party_dir)

message("*** Staging ${var_project_name}/${var_binary_name}")
message(" - Stage Directory: ${var_stage_dir}")
message(" - Platform: ${var_platform}")
message(" - Source Directory: ${CMAKE_SOURCE_DIR}")
message(" - Build Type: ${CMAKE_BUILD_TYPE}")


file(GLOB var_source_files
  ${var_third_party_dir}/boost1.55/libs/${var_binary_name}/src/*.h
  ${var_third_party_dir}/boost1.55/libs/${var_binary_name}/src/*.cpp
  )
message("Source Files: ${var_source_files}")

include_directories(
  /root/third-party/boost1.55
  )

add_definitions(-DBOOST_THREAD_PROVIDES_INTERRUPTIONS)

string(TOLOWER "${var_stage_dir}/${var_project_name}/bin/${var_platform}/${CMAKE_BUILD_TYPE}" var_bin_dir)

add_library(${var_binary_name}_static ${var_source_files})
set_target_properties(${var_binary_name}_static 
  PROPERTIES 
  LIBRARY_OUTPUT_DIRECTORY ${var_bin_dir}
  ARCHIVE_OUTPUT_DIRECTORY ${var_bin_dir}
  RUNTIME_OUTPUT_DIRECTORY ${var_bin_dir}
  OUTPUT_NAME boost_${var_binary_name}
  )

add_library(${var_binary_name}_shared SHARED ${var_source_files})
set_target_properties(${var_binary_name}_shared 
  PROPERTIES 
  LIBRARY_OUTPUT_DIRECTORY ${var_bin_dir}
  ARCHIVE_OUTPUT_DIRECTORY ${var_bin_dir}
  RUNTIME_OUTPUT_DIRECTORY ${var_bin_dir}
  OUTPUT_NAME boost_${var_binary_name}
  )
