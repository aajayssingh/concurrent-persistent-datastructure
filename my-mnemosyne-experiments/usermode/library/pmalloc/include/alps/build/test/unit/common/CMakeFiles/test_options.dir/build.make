# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_SOURCE_DIR = /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/build

# Include any dependencies generated for this target.
include test/unit/common/CMakeFiles/test_options.dir/depend.make

# Include the progress variables for this target.
include test/unit/common/CMakeFiles/test_options.dir/progress.make

# Include the compile flags for this target's objects.
include test/unit/common/CMakeFiles/test_options.dir/flags.make

test/unit/common/CMakeFiles/test_options.dir/test_options.cc.o: test/unit/common/CMakeFiles/test_options.dir/flags.make
test/unit/common/CMakeFiles/test_options.dir/test_options.cc.o: ../test/unit/common/test_options.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/unit/common/CMakeFiles/test_options.dir/test_options.cc.o"
	cd /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/build/test/unit/common && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_options.dir/test_options.cc.o -c /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/test/unit/common/test_options.cc

test/unit/common/CMakeFiles/test_options.dir/test_options.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_options.dir/test_options.cc.i"
	cd /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/build/test/unit/common && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/test/unit/common/test_options.cc > CMakeFiles/test_options.dir/test_options.cc.i

test/unit/common/CMakeFiles/test_options.dir/test_options.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_options.dir/test_options.cc.s"
	cd /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/build/test/unit/common && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/test/unit/common/test_options.cc -o CMakeFiles/test_options.dir/test_options.cc.s

test/unit/common/CMakeFiles/test_options.dir/test_options.cc.o.requires:

.PHONY : test/unit/common/CMakeFiles/test_options.dir/test_options.cc.o.requires

test/unit/common/CMakeFiles/test_options.dir/test_options.cc.o.provides: test/unit/common/CMakeFiles/test_options.dir/test_options.cc.o.requires
	$(MAKE) -f test/unit/common/CMakeFiles/test_options.dir/build.make test/unit/common/CMakeFiles/test_options.dir/test_options.cc.o.provides.build
.PHONY : test/unit/common/CMakeFiles/test_options.dir/test_options.cc.o.provides

test/unit/common/CMakeFiles/test_options.dir/test_options.cc.o.provides.build: test/unit/common/CMakeFiles/test_options.dir/test_options.cc.o


# Object files for target test_options
test_options_OBJECTS = \
"CMakeFiles/test_options.dir/test_options.cc.o"

# External object files for target test_options
test_options_EXTERNAL_OBJECTS =

test/unit/common/test_options: test/unit/common/CMakeFiles/test_options.dir/test_options.cc.o
test/unit/common/test_options: test/unit/common/CMakeFiles/test_options.dir/build.make
test/unit/common/test_options: third-party/gtest/libgtest.a
test/unit/common/test_options: src/libalps.so
test/unit/common/test_options: third-party/libbacktrace/libbacktrace.a
test/unit/common/test_options: third-party/yaml-cpp-0.5.2/libyaml-cpp.a
test/unit/common/test_options: test/unit/common/CMakeFiles/test_options.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test_options"
	cd /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/build/test/unit/common && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_options.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/unit/common/CMakeFiles/test_options.dir/build: test/unit/common/test_options

.PHONY : test/unit/common/CMakeFiles/test_options.dir/build

test/unit/common/CMakeFiles/test_options.dir/requires: test/unit/common/CMakeFiles/test_options.dir/test_options.cc.o.requires

.PHONY : test/unit/common/CMakeFiles/test_options.dir/requires

test/unit/common/CMakeFiles/test_options.dir/clean:
	cd /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/build/test/unit/common && $(CMAKE_COMMAND) -P CMakeFiles/test_options.dir/cmake_clean.cmake
.PHONY : test/unit/common/CMakeFiles/test_options.dir/clean

test/unit/common/CMakeFiles/test_options.dir/depend:
	cd /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/test/unit/common /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/build /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/build/test/unit/common /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/build/test/unit/common/CMakeFiles/test_options.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/unit/common/CMakeFiles/test_options.dir/depend

