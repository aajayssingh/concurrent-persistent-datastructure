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
include third-party/libbacktrace/CMakeFiles/backtrace.dir/depend.make

# Include the progress variables for this target.
include third-party/libbacktrace/CMakeFiles/backtrace.dir/progress.make

# Include the compile flags for this target's objects.
include third-party/libbacktrace/CMakeFiles/backtrace.dir/flags.make

third-party/libbacktrace/CMakeFiles/backtrace.dir/backtrace.c.o: third-party/libbacktrace/CMakeFiles/backtrace.dir/flags.make
third-party/libbacktrace/CMakeFiles/backtrace.dir/backtrace.c.o: ../third-party/libbacktrace/backtrace.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object third-party/libbacktrace/CMakeFiles/backtrace.dir/backtrace.c.o"
	cd /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/build/third-party/libbacktrace && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/backtrace.dir/backtrace.c.o   -c /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/libbacktrace/backtrace.c

third-party/libbacktrace/CMakeFiles/backtrace.dir/backtrace.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/backtrace.dir/backtrace.c.i"
	cd /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/build/third-party/libbacktrace && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/libbacktrace/backtrace.c > CMakeFiles/backtrace.dir/backtrace.c.i

third-party/libbacktrace/CMakeFiles/backtrace.dir/backtrace.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/backtrace.dir/backtrace.c.s"
	cd /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/build/third-party/libbacktrace && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/libbacktrace/backtrace.c -o CMakeFiles/backtrace.dir/backtrace.c.s

third-party/libbacktrace/CMakeFiles/backtrace.dir/backtrace.c.o.requires:

.PHONY : third-party/libbacktrace/CMakeFiles/backtrace.dir/backtrace.c.o.requires

third-party/libbacktrace/CMakeFiles/backtrace.dir/backtrace.c.o.provides: third-party/libbacktrace/CMakeFiles/backtrace.dir/backtrace.c.o.requires
	$(MAKE) -f third-party/libbacktrace/CMakeFiles/backtrace.dir/build.make third-party/libbacktrace/CMakeFiles/backtrace.dir/backtrace.c.o.provides.build
.PHONY : third-party/libbacktrace/CMakeFiles/backtrace.dir/backtrace.c.o.provides

third-party/libbacktrace/CMakeFiles/backtrace.dir/backtrace.c.o.provides.build: third-party/libbacktrace/CMakeFiles/backtrace.dir/backtrace.c.o


third-party/libbacktrace/CMakeFiles/backtrace.dir/simple.c.o: third-party/libbacktrace/CMakeFiles/backtrace.dir/flags.make
third-party/libbacktrace/CMakeFiles/backtrace.dir/simple.c.o: ../third-party/libbacktrace/simple.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object third-party/libbacktrace/CMakeFiles/backtrace.dir/simple.c.o"
	cd /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/build/third-party/libbacktrace && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/backtrace.dir/simple.c.o   -c /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/libbacktrace/simple.c

third-party/libbacktrace/CMakeFiles/backtrace.dir/simple.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/backtrace.dir/simple.c.i"
	cd /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/build/third-party/libbacktrace && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/libbacktrace/simple.c > CMakeFiles/backtrace.dir/simple.c.i

third-party/libbacktrace/CMakeFiles/backtrace.dir/simple.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/backtrace.dir/simple.c.s"
	cd /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/build/third-party/libbacktrace && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/libbacktrace/simple.c -o CMakeFiles/backtrace.dir/simple.c.s

third-party/libbacktrace/CMakeFiles/backtrace.dir/simple.c.o.requires:

.PHONY : third-party/libbacktrace/CMakeFiles/backtrace.dir/simple.c.o.requires

third-party/libbacktrace/CMakeFiles/backtrace.dir/simple.c.o.provides: third-party/libbacktrace/CMakeFiles/backtrace.dir/simple.c.o.requires
	$(MAKE) -f third-party/libbacktrace/CMakeFiles/backtrace.dir/build.make third-party/libbacktrace/CMakeFiles/backtrace.dir/simple.c.o.provides.build
.PHONY : third-party/libbacktrace/CMakeFiles/backtrace.dir/simple.c.o.provides

third-party/libbacktrace/CMakeFiles/backtrace.dir/simple.c.o.provides.build: third-party/libbacktrace/CMakeFiles/backtrace.dir/simple.c.o


third-party/libbacktrace/CMakeFiles/backtrace.dir/unknown.c.o: third-party/libbacktrace/CMakeFiles/backtrace.dir/flags.make
third-party/libbacktrace/CMakeFiles/backtrace.dir/unknown.c.o: ../third-party/libbacktrace/unknown.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object third-party/libbacktrace/CMakeFiles/backtrace.dir/unknown.c.o"
	cd /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/build/third-party/libbacktrace && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/backtrace.dir/unknown.c.o   -c /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/libbacktrace/unknown.c

third-party/libbacktrace/CMakeFiles/backtrace.dir/unknown.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/backtrace.dir/unknown.c.i"
	cd /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/build/third-party/libbacktrace && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/libbacktrace/unknown.c > CMakeFiles/backtrace.dir/unknown.c.i

third-party/libbacktrace/CMakeFiles/backtrace.dir/unknown.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/backtrace.dir/unknown.c.s"
	cd /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/build/third-party/libbacktrace && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/libbacktrace/unknown.c -o CMakeFiles/backtrace.dir/unknown.c.s

third-party/libbacktrace/CMakeFiles/backtrace.dir/unknown.c.o.requires:

.PHONY : third-party/libbacktrace/CMakeFiles/backtrace.dir/unknown.c.o.requires

third-party/libbacktrace/CMakeFiles/backtrace.dir/unknown.c.o.provides: third-party/libbacktrace/CMakeFiles/backtrace.dir/unknown.c.o.requires
	$(MAKE) -f third-party/libbacktrace/CMakeFiles/backtrace.dir/build.make third-party/libbacktrace/CMakeFiles/backtrace.dir/unknown.c.o.provides.build
.PHONY : third-party/libbacktrace/CMakeFiles/backtrace.dir/unknown.c.o.provides

third-party/libbacktrace/CMakeFiles/backtrace.dir/unknown.c.o.provides.build: third-party/libbacktrace/CMakeFiles/backtrace.dir/unknown.c.o


third-party/libbacktrace/CMakeFiles/backtrace.dir/mmapio.c.o: third-party/libbacktrace/CMakeFiles/backtrace.dir/flags.make
third-party/libbacktrace/CMakeFiles/backtrace.dir/mmapio.c.o: ../third-party/libbacktrace/mmapio.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object third-party/libbacktrace/CMakeFiles/backtrace.dir/mmapio.c.o"
	cd /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/build/third-party/libbacktrace && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/backtrace.dir/mmapio.c.o   -c /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/libbacktrace/mmapio.c

third-party/libbacktrace/CMakeFiles/backtrace.dir/mmapio.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/backtrace.dir/mmapio.c.i"
	cd /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/build/third-party/libbacktrace && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/libbacktrace/mmapio.c > CMakeFiles/backtrace.dir/mmapio.c.i

third-party/libbacktrace/CMakeFiles/backtrace.dir/mmapio.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/backtrace.dir/mmapio.c.s"
	cd /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/build/third-party/libbacktrace && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/libbacktrace/mmapio.c -o CMakeFiles/backtrace.dir/mmapio.c.s

third-party/libbacktrace/CMakeFiles/backtrace.dir/mmapio.c.o.requires:

.PHONY : third-party/libbacktrace/CMakeFiles/backtrace.dir/mmapio.c.o.requires

third-party/libbacktrace/CMakeFiles/backtrace.dir/mmapio.c.o.provides: third-party/libbacktrace/CMakeFiles/backtrace.dir/mmapio.c.o.requires
	$(MAKE) -f third-party/libbacktrace/CMakeFiles/backtrace.dir/build.make third-party/libbacktrace/CMakeFiles/backtrace.dir/mmapio.c.o.provides.build
.PHONY : third-party/libbacktrace/CMakeFiles/backtrace.dir/mmapio.c.o.provides

third-party/libbacktrace/CMakeFiles/backtrace.dir/mmapio.c.o.provides.build: third-party/libbacktrace/CMakeFiles/backtrace.dir/mmapio.c.o


third-party/libbacktrace/CMakeFiles/backtrace.dir/mmap.c.o: third-party/libbacktrace/CMakeFiles/backtrace.dir/flags.make
third-party/libbacktrace/CMakeFiles/backtrace.dir/mmap.c.o: ../third-party/libbacktrace/mmap.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object third-party/libbacktrace/CMakeFiles/backtrace.dir/mmap.c.o"
	cd /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/build/third-party/libbacktrace && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/backtrace.dir/mmap.c.o   -c /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/libbacktrace/mmap.c

third-party/libbacktrace/CMakeFiles/backtrace.dir/mmap.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/backtrace.dir/mmap.c.i"
	cd /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/build/third-party/libbacktrace && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/libbacktrace/mmap.c > CMakeFiles/backtrace.dir/mmap.c.i

third-party/libbacktrace/CMakeFiles/backtrace.dir/mmap.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/backtrace.dir/mmap.c.s"
	cd /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/build/third-party/libbacktrace && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/libbacktrace/mmap.c -o CMakeFiles/backtrace.dir/mmap.c.s

third-party/libbacktrace/CMakeFiles/backtrace.dir/mmap.c.o.requires:

.PHONY : third-party/libbacktrace/CMakeFiles/backtrace.dir/mmap.c.o.requires

third-party/libbacktrace/CMakeFiles/backtrace.dir/mmap.c.o.provides: third-party/libbacktrace/CMakeFiles/backtrace.dir/mmap.c.o.requires
	$(MAKE) -f third-party/libbacktrace/CMakeFiles/backtrace.dir/build.make third-party/libbacktrace/CMakeFiles/backtrace.dir/mmap.c.o.provides.build
.PHONY : third-party/libbacktrace/CMakeFiles/backtrace.dir/mmap.c.o.provides

third-party/libbacktrace/CMakeFiles/backtrace.dir/mmap.c.o.provides.build: third-party/libbacktrace/CMakeFiles/backtrace.dir/mmap.c.o


third-party/libbacktrace/CMakeFiles/backtrace.dir/atomic.c.o: third-party/libbacktrace/CMakeFiles/backtrace.dir/flags.make
third-party/libbacktrace/CMakeFiles/backtrace.dir/atomic.c.o: ../third-party/libbacktrace/atomic.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object third-party/libbacktrace/CMakeFiles/backtrace.dir/atomic.c.o"
	cd /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/build/third-party/libbacktrace && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/backtrace.dir/atomic.c.o   -c /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/libbacktrace/atomic.c

third-party/libbacktrace/CMakeFiles/backtrace.dir/atomic.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/backtrace.dir/atomic.c.i"
	cd /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/build/third-party/libbacktrace && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/libbacktrace/atomic.c > CMakeFiles/backtrace.dir/atomic.c.i

third-party/libbacktrace/CMakeFiles/backtrace.dir/atomic.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/backtrace.dir/atomic.c.s"
	cd /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/build/third-party/libbacktrace && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/libbacktrace/atomic.c -o CMakeFiles/backtrace.dir/atomic.c.s

third-party/libbacktrace/CMakeFiles/backtrace.dir/atomic.c.o.requires:

.PHONY : third-party/libbacktrace/CMakeFiles/backtrace.dir/atomic.c.o.requires

third-party/libbacktrace/CMakeFiles/backtrace.dir/atomic.c.o.provides: third-party/libbacktrace/CMakeFiles/backtrace.dir/atomic.c.o.requires
	$(MAKE) -f third-party/libbacktrace/CMakeFiles/backtrace.dir/build.make third-party/libbacktrace/CMakeFiles/backtrace.dir/atomic.c.o.provides.build
.PHONY : third-party/libbacktrace/CMakeFiles/backtrace.dir/atomic.c.o.provides

third-party/libbacktrace/CMakeFiles/backtrace.dir/atomic.c.o.provides.build: third-party/libbacktrace/CMakeFiles/backtrace.dir/atomic.c.o


third-party/libbacktrace/CMakeFiles/backtrace.dir/fileline.c.o: third-party/libbacktrace/CMakeFiles/backtrace.dir/flags.make
third-party/libbacktrace/CMakeFiles/backtrace.dir/fileline.c.o: ../third-party/libbacktrace/fileline.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object third-party/libbacktrace/CMakeFiles/backtrace.dir/fileline.c.o"
	cd /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/build/third-party/libbacktrace && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/backtrace.dir/fileline.c.o   -c /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/libbacktrace/fileline.c

third-party/libbacktrace/CMakeFiles/backtrace.dir/fileline.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/backtrace.dir/fileline.c.i"
	cd /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/build/third-party/libbacktrace && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/libbacktrace/fileline.c > CMakeFiles/backtrace.dir/fileline.c.i

third-party/libbacktrace/CMakeFiles/backtrace.dir/fileline.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/backtrace.dir/fileline.c.s"
	cd /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/build/third-party/libbacktrace && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/libbacktrace/fileline.c -o CMakeFiles/backtrace.dir/fileline.c.s

third-party/libbacktrace/CMakeFiles/backtrace.dir/fileline.c.o.requires:

.PHONY : third-party/libbacktrace/CMakeFiles/backtrace.dir/fileline.c.o.requires

third-party/libbacktrace/CMakeFiles/backtrace.dir/fileline.c.o.provides: third-party/libbacktrace/CMakeFiles/backtrace.dir/fileline.c.o.requires
	$(MAKE) -f third-party/libbacktrace/CMakeFiles/backtrace.dir/build.make third-party/libbacktrace/CMakeFiles/backtrace.dir/fileline.c.o.provides.build
.PHONY : third-party/libbacktrace/CMakeFiles/backtrace.dir/fileline.c.o.provides

third-party/libbacktrace/CMakeFiles/backtrace.dir/fileline.c.o.provides.build: third-party/libbacktrace/CMakeFiles/backtrace.dir/fileline.c.o


third-party/libbacktrace/CMakeFiles/backtrace.dir/posix.c.o: third-party/libbacktrace/CMakeFiles/backtrace.dir/flags.make
third-party/libbacktrace/CMakeFiles/backtrace.dir/posix.c.o: ../third-party/libbacktrace/posix.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object third-party/libbacktrace/CMakeFiles/backtrace.dir/posix.c.o"
	cd /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/build/third-party/libbacktrace && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/backtrace.dir/posix.c.o   -c /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/libbacktrace/posix.c

third-party/libbacktrace/CMakeFiles/backtrace.dir/posix.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/backtrace.dir/posix.c.i"
	cd /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/build/third-party/libbacktrace && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/libbacktrace/posix.c > CMakeFiles/backtrace.dir/posix.c.i

third-party/libbacktrace/CMakeFiles/backtrace.dir/posix.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/backtrace.dir/posix.c.s"
	cd /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/build/third-party/libbacktrace && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/libbacktrace/posix.c -o CMakeFiles/backtrace.dir/posix.c.s

third-party/libbacktrace/CMakeFiles/backtrace.dir/posix.c.o.requires:

.PHONY : third-party/libbacktrace/CMakeFiles/backtrace.dir/posix.c.o.requires

third-party/libbacktrace/CMakeFiles/backtrace.dir/posix.c.o.provides: third-party/libbacktrace/CMakeFiles/backtrace.dir/posix.c.o.requires
	$(MAKE) -f third-party/libbacktrace/CMakeFiles/backtrace.dir/build.make third-party/libbacktrace/CMakeFiles/backtrace.dir/posix.c.o.provides.build
.PHONY : third-party/libbacktrace/CMakeFiles/backtrace.dir/posix.c.o.provides

third-party/libbacktrace/CMakeFiles/backtrace.dir/posix.c.o.provides.build: third-party/libbacktrace/CMakeFiles/backtrace.dir/posix.c.o


third-party/libbacktrace/CMakeFiles/backtrace.dir/print.c.o: third-party/libbacktrace/CMakeFiles/backtrace.dir/flags.make
third-party/libbacktrace/CMakeFiles/backtrace.dir/print.c.o: ../third-party/libbacktrace/print.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object third-party/libbacktrace/CMakeFiles/backtrace.dir/print.c.o"
	cd /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/build/third-party/libbacktrace && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/backtrace.dir/print.c.o   -c /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/libbacktrace/print.c

third-party/libbacktrace/CMakeFiles/backtrace.dir/print.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/backtrace.dir/print.c.i"
	cd /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/build/third-party/libbacktrace && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/libbacktrace/print.c > CMakeFiles/backtrace.dir/print.c.i

third-party/libbacktrace/CMakeFiles/backtrace.dir/print.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/backtrace.dir/print.c.s"
	cd /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/build/third-party/libbacktrace && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/libbacktrace/print.c -o CMakeFiles/backtrace.dir/print.c.s

third-party/libbacktrace/CMakeFiles/backtrace.dir/print.c.o.requires:

.PHONY : third-party/libbacktrace/CMakeFiles/backtrace.dir/print.c.o.requires

third-party/libbacktrace/CMakeFiles/backtrace.dir/print.c.o.provides: third-party/libbacktrace/CMakeFiles/backtrace.dir/print.c.o.requires
	$(MAKE) -f third-party/libbacktrace/CMakeFiles/backtrace.dir/build.make third-party/libbacktrace/CMakeFiles/backtrace.dir/print.c.o.provides.build
.PHONY : third-party/libbacktrace/CMakeFiles/backtrace.dir/print.c.o.provides

third-party/libbacktrace/CMakeFiles/backtrace.dir/print.c.o.provides.build: third-party/libbacktrace/CMakeFiles/backtrace.dir/print.c.o


third-party/libbacktrace/CMakeFiles/backtrace.dir/sort.c.o: third-party/libbacktrace/CMakeFiles/backtrace.dir/flags.make
third-party/libbacktrace/CMakeFiles/backtrace.dir/sort.c.o: ../third-party/libbacktrace/sort.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building C object third-party/libbacktrace/CMakeFiles/backtrace.dir/sort.c.o"
	cd /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/build/third-party/libbacktrace && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/backtrace.dir/sort.c.o   -c /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/libbacktrace/sort.c

third-party/libbacktrace/CMakeFiles/backtrace.dir/sort.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/backtrace.dir/sort.c.i"
	cd /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/build/third-party/libbacktrace && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/libbacktrace/sort.c > CMakeFiles/backtrace.dir/sort.c.i

third-party/libbacktrace/CMakeFiles/backtrace.dir/sort.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/backtrace.dir/sort.c.s"
	cd /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/build/third-party/libbacktrace && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/libbacktrace/sort.c -o CMakeFiles/backtrace.dir/sort.c.s

third-party/libbacktrace/CMakeFiles/backtrace.dir/sort.c.o.requires:

.PHONY : third-party/libbacktrace/CMakeFiles/backtrace.dir/sort.c.o.requires

third-party/libbacktrace/CMakeFiles/backtrace.dir/sort.c.o.provides: third-party/libbacktrace/CMakeFiles/backtrace.dir/sort.c.o.requires
	$(MAKE) -f third-party/libbacktrace/CMakeFiles/backtrace.dir/build.make third-party/libbacktrace/CMakeFiles/backtrace.dir/sort.c.o.provides.build
.PHONY : third-party/libbacktrace/CMakeFiles/backtrace.dir/sort.c.o.provides

third-party/libbacktrace/CMakeFiles/backtrace.dir/sort.c.o.provides.build: third-party/libbacktrace/CMakeFiles/backtrace.dir/sort.c.o


third-party/libbacktrace/CMakeFiles/backtrace.dir/state.c.o: third-party/libbacktrace/CMakeFiles/backtrace.dir/flags.make
third-party/libbacktrace/CMakeFiles/backtrace.dir/state.c.o: ../third-party/libbacktrace/state.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building C object third-party/libbacktrace/CMakeFiles/backtrace.dir/state.c.o"
	cd /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/build/third-party/libbacktrace && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/backtrace.dir/state.c.o   -c /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/libbacktrace/state.c

third-party/libbacktrace/CMakeFiles/backtrace.dir/state.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/backtrace.dir/state.c.i"
	cd /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/build/third-party/libbacktrace && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/libbacktrace/state.c > CMakeFiles/backtrace.dir/state.c.i

third-party/libbacktrace/CMakeFiles/backtrace.dir/state.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/backtrace.dir/state.c.s"
	cd /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/build/third-party/libbacktrace && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/libbacktrace/state.c -o CMakeFiles/backtrace.dir/state.c.s

third-party/libbacktrace/CMakeFiles/backtrace.dir/state.c.o.requires:

.PHONY : third-party/libbacktrace/CMakeFiles/backtrace.dir/state.c.o.requires

third-party/libbacktrace/CMakeFiles/backtrace.dir/state.c.o.provides: third-party/libbacktrace/CMakeFiles/backtrace.dir/state.c.o.requires
	$(MAKE) -f third-party/libbacktrace/CMakeFiles/backtrace.dir/build.make third-party/libbacktrace/CMakeFiles/backtrace.dir/state.c.o.provides.build
.PHONY : third-party/libbacktrace/CMakeFiles/backtrace.dir/state.c.o.provides

third-party/libbacktrace/CMakeFiles/backtrace.dir/state.c.o.provides.build: third-party/libbacktrace/CMakeFiles/backtrace.dir/state.c.o


# Object files for target backtrace
backtrace_OBJECTS = \
"CMakeFiles/backtrace.dir/backtrace.c.o" \
"CMakeFiles/backtrace.dir/simple.c.o" \
"CMakeFiles/backtrace.dir/unknown.c.o" \
"CMakeFiles/backtrace.dir/mmapio.c.o" \
"CMakeFiles/backtrace.dir/mmap.c.o" \
"CMakeFiles/backtrace.dir/atomic.c.o" \
"CMakeFiles/backtrace.dir/fileline.c.o" \
"CMakeFiles/backtrace.dir/posix.c.o" \
"CMakeFiles/backtrace.dir/print.c.o" \
"CMakeFiles/backtrace.dir/sort.c.o" \
"CMakeFiles/backtrace.dir/state.c.o"

# External object files for target backtrace
backtrace_EXTERNAL_OBJECTS =

third-party/libbacktrace/libbacktrace.a: third-party/libbacktrace/CMakeFiles/backtrace.dir/backtrace.c.o
third-party/libbacktrace/libbacktrace.a: third-party/libbacktrace/CMakeFiles/backtrace.dir/simple.c.o
third-party/libbacktrace/libbacktrace.a: third-party/libbacktrace/CMakeFiles/backtrace.dir/unknown.c.o
third-party/libbacktrace/libbacktrace.a: third-party/libbacktrace/CMakeFiles/backtrace.dir/mmapio.c.o
third-party/libbacktrace/libbacktrace.a: third-party/libbacktrace/CMakeFiles/backtrace.dir/mmap.c.o
third-party/libbacktrace/libbacktrace.a: third-party/libbacktrace/CMakeFiles/backtrace.dir/atomic.c.o
third-party/libbacktrace/libbacktrace.a: third-party/libbacktrace/CMakeFiles/backtrace.dir/fileline.c.o
third-party/libbacktrace/libbacktrace.a: third-party/libbacktrace/CMakeFiles/backtrace.dir/posix.c.o
third-party/libbacktrace/libbacktrace.a: third-party/libbacktrace/CMakeFiles/backtrace.dir/print.c.o
third-party/libbacktrace/libbacktrace.a: third-party/libbacktrace/CMakeFiles/backtrace.dir/sort.c.o
third-party/libbacktrace/libbacktrace.a: third-party/libbacktrace/CMakeFiles/backtrace.dir/state.c.o
third-party/libbacktrace/libbacktrace.a: third-party/libbacktrace/CMakeFiles/backtrace.dir/build.make
third-party/libbacktrace/libbacktrace.a: third-party/libbacktrace/CMakeFiles/backtrace.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Linking C static library libbacktrace.a"
	cd /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/build/third-party/libbacktrace && $(CMAKE_COMMAND) -P CMakeFiles/backtrace.dir/cmake_clean_target.cmake
	cd /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/build/third-party/libbacktrace && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/backtrace.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
third-party/libbacktrace/CMakeFiles/backtrace.dir/build: third-party/libbacktrace/libbacktrace.a

.PHONY : third-party/libbacktrace/CMakeFiles/backtrace.dir/build

third-party/libbacktrace/CMakeFiles/backtrace.dir/requires: third-party/libbacktrace/CMakeFiles/backtrace.dir/backtrace.c.o.requires
third-party/libbacktrace/CMakeFiles/backtrace.dir/requires: third-party/libbacktrace/CMakeFiles/backtrace.dir/simple.c.o.requires
third-party/libbacktrace/CMakeFiles/backtrace.dir/requires: third-party/libbacktrace/CMakeFiles/backtrace.dir/unknown.c.o.requires
third-party/libbacktrace/CMakeFiles/backtrace.dir/requires: third-party/libbacktrace/CMakeFiles/backtrace.dir/mmapio.c.o.requires
third-party/libbacktrace/CMakeFiles/backtrace.dir/requires: third-party/libbacktrace/CMakeFiles/backtrace.dir/mmap.c.o.requires
third-party/libbacktrace/CMakeFiles/backtrace.dir/requires: third-party/libbacktrace/CMakeFiles/backtrace.dir/atomic.c.o.requires
third-party/libbacktrace/CMakeFiles/backtrace.dir/requires: third-party/libbacktrace/CMakeFiles/backtrace.dir/fileline.c.o.requires
third-party/libbacktrace/CMakeFiles/backtrace.dir/requires: third-party/libbacktrace/CMakeFiles/backtrace.dir/posix.c.o.requires
third-party/libbacktrace/CMakeFiles/backtrace.dir/requires: third-party/libbacktrace/CMakeFiles/backtrace.dir/print.c.o.requires
third-party/libbacktrace/CMakeFiles/backtrace.dir/requires: third-party/libbacktrace/CMakeFiles/backtrace.dir/sort.c.o.requires
third-party/libbacktrace/CMakeFiles/backtrace.dir/requires: third-party/libbacktrace/CMakeFiles/backtrace.dir/state.c.o.requires

.PHONY : third-party/libbacktrace/CMakeFiles/backtrace.dir/requires

third-party/libbacktrace/CMakeFiles/backtrace.dir/clean:
	cd /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/build/third-party/libbacktrace && $(CMAKE_COMMAND) -P CMakeFiles/backtrace.dir/cmake_clean.cmake
.PHONY : third-party/libbacktrace/CMakeFiles/backtrace.dir/clean

third-party/libbacktrace/CMakeFiles/backtrace.dir/depend:
	cd /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/libbacktrace /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/build /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/build/third-party/libbacktrace /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/build/third-party/libbacktrace/CMakeFiles/backtrace.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : third-party/libbacktrace/CMakeFiles/backtrace.dir/depend
