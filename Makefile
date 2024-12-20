# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.20.5/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.20.5/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/janamzaveri/y3/fyp/fyp-src/reg_alloc_cpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/janamzaveri/y3/fyp/fyp-src/reg_alloc_cpp

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/opt/homebrew/Cellar/cmake/3.20.5/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/opt/homebrew/Cellar/cmake/3.20.5/bin/ccmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/janamzaveri/y3/fyp/fyp-src/reg_alloc_cpp/CMakeFiles /Users/janamzaveri/y3/fyp/fyp-src/reg_alloc_cpp//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/janamzaveri/y3/fyp/fyp-src/reg_alloc_cpp/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named reg_alloc_cpp

# Build rule for target.
reg_alloc_cpp: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 reg_alloc_cpp
.PHONY : reg_alloc_cpp

# fast build rule for target.
reg_alloc_cpp/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/reg_alloc_cpp.dir/build.make CMakeFiles/reg_alloc_cpp.dir/build
.PHONY : reg_alloc_cpp/fast

code_gen.o: code_gen.cpp.o
.PHONY : code_gen.o

# target to build an object file
code_gen.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/reg_alloc_cpp.dir/build.make CMakeFiles/reg_alloc_cpp.dir/code_gen.cpp.o
.PHONY : code_gen.cpp.o

code_gen.i: code_gen.cpp.i
.PHONY : code_gen.i

# target to preprocess a source file
code_gen.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/reg_alloc_cpp.dir/build.make CMakeFiles/reg_alloc_cpp.dir/code_gen.cpp.i
.PHONY : code_gen.cpp.i

code_gen.s: code_gen.cpp.s
.PHONY : code_gen.s

# target to generate assembly for a file
code_gen.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/reg_alloc_cpp.dir/build.make CMakeFiles/reg_alloc_cpp.dir/code_gen.cpp.s
.PHONY : code_gen.cpp.s

color.o: color.cpp.o
.PHONY : color.o

# target to build an object file
color.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/reg_alloc_cpp.dir/build.make CMakeFiles/reg_alloc_cpp.dir/color.cpp.o
.PHONY : color.cpp.o

color.i: color.cpp.i
.PHONY : color.i

# target to preprocess a source file
color.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/reg_alloc_cpp.dir/build.make CMakeFiles/reg_alloc_cpp.dir/color.cpp.i
.PHONY : color.cpp.i

color.s: color.cpp.s
.PHONY : color.s

# target to generate assembly for a file
color.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/reg_alloc_cpp.dir/build.make CMakeFiles/reg_alloc_cpp.dir/color.cpp.s
.PHONY : color.cpp.s

flowgraph.o: flowgraph.cpp.o
.PHONY : flowgraph.o

# target to build an object file
flowgraph.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/reg_alloc_cpp.dir/build.make CMakeFiles/reg_alloc_cpp.dir/flowgraph.cpp.o
.PHONY : flowgraph.cpp.o

flowgraph.i: flowgraph.cpp.i
.PHONY : flowgraph.i

# target to preprocess a source file
flowgraph.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/reg_alloc_cpp.dir/build.make CMakeFiles/reg_alloc_cpp.dir/flowgraph.cpp.i
.PHONY : flowgraph.cpp.i

flowgraph.s: flowgraph.cpp.s
.PHONY : flowgraph.s

# target to generate assembly for a file
flowgraph.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/reg_alloc_cpp.dir/build.make CMakeFiles/reg_alloc_cpp.dir/flowgraph.cpp.s
.PHONY : flowgraph.cpp.s

liveness.o: liveness.cpp.o
.PHONY : liveness.o

# target to build an object file
liveness.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/reg_alloc_cpp.dir/build.make CMakeFiles/reg_alloc_cpp.dir/liveness.cpp.o
.PHONY : liveness.cpp.o

liveness.i: liveness.cpp.i
.PHONY : liveness.i

# target to preprocess a source file
liveness.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/reg_alloc_cpp.dir/build.make CMakeFiles/reg_alloc_cpp.dir/liveness.cpp.i
.PHONY : liveness.cpp.i

liveness.s: liveness.cpp.s
.PHONY : liveness.s

# target to generate assembly for a file
liveness.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/reg_alloc_cpp.dir/build.make CMakeFiles/reg_alloc_cpp.dir/liveness.cpp.s
.PHONY : liveness.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... reg_alloc_cpp"
	@echo "... code_gen.o"
	@echo "... code_gen.i"
	@echo "... code_gen.s"
	@echo "... color.o"
	@echo "... color.i"
	@echo "... color.s"
	@echo "... flowgraph.o"
	@echo "... flowgraph.i"
	@echo "... flowgraph.s"
	@echo "... liveness.o"
	@echo "... liveness.i"
	@echo "... liveness.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

