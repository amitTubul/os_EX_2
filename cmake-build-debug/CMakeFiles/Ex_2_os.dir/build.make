# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

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
CMAKE_COMMAND = /snap/clion/234/bin/cmake/linux/x64/bin/cmake

# The command to remove a file.
RM = /snap/clion/234/bin/cmake/linux/x64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/itamarq/CLionProjects/C/os_EX_2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/itamarq/CLionProjects/C/os_EX_2/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Ex_2_os.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Ex_2_os.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Ex_2_os.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Ex_2_os.dir/flags.make

CMakeFiles/Ex_2_os.dir/cmp.c.o: CMakeFiles/Ex_2_os.dir/flags.make
CMakeFiles/Ex_2_os.dir/cmp.c.o: /home/itamarq/CLionProjects/C/os_EX_2/cmp.c
CMakeFiles/Ex_2_os.dir/cmp.c.o: CMakeFiles/Ex_2_os.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/itamarq/CLionProjects/C/os_EX_2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Ex_2_os.dir/cmp.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/Ex_2_os.dir/cmp.c.o -MF CMakeFiles/Ex_2_os.dir/cmp.c.o.d -o CMakeFiles/Ex_2_os.dir/cmp.c.o -c /home/itamarq/CLionProjects/C/os_EX_2/cmp.c

CMakeFiles/Ex_2_os.dir/cmp.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Ex_2_os.dir/cmp.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/itamarq/CLionProjects/C/os_EX_2/cmp.c > CMakeFiles/Ex_2_os.dir/cmp.c.i

CMakeFiles/Ex_2_os.dir/cmp.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Ex_2_os.dir/cmp.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/itamarq/CLionProjects/C/os_EX_2/cmp.c -o CMakeFiles/Ex_2_os.dir/cmp.c.s

CMakeFiles/Ex_2_os.dir/copy.c.o: CMakeFiles/Ex_2_os.dir/flags.make
CMakeFiles/Ex_2_os.dir/copy.c.o: /home/itamarq/CLionProjects/C/os_EX_2/copy.c
CMakeFiles/Ex_2_os.dir/copy.c.o: CMakeFiles/Ex_2_os.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/itamarq/CLionProjects/C/os_EX_2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/Ex_2_os.dir/copy.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/Ex_2_os.dir/copy.c.o -MF CMakeFiles/Ex_2_os.dir/copy.c.o.d -o CMakeFiles/Ex_2_os.dir/copy.c.o -c /home/itamarq/CLionProjects/C/os_EX_2/copy.c

CMakeFiles/Ex_2_os.dir/copy.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Ex_2_os.dir/copy.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/itamarq/CLionProjects/C/os_EX_2/copy.c > CMakeFiles/Ex_2_os.dir/copy.c.i

CMakeFiles/Ex_2_os.dir/copy.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Ex_2_os.dir/copy.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/itamarq/CLionProjects/C/os_EX_2/copy.c -o CMakeFiles/Ex_2_os.dir/copy.c.s

CMakeFiles/Ex_2_os.dir/stshell.c.o: CMakeFiles/Ex_2_os.dir/flags.make
CMakeFiles/Ex_2_os.dir/stshell.c.o: /home/itamarq/CLionProjects/C/os_EX_2/stshell.c
CMakeFiles/Ex_2_os.dir/stshell.c.o: CMakeFiles/Ex_2_os.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/itamarq/CLionProjects/C/os_EX_2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/Ex_2_os.dir/stshell.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/Ex_2_os.dir/stshell.c.o -MF CMakeFiles/Ex_2_os.dir/stshell.c.o.d -o CMakeFiles/Ex_2_os.dir/stshell.c.o -c /home/itamarq/CLionProjects/C/os_EX_2/stshell.c

CMakeFiles/Ex_2_os.dir/stshell.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Ex_2_os.dir/stshell.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/itamarq/CLionProjects/C/os_EX_2/stshell.c > CMakeFiles/Ex_2_os.dir/stshell.c.i

CMakeFiles/Ex_2_os.dir/stshell.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Ex_2_os.dir/stshell.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/itamarq/CLionProjects/C/os_EX_2/stshell.c -o CMakeFiles/Ex_2_os.dir/stshell.c.s

# Object files for target Ex_2_os
Ex_2_os_OBJECTS = \
"CMakeFiles/Ex_2_os.dir/cmp.c.o" \
"CMakeFiles/Ex_2_os.dir/copy.c.o" \
"CMakeFiles/Ex_2_os.dir/stshell.c.o"

# External object files for target Ex_2_os
Ex_2_os_EXTERNAL_OBJECTS =

Ex_2_os: CMakeFiles/Ex_2_os.dir/cmp.c.o
Ex_2_os: CMakeFiles/Ex_2_os.dir/copy.c.o
Ex_2_os: CMakeFiles/Ex_2_os.dir/stshell.c.o
Ex_2_os: CMakeFiles/Ex_2_os.dir/build.make
Ex_2_os: CMakeFiles/Ex_2_os.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/itamarq/CLionProjects/C/os_EX_2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable Ex_2_os"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Ex_2_os.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Ex_2_os.dir/build: Ex_2_os
.PHONY : CMakeFiles/Ex_2_os.dir/build

CMakeFiles/Ex_2_os.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Ex_2_os.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Ex_2_os.dir/clean

CMakeFiles/Ex_2_os.dir/depend:
	cd /home/itamarq/CLionProjects/C/os_EX_2/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/itamarq/CLionProjects/C/os_EX_2 /home/itamarq/CLionProjects/C/os_EX_2 /home/itamarq/CLionProjects/C/os_EX_2/cmake-build-debug /home/itamarq/CLionProjects/C/os_EX_2/cmake-build-debug /home/itamarq/CLionProjects/C/os_EX_2/cmake-build-debug/CMakeFiles/Ex_2_os.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Ex_2_os.dir/depend

