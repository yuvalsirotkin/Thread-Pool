# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /home/yuval/Desktop/clion-2019.2.5/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/yuval/Desktop/clion-2019.2.5/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/yuval/CLionProjects/OS_ex4

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yuval/CLionProjects/OS_ex4/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/OS_ex4.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/OS_ex4.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/OS_ex4.dir/flags.make

CMakeFiles/OS_ex4.dir/test.c.o: CMakeFiles/OS_ex4.dir/flags.make
CMakeFiles/OS_ex4.dir/test.c.o: ../test.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yuval/CLionProjects/OS_ex4/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/OS_ex4.dir/test.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/OS_ex4.dir/test.c.o   -c /home/yuval/CLionProjects/OS_ex4/test.c

CMakeFiles/OS_ex4.dir/test.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/OS_ex4.dir/test.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/yuval/CLionProjects/OS_ex4/test.c > CMakeFiles/OS_ex4.dir/test.c.i

CMakeFiles/OS_ex4.dir/test.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/OS_ex4.dir/test.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/yuval/CLionProjects/OS_ex4/test.c -o CMakeFiles/OS_ex4.dir/test.c.s

CMakeFiles/OS_ex4.dir/osqueue.c.o: CMakeFiles/OS_ex4.dir/flags.make
CMakeFiles/OS_ex4.dir/osqueue.c.o: ../osqueue.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yuval/CLionProjects/OS_ex4/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/OS_ex4.dir/osqueue.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/OS_ex4.dir/osqueue.c.o   -c /home/yuval/CLionProjects/OS_ex4/osqueue.c

CMakeFiles/OS_ex4.dir/osqueue.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/OS_ex4.dir/osqueue.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/yuval/CLionProjects/OS_ex4/osqueue.c > CMakeFiles/OS_ex4.dir/osqueue.c.i

CMakeFiles/OS_ex4.dir/osqueue.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/OS_ex4.dir/osqueue.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/yuval/CLionProjects/OS_ex4/osqueue.c -o CMakeFiles/OS_ex4.dir/osqueue.c.s

CMakeFiles/OS_ex4.dir/threadPool.c.o: CMakeFiles/OS_ex4.dir/flags.make
CMakeFiles/OS_ex4.dir/threadPool.c.o: ../threadPool.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yuval/CLionProjects/OS_ex4/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/OS_ex4.dir/threadPool.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/OS_ex4.dir/threadPool.c.o   -c /home/yuval/CLionProjects/OS_ex4/threadPool.c

CMakeFiles/OS_ex4.dir/threadPool.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/OS_ex4.dir/threadPool.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/yuval/CLionProjects/OS_ex4/threadPool.c > CMakeFiles/OS_ex4.dir/threadPool.c.i

CMakeFiles/OS_ex4.dir/threadPool.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/OS_ex4.dir/threadPool.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/yuval/CLionProjects/OS_ex4/threadPool.c -o CMakeFiles/OS_ex4.dir/threadPool.c.s

# Object files for target OS_ex4
OS_ex4_OBJECTS = \
"CMakeFiles/OS_ex4.dir/test.c.o" \
"CMakeFiles/OS_ex4.dir/osqueue.c.o" \
"CMakeFiles/OS_ex4.dir/threadPool.c.o"

# External object files for target OS_ex4
OS_ex4_EXTERNAL_OBJECTS =

OS_ex4: CMakeFiles/OS_ex4.dir/test.c.o
OS_ex4: CMakeFiles/OS_ex4.dir/osqueue.c.o
OS_ex4: CMakeFiles/OS_ex4.dir/threadPool.c.o
OS_ex4: CMakeFiles/OS_ex4.dir/build.make
OS_ex4: CMakeFiles/OS_ex4.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/yuval/CLionProjects/OS_ex4/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable OS_ex4"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/OS_ex4.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/OS_ex4.dir/build: OS_ex4

.PHONY : CMakeFiles/OS_ex4.dir/build

CMakeFiles/OS_ex4.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/OS_ex4.dir/cmake_clean.cmake
.PHONY : CMakeFiles/OS_ex4.dir/clean

CMakeFiles/OS_ex4.dir/depend:
	cd /home/yuval/CLionProjects/OS_ex4/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yuval/CLionProjects/OS_ex4 /home/yuval/CLionProjects/OS_ex4 /home/yuval/CLionProjects/OS_ex4/cmake-build-debug /home/yuval/CLionProjects/OS_ex4/cmake-build-debug /home/yuval/CLionProjects/OS_ex4/cmake-build-debug/CMakeFiles/OS_ex4.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/OS_ex4.dir/depend

