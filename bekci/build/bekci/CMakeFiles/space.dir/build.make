# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/fatih/git/GuvenlikBekcisi/bekci/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/fatih/git/GuvenlikBekcisi/bekci/build

# Include any dependencies generated for this target.
include bekci/CMakeFiles/space.dir/depend.make

# Include the progress variables for this target.
include bekci/CMakeFiles/space.dir/progress.make

# Include the compile flags for this target's objects.
include bekci/CMakeFiles/space.dir/flags.make

bekci/CMakeFiles/space.dir/space.cpp.o: bekci/CMakeFiles/space.dir/flags.make
bekci/CMakeFiles/space.dir/space.cpp.o: /home/fatih/git/GuvenlikBekcisi/bekci/src/bekci/space.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/fatih/git/GuvenlikBekcisi/bekci/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object bekci/CMakeFiles/space.dir/space.cpp.o"
	cd /home/fatih/git/GuvenlikBekcisi/bekci/build/bekci && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/space.dir/space.cpp.o -c /home/fatih/git/GuvenlikBekcisi/bekci/src/bekci/space.cpp

bekci/CMakeFiles/space.dir/space.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/space.dir/space.cpp.i"
	cd /home/fatih/git/GuvenlikBekcisi/bekci/build/bekci && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/fatih/git/GuvenlikBekcisi/bekci/src/bekci/space.cpp > CMakeFiles/space.dir/space.cpp.i

bekci/CMakeFiles/space.dir/space.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/space.dir/space.cpp.s"
	cd /home/fatih/git/GuvenlikBekcisi/bekci/build/bekci && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/fatih/git/GuvenlikBekcisi/bekci/src/bekci/space.cpp -o CMakeFiles/space.dir/space.cpp.s

bekci/CMakeFiles/space.dir/space.cpp.o.requires:
.PHONY : bekci/CMakeFiles/space.dir/space.cpp.o.requires

bekci/CMakeFiles/space.dir/space.cpp.o.provides: bekci/CMakeFiles/space.dir/space.cpp.o.requires
	$(MAKE) -f bekci/CMakeFiles/space.dir/build.make bekci/CMakeFiles/space.dir/space.cpp.o.provides.build
.PHONY : bekci/CMakeFiles/space.dir/space.cpp.o.provides

bekci/CMakeFiles/space.dir/space.cpp.o.provides.build: bekci/CMakeFiles/space.dir/space.cpp.o

# Object files for target space
space_OBJECTS = \
"CMakeFiles/space.dir/space.cpp.o"

# External object files for target space
space_EXTERNAL_OBJECTS =

/home/fatih/git/GuvenlikBekcisi/bekci/devel/lib/bekci/space: bekci/CMakeFiles/space.dir/space.cpp.o
/home/fatih/git/GuvenlikBekcisi/bekci/devel/lib/bekci/space: bekci/CMakeFiles/space.dir/build.make
/home/fatih/git/GuvenlikBekcisi/bekci/devel/lib/bekci/space: /opt/ros/indigo/lib/libroscpp.so
/home/fatih/git/GuvenlikBekcisi/bekci/devel/lib/bekci/space: /usr/lib/x86_64-linux-gnu/libboost_signals.so
/home/fatih/git/GuvenlikBekcisi/bekci/devel/lib/bekci/space: /opt/ros/indigo/lib/librosconsole.so
/home/fatih/git/GuvenlikBekcisi/bekci/devel/lib/bekci/space: /opt/ros/indigo/lib/librosconsole_log4cxx.so
/home/fatih/git/GuvenlikBekcisi/bekci/devel/lib/bekci/space: /opt/ros/indigo/lib/librosconsole_backend_interface.so
/home/fatih/git/GuvenlikBekcisi/bekci/devel/lib/bekci/space: /usr/lib/liblog4cxx.so
/home/fatih/git/GuvenlikBekcisi/bekci/devel/lib/bekci/space: /usr/lib/x86_64-linux-gnu/libboost_regex.so
/home/fatih/git/GuvenlikBekcisi/bekci/devel/lib/bekci/space: /opt/ros/indigo/lib/libroscpp_serialization.so
/home/fatih/git/GuvenlikBekcisi/bekci/devel/lib/bekci/space: /opt/ros/indigo/lib/librostime.so
/home/fatih/git/GuvenlikBekcisi/bekci/devel/lib/bekci/space: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
/home/fatih/git/GuvenlikBekcisi/bekci/devel/lib/bekci/space: /opt/ros/indigo/lib/libxmlrpcpp.so
/home/fatih/git/GuvenlikBekcisi/bekci/devel/lib/bekci/space: /opt/ros/indigo/lib/libcpp_common.so
/home/fatih/git/GuvenlikBekcisi/bekci/devel/lib/bekci/space: /usr/lib/x86_64-linux-gnu/libboost_thread.so
/home/fatih/git/GuvenlikBekcisi/bekci/devel/lib/bekci/space: /usr/lib/x86_64-linux-gnu/libpthread.so
/home/fatih/git/GuvenlikBekcisi/bekci/devel/lib/bekci/space: /usr/lib/x86_64-linux-gnu/libconsole_bridge.so
/home/fatih/git/GuvenlikBekcisi/bekci/devel/lib/bekci/space: /opt/ros/indigo/lib/libroslib.so
/home/fatih/git/GuvenlikBekcisi/bekci/devel/lib/bekci/space: /opt/ros/indigo/lib/librospack.so
/home/fatih/git/GuvenlikBekcisi/bekci/devel/lib/bekci/space: /usr/lib/x86_64-linux-gnu/libpython2.7.so
/home/fatih/git/GuvenlikBekcisi/bekci/devel/lib/bekci/space: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
/home/fatih/git/GuvenlikBekcisi/bekci/devel/lib/bekci/space: /usr/lib/x86_64-linux-gnu/libboost_program_options.so
/home/fatih/git/GuvenlikBekcisi/bekci/devel/lib/bekci/space: /usr/lib/x86_64-linux-gnu/libboost_system.so
/home/fatih/git/GuvenlikBekcisi/bekci/devel/lib/bekci/space: /usr/lib/x86_64-linux-gnu/libtinyxml.so
/home/fatih/git/GuvenlikBekcisi/bekci/devel/lib/bekci/space: bekci/CMakeFiles/space.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable /home/fatih/git/GuvenlikBekcisi/bekci/devel/lib/bekci/space"
	cd /home/fatih/git/GuvenlikBekcisi/bekci/build/bekci && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/space.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
bekci/CMakeFiles/space.dir/build: /home/fatih/git/GuvenlikBekcisi/bekci/devel/lib/bekci/space
.PHONY : bekci/CMakeFiles/space.dir/build

bekci/CMakeFiles/space.dir/requires: bekci/CMakeFiles/space.dir/space.cpp.o.requires
.PHONY : bekci/CMakeFiles/space.dir/requires

bekci/CMakeFiles/space.dir/clean:
	cd /home/fatih/git/GuvenlikBekcisi/bekci/build/bekci && $(CMAKE_COMMAND) -P CMakeFiles/space.dir/cmake_clean.cmake
.PHONY : bekci/CMakeFiles/space.dir/clean

bekci/CMakeFiles/space.dir/depend:
	cd /home/fatih/git/GuvenlikBekcisi/bekci/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/fatih/git/GuvenlikBekcisi/bekci/src /home/fatih/git/GuvenlikBekcisi/bekci/src/bekci /home/fatih/git/GuvenlikBekcisi/bekci/build /home/fatih/git/GuvenlikBekcisi/bekci/build/bekci /home/fatih/git/GuvenlikBekcisi/bekci/build/bekci/CMakeFiles/space.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : bekci/CMakeFiles/space.dir/depend

