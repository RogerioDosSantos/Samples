cmake_minimum_required (VERSION 2.8)

# Configuration
set(var_binary_name "boost")
string(TOLOWER "${config_project_name}" var_project_name)
string(TOLOWER "${config_stage_dir}" var_stage_dir)
string(TOLOWER "${config_platform}" var_platform)
string(TOLOWER "${config_third_party_dir}" var_third_party_dir)

message("*** Staging ${var_project_name}/${var_binary_name}")
message(" - Stage Directory: ${var_stage_dir}")
message(" - Platform: ${var_platform}")
message(" - Source Directory: ${CMAKE_SOURCE_DIR}")
message(" - Build Type: ${CMAKE_BUILD_TYPE}")

set(var_project_libraries
  program_options
  timer
  )
message(" - Project Libraries: ${var_project_libraries}")

# Compilation
foreach(var_project_library ${var_project_libraries})
  add_subdirectory(${var_project_library})
endforeach(var_project_library)

