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

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/fatih/git/GuvenlikBekcisi/bekci/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/fatih/git/GuvenlikBekcisi/bekci/build

# Include any dependencies generated for this target.
include bekci/CMakeFiles/pugi.dir/depend.make

# Include the progress variables for this target.
include bekci/CMakeFiles/pugi.dir/progress.make

# Include the compile flags for this target's objects.
include bekci/CMakeFiles/pugi.dir/flags.make

bekci/CMakeFiles/pugi.dir/include/pugi/pugixml.cpp.o: bekci/CMakeFiles/pugi.dir/flags.make
bekci/CMakeFiles/pugi.dir/include/pugi/pugixml.cpp.o: /home/fatih/git/GuvenlikBekcisi/bekci/src/bekci/include/pugi/pugixml.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/fatih/git/GuvenlikBekcisi/bekci/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object bekci/CMakeFiles/pugi.dir/include/pugi/pugixml.cpp.o"
	cd /home/fatih/git/GuvenlikBekcisi/bekci/build/bekci && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/pugi.dir/include/pugi/pugixml.cpp.o -c /home/fatih/git/GuvenlikBekcisi/bekci/src/bekci/include/pugi/pugixml.cpp

bekci/CMakeFiles/pugi.dir/include/pugi/pugixml.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pugi.dir/include/pugi/pugixml.cpp.i"
	cd /home/fatih/git/GuvenlikBekcisi/bekci/build/bekci && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/fatih/git/GuvenlikBekcisi/bekci/src/bekci/include/pugi/pugixml.cpp > CMakeFiles/pugi.dir/include/pugi/pugixml.cpp.i

bekci/CMakeFiles/pugi.dir/include/pugi/pugixml.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pugi.dir/include/pugi/pugixml.cpp.s"
	cd /home/fatih/git/GuvenlikBekcisi/bekci/build/bekci && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/fatih/git/GuvenlikBekcisi/bekci/src/bekci/include/pugi/pugixml.cpp -o CMakeFiles/pugi.dir/include/pugi/pugixml.cpp.s

bekci/CMakeFiles/pugi.dir/include/pugi/pugixml.cpp.o.requires:
.PHONY : bekci/CMakeFiles/pugi.dir/include/pugi/pugixml.cpp.o.requires

bekci/CMakeFiles/pugi.dir/include/pugi/pugixml.cpp.o.provides: bekci/CMakeFiles/pugi.dir/include/pugi/pugixml.cpp.o.requires
	$(MAKE) -f bekci/CMakeFiles/pugi.dir/build.make bekci/CMakeFiles/pugi.dir/include/pugi/pugixml.cpp.o.provides.build
.PHONY : bekci/CMakeFiles/pugi.dir/include/pugi/pugixml.cpp.o.provides

bekci/CMakeFiles/pugi.dir/include/pugi/pugixml.cpp.o.provides.build: bekci/CMakeFiles/pugi.dir/include/pugi/pugixml.cpp.o

# Object files for target pugi
pugi_OBJECTS = \
"CMakeFiles/pugi.dir/include/pugi/pugixml.cpp.o"

# External object files for target pugi
pugi_EXTERNAL_OBJECTS =

/home/fatih/git/GuvenlikBekcisi/bekci/devel/lib/libpugi.so: bekci/CMakeFiles/pugi.dir/include/pugi/pugixml.cpp.o
/home/fatih/git/GuvenlikBekcisi/bekci/devel/lib/libpugi.so: bekci/CMakeFiles/pugi.dir/build.make
/home/fatih/git/GuvenlikBekcisi/bekci/devel/lib/libpugi.so: bekci/CMakeFiles/pugi.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX shared library /home/fatih/git/GuvenlikBekcisi/bekci/devel/lib/libpugi.so"
	cd /home/fatih/git/GuvenlikBekcisi/bekci/build/bekci && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pugi.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
bekci/CMakeFiles/pugi.dir/build: /home/fatih/git/GuvenlikBekcisi/bekci/devel/lib/libpugi.so
.PHONY : bekci/CMakeFiles/pugi.dir/build

bekci/CMakeFiles/pugi.dir/requires: bekci/CMakeFiles/pugi.dir/include/pugi/pugixml.cpp.o.requires
.PHONY : bekci/CMakeFiles/pugi.dir/requires

bekci/CMakeFiles/pugi.dir/clean:
	cd /home/fatih/git/GuvenlikBekcisi/bekci/build/bekci && $(CMAKE_COMMAND) -P CMakeFiles/pugi.dir/cmake_clean.cmake
.PHONY : bekci/CMakeFiles/pugi.dir/clean

bekci/CMakeFiles/pugi.dir/depend:
	cd /home/fatih/git/GuvenlikBekcisi/bekci/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/fatih/git/GuvenlikBekcisi/bekci/src /home/fatih/git/GuvenlikBekcisi/bekci/src/bekci /home/fatih/git/GuvenlikBekcisi/bekci/build /home/fatih/git/GuvenlikBekcisi/bekci/build/bekci /home/fatih/git/GuvenlikBekcisi/bekci/build/bekci/CMakeFiles/pugi.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : bekci/CMakeFiles/pugi.dir/depend
