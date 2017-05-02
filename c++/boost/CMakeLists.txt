cmake_minimum_required(VERSION 2.8.3)

include(ExternalProject)


# about this project
# ------------------

# project (boost_samples)
# SET(boost_samples_VERSION_MAJOR "1")
# SET(boost_samples_VERSION_MINOR "0")
# SET(boost_samples_VERSION_PATCH "0")
# SET(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

set(var_binary_name "boost_examples")

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
  ./source/boost_samples.cpp
  # ./source/timer.cpp
  ./source/webserver.cpp
  ./source/webclient.cpp
  )
message(" - Source Files: ${var_source_files}")

set(var_link_libraries
  libprogram_options.a
  libsystem.a
  # libtimer.a
  # libchrono.a
  # libthread.a
  # libfilesystem.a
  )
message(" - Link Libraries: ${var_link_libraries}")

set(var_static_dependency_projects
  ./libs/boost/program_options
  ./libs/boost/system
  # ./libs/boost/timer
  # ./libs/boost/chrono
  # ./libs/boost/thread
  # ./libs/boost/filesystem
  )
message(" - Static Dependencies Projects: ${var_static_dependency_projects}")

include_directories(
  /root/third-party/boost1.55
  )

link_directories(
  ${var_bin_dir}
  /root/samples/c++/boost/stage/boost/bin/default/release
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



# # External Libraries
# # execute_process(COMMAND "/root/host/git/samples/c++/boost/libs/boost/program_options/build/compile_default_release.sh")
# SET(var_static_dependency_projects "boost_program_options")
# externalproject_add(${var_static_dependency_projects}
#   PREFIX            ${var_static_dependency_projects}
#   TMP_DIR           ${var_static_dependency_projects}/temp
#   STAMP_DIR         ${var_static_dependency_projects}/stamp
#   #--Download step--------------
#   DOWNLOAD_DIR      ${var_static_dependency_projects}/download
#   # DOWNLOAD_COMMAND  rsync -av --progress /root/samples/c++/boost/libs/boost ../source
#   DOWNLOAD_COMMAND  ""
#   #--Update/Patch step----------
#   UPDATE_COMMAND    ""
#   #--Configure step-------------
#   # SOURCE_DIR        ${var_static_dependency_projects}/source
#   SOURCE_DIR        "/root/host/git/samples/c++/boost/libs/boost/program_options/build"
#   CONFIGURE_COMMAND ""
#   #--Build step-----------------
#   # BUILD_COMMAND     ../source/boost/program_options/build/compile.sh "${var_project_name}" "${var_platform}" "${CMAKE_BUILD_TYPE}" "${var_third_party_dir}" "${var_stage_dir}"
#   # BUILD_COMMAND        "/root/host/git/samples/c++/boost/libs/boost/program_options/build/compile_default_release.sh"
#   BUILD_COMMAND        "./compile_default_release.sh"
#   # BUILD_COMMAND     ./compile.sh "${var_project_name}" "${var_platform}" "${CMAKE_BUILD_TYPE}" "${var_third_party_dir}" "${var_stage_dir}"
#   BUILD_IN_SOURCE   1
#   BUILD_ALWAYS 1
#   #--Install step---------------
#   # INSTALL_COMMAND    rsync -av --progress ./program_options/build/default/*.a ../output/
#   INSTALL_COMMAND ""
#   )
#
# # externalproject_get_property(${var_static_dependency_projects} var_dependency_installation_dir)
# # message("${var_static_dependency_projects} installation directory: ${var_dependency_installation_dir}")
#

# Thread Libraries (Needed for pthread support)
find_package(Threads)
set(var_link_libraries ${var_link_libraries} ${CMAKE_THREAD_LIBS_INIT})
message(" - Theads Libraries: ${CMAKE_THREAD_LIBS_INIT}")

add_library(${var_binary_name}_static ${var_source_files})
set_target_properties(${var_binary_name}_static 
  PROPERTIES 
  LIBRARY_OUTPUT_DIRECTORY ${var_bin_dir}
  ARCHIVE_OUTPUT_DIRECTORY ${var_bin_dir}
  RUNTIME_OUTPUT_DIRECTORY ${var_bin_dir}
  OUTPUT_NAME ${var_binary_name}
  )

# add_library(${var_binary_name}_shared SHARED ${var_source_files})
# add_dependencies(${var_binary_name}_shared ${var_static_dependency_projects})
# target_link_libraries(${var_binary_name}_shared ${var_link_libraries})
# set_target_properties(${var_binary_name}_shared 
#   PROPERTIES 
#   LIBRARY_OUTPUT_DIRECTORY ${var_bin_dir}
#   ARCHIVE_OUTPUT_DIRECTORY ${var_bin_dir}
#   RUNTIME_OUTPUT_DIRECTORY ${var_bin_dir}
#   OUTPUT_NAME ${var_binary_name}
#   )

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

