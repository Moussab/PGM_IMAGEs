# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

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
CMAKE_COMMAND = /usr/locale/Clion/bin/cmake/bin/cmake

# The command to remove a file.
RM = /usr/locale/Clion/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/amrine/CLionProjects/PGM

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/amrine/CLionProjects/PGM/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/PGM.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/PGM.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/PGM.dir/flags.make

CMakeFiles/PGM.dir/main.c.o: CMakeFiles/PGM.dir/flags.make
CMakeFiles/PGM.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/amrine/CLionProjects/PGM/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/PGM.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/PGM.dir/main.c.o   -c /home/amrine/CLionProjects/PGM/main.c

CMakeFiles/PGM.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/PGM.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/amrine/CLionProjects/PGM/main.c > CMakeFiles/PGM.dir/main.c.i

CMakeFiles/PGM.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/PGM.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/amrine/CLionProjects/PGM/main.c -o CMakeFiles/PGM.dir/main.c.s

CMakeFiles/PGM.dir/main.c.o.requires:

.PHONY : CMakeFiles/PGM.dir/main.c.o.requires

CMakeFiles/PGM.dir/main.c.o.provides: CMakeFiles/PGM.dir/main.c.o.requires
	$(MAKE) -f CMakeFiles/PGM.dir/build.make CMakeFiles/PGM.dir/main.c.o.provides.build
.PHONY : CMakeFiles/PGM.dir/main.c.o.provides

CMakeFiles/PGM.dir/main.c.o.provides.build: CMakeFiles/PGM.dir/main.c.o


CMakeFiles/PGM.dir/lib.c.o: CMakeFiles/PGM.dir/flags.make
CMakeFiles/PGM.dir/lib.c.o: ../lib.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/amrine/CLionProjects/PGM/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/PGM.dir/lib.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/PGM.dir/lib.c.o   -c /home/amrine/CLionProjects/PGM/lib.c

CMakeFiles/PGM.dir/lib.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/PGM.dir/lib.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/amrine/CLionProjects/PGM/lib.c > CMakeFiles/PGM.dir/lib.c.i

CMakeFiles/PGM.dir/lib.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/PGM.dir/lib.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/amrine/CLionProjects/PGM/lib.c -o CMakeFiles/PGM.dir/lib.c.s

CMakeFiles/PGM.dir/lib.c.o.requires:

.PHONY : CMakeFiles/PGM.dir/lib.c.o.requires

CMakeFiles/PGM.dir/lib.c.o.provides: CMakeFiles/PGM.dir/lib.c.o.requires
	$(MAKE) -f CMakeFiles/PGM.dir/build.make CMakeFiles/PGM.dir/lib.c.o.provides.build
.PHONY : CMakeFiles/PGM.dir/lib.c.o.provides

CMakeFiles/PGM.dir/lib.c.o.provides.build: CMakeFiles/PGM.dir/lib.c.o


# Object files for target PGM
PGM_OBJECTS = \
"CMakeFiles/PGM.dir/main.c.o" \
"CMakeFiles/PGM.dir/lib.c.o"

# External object files for target PGM
PGM_EXTERNAL_OBJECTS =

PGM: CMakeFiles/PGM.dir/main.c.o
PGM: CMakeFiles/PGM.dir/lib.c.o
PGM: CMakeFiles/PGM.dir/build.make
PGM: CMakeFiles/PGM.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/amrine/CLionProjects/PGM/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable PGM"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/PGM.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/PGM.dir/build: PGM

.PHONY : CMakeFiles/PGM.dir/build

CMakeFiles/PGM.dir/requires: CMakeFiles/PGM.dir/main.c.o.requires
CMakeFiles/PGM.dir/requires: CMakeFiles/PGM.dir/lib.c.o.requires

.PHONY : CMakeFiles/PGM.dir/requires

CMakeFiles/PGM.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/PGM.dir/cmake_clean.cmake
.PHONY : CMakeFiles/PGM.dir/clean

CMakeFiles/PGM.dir/depend:
	cd /home/amrine/CLionProjects/PGM/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/amrine/CLionProjects/PGM /home/amrine/CLionProjects/PGM /home/amrine/CLionProjects/PGM/cmake-build-debug /home/amrine/CLionProjects/PGM/cmake-build-debug /home/amrine/CLionProjects/PGM/cmake-build-debug/CMakeFiles/PGM.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/PGM.dir/depend

