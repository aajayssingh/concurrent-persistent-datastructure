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

# Utility rule file for format.

# Include the progress variables for this target.
include third-party/yaml-cpp-0.5.2/CMakeFiles/format.dir/progress.make

third-party/yaml-cpp-0.5.2/CMakeFiles/format:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Running clang-format"
	cd /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/build/third-party/yaml-cpp-0.5.2 && clang-format --style=file -i /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/src/emitterutils.cpp /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/src/stream.cpp /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/src/emitfromevents.cpp /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/src/null.cpp /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/src/emit.cpp /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/src/singledocparser.cpp /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/src/convert.cpp /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/src/memory.cpp /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/src/exp.cpp /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/src/node.cpp /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/src/nodebuilder.cpp /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/src/simplekey.cpp /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/src/emitter.cpp /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/src/emitterstate.cpp /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/src/nodeevents.cpp /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/src/parse.cpp /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/src/node_data.cpp /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/src/scanscalar.cpp /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/src/parser.cpp /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/src/directives.cpp /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/src/binary.cpp /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/src/scantag.cpp /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/src/scantoken.cpp /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/src/regex_yaml.cpp /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/src/ostream_wrapper.cpp /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/src/scanner.cpp /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/src/tag.cpp /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/include/yaml-cpp/exceptions.h /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/include/yaml-cpp/emitter.h /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/include/yaml-cpp/null.h /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/include/yaml-cpp/binary.h /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/include/yaml-cpp/emitterstyle.h /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/include/yaml-cpp/emitfromevents.h /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/include/yaml-cpp/emittermanip.h /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/include/yaml-cpp/anchor.h /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/include/yaml-cpp/dll.h /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/include/yaml-cpp/parser.h /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/include/yaml-cpp/yaml.h /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/include/yaml-cpp/traits.h /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/include/yaml-cpp/node/parse.h /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/include/yaml-cpp/node/ptr.h /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/include/yaml-cpp/node/iterator.h /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/include/yaml-cpp/node/node.h /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/include/yaml-cpp/node/type.h /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/include/yaml-cpp/node/detail/memory.h /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/include/yaml-cpp/node/detail/iterator.h /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/include/yaml-cpp/node/detail/node.h /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/include/yaml-cpp/node/detail/node_data.h /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/include/yaml-cpp/node/detail/bool_type.h /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/include/yaml-cpp/node/detail/node_ref.h /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/include/yaml-cpp/node/detail/node_iterator.h /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/include/yaml-cpp/node/detail/impl.h /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/include/yaml-cpp/node/detail/iterator_fwd.h /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/include/yaml-cpp/node/emit.h /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/include/yaml-cpp/node/impl.h /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/include/yaml-cpp/node/convert.h /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/include/yaml-cpp/stlemitter.h /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/include/yaml-cpp/noncopyable.h /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/include/yaml-cpp/eventhandler.h /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/include/yaml-cpp/contrib/anchordict.h /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/include/yaml-cpp/contrib/graphbuilder.h /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/include/yaml-cpp/ostream_wrapper.h /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/include/yaml-cpp/emitterdef.h /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/include/yaml-cpp/mark.h /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/src/singledocparser.h /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/src/indentation.h /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/src/exp.h /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/src/collectionstack.h /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/src/setting.h /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/src/ptr_stack.h /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/src/nodebuilder.h /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/src/regex_yaml.h /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/src/emitterstate.h /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/src/stream.h /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/src/token.h /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/src/scanner.h /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/src/ptr_vector.h /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/src/streamcharsource.h /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/src/tag.h /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/src/nodeevents.h /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/src/emitterutils.h /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/src/directives.h /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/src/scanscalar.h /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/src/stringsource.h /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/src/scantag.h /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/src/regeximpl.h /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/src/contrib/graphbuilder.cpp /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/src/contrib/graphbuilderadapter.cpp /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/include/yaml-cpp/contrib/anchordict.h /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/include/yaml-cpp/contrib/graphbuilder.h /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/src/contrib/graphbuilderadapter.h /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/util/parse.cpp /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/util/sandbox.cpp /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2/util/read.cpp

format: third-party/yaml-cpp-0.5.2/CMakeFiles/format
format: third-party/yaml-cpp-0.5.2/CMakeFiles/format.dir/build.make

.PHONY : format

# Rule to build all files generated by this target.
third-party/yaml-cpp-0.5.2/CMakeFiles/format.dir/build: format

.PHONY : third-party/yaml-cpp-0.5.2/CMakeFiles/format.dir/build

third-party/yaml-cpp-0.5.2/CMakeFiles/format.dir/clean:
	cd /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/build/third-party/yaml-cpp-0.5.2 && $(CMAKE_COMMAND) -P CMakeFiles/format.dir/cmake_clean.cmake
.PHONY : third-party/yaml-cpp-0.5.2/CMakeFiles/format.dir/clean

third-party/yaml-cpp-0.5.2/CMakeFiles/format.dir/depend:
	cd /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/third-party/yaml-cpp-0.5.2 /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/build /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/build/third-party/yaml-cpp-0.5.2 /home/ajay/intern-ws/mnemosyne-gcc-alps/usermode/library/pmalloc/include/alps/build/third-party/yaml-cpp-0.5.2/CMakeFiles/format.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : third-party/yaml-cpp-0.5.2/CMakeFiles/format.dir/depend

