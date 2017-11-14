cmake_minimum_required(VERSION 2.8.3)

include(ExternalProject)

project(0mq_samples)

set(var_binary_name "0mq_examples")

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

string(TOLOWER "${var_stage_dir}/${var_project_name}/bin/${var_platform}/${CMAKE_BUILD_TYPE}" var_bin_dir)
message(" - Bin Directory: ${CMAKE_BUILD_TYPE}")

set(var_source_files
  ./source/main.cpp
  ./source/request_reply_server.cpp
  )
message(" - Source Files: ${var_source_files}")

set(var_link_libraries
  libboost_program_options.a
  )
message(" - Link Libraries: ${var_link_libraries}")

set(var_static_dependency_projects
  ./libs/boost/program_options
  )
message(" - Static Dependencies Projects: ${var_static_dependency_projects}")

include_directories(
  ${var_third_party_dir}/boost1.55
  )

link_directories(
  ${var_bin_dir}
  )

message(" - Binary Directory: ${var_bin_dir}")

# Compilation of Dependencies
message("Adding Dependencies:")
foreach(var_dependency_project ${var_static_dependency_projects})
  message("- ${CMAKE_CURRENT_SOURCE_DIR}/${var_dependency_project}")
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/${var_dependency_project})
  get_filename_component(var_dependency_name ${var_dependency_project} NAME)
  set(var_all_dependency_projects ${var_all_dependency_projects} ${var_dependency_name}_static)
endforeach(var_dependency_project)

add_library(${var_binary_name}_static ${var_source_files})
set_target_properties(${var_binary_name}_static
  PROPERTIES
  LIBRARY_OUTPUT_DIRECTORY ${var_bin_dir}
  ARCHIVE_OUTPUT_DIRECTORY ${var_bin_dir}
  RUNTIME_OUTPUT_DIRECTORY ${var_bin_dir}
  OUTPUT_NAME ${var_binary_name}
  )

add_executable(${var_binary_name}_executable ${var_source_files})
add_dependencies(${var_binary_name}_executable ${var_all_dependency_projects})
target_link_libraries(${var_binary_name}_executable ${var_link_libraries})
set_target_properties(${var_binary_name}_executable
  PROPERTIES
  LIBRARY_OUTPUT_DIRECTORY ${var_bin_dir}
  ARCHIVE_OUTPUT_DIRECTORY ${var_bin_dir}
  RUNTIME_OUTPUT_DIRECTORY ${var_bin_dir}
  OUTPUT_NAME ${var_binary_name}
  )

