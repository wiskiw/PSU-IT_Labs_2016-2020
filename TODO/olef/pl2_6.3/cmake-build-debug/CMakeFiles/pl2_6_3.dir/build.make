# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.7

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2017.1.1\bin\cmake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2017.1.1\bin\cmake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\WiskiW\Desktop\TODO\olef\pl2_6.3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\WiskiW\Desktop\TODO\olef\pl2_6.3\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/pl2_6_3.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/pl2_6_3.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/pl2_6_3.dir/flags.make

CMakeFiles/pl2_6_3.dir/main.cpp.obj: CMakeFiles/pl2_6_3.dir/flags.make
CMakeFiles/pl2_6_3.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\WiskiW\Desktop\TODO\olef\pl2_6.3\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/pl2_6_3.dir/main.cpp.obj"
	C:\MinGW\bin\g++.exe   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\pl2_6_3.dir\main.cpp.obj -c C:\Users\WiskiW\Desktop\TODO\olef\pl2_6.3\main.cpp

CMakeFiles/pl2_6_3.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pl2_6_3.dir/main.cpp.i"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\WiskiW\Desktop\TODO\olef\pl2_6.3\main.cpp > CMakeFiles\pl2_6_3.dir\main.cpp.i

CMakeFiles/pl2_6_3.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pl2_6_3.dir/main.cpp.s"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\WiskiW\Desktop\TODO\olef\pl2_6.3\main.cpp -o CMakeFiles\pl2_6_3.dir\main.cpp.s

CMakeFiles/pl2_6_3.dir/main.cpp.obj.requires:

.PHONY : CMakeFiles/pl2_6_3.dir/main.cpp.obj.requires

CMakeFiles/pl2_6_3.dir/main.cpp.obj.provides: CMakeFiles/pl2_6_3.dir/main.cpp.obj.requires
	$(MAKE) -f CMakeFiles\pl2_6_3.dir\build.make CMakeFiles/pl2_6_3.dir/main.cpp.obj.provides.build
.PHONY : CMakeFiles/pl2_6_3.dir/main.cpp.obj.provides

CMakeFiles/pl2_6_3.dir/main.cpp.obj.provides.build: CMakeFiles/pl2_6_3.dir/main.cpp.obj


# Object files for target pl2_6_3
pl2_6_3_OBJECTS = \
"CMakeFiles/pl2_6_3.dir/main.cpp.obj"

# External object files for target pl2_6_3
pl2_6_3_EXTERNAL_OBJECTS =

pl2_6_3.exe: CMakeFiles/pl2_6_3.dir/main.cpp.obj
pl2_6_3.exe: CMakeFiles/pl2_6_3.dir/build.make
pl2_6_3.exe: CMakeFiles/pl2_6_3.dir/linklibs.rsp
pl2_6_3.exe: CMakeFiles/pl2_6_3.dir/objects1.rsp
pl2_6_3.exe: CMakeFiles/pl2_6_3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\WiskiW\Desktop\TODO\olef\pl2_6.3\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable pl2_6_3.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\pl2_6_3.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/pl2_6_3.dir/build: pl2_6_3.exe

.PHONY : CMakeFiles/pl2_6_3.dir/build

CMakeFiles/pl2_6_3.dir/requires: CMakeFiles/pl2_6_3.dir/main.cpp.obj.requires

.PHONY : CMakeFiles/pl2_6_3.dir/requires

CMakeFiles/pl2_6_3.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\pl2_6_3.dir\cmake_clean.cmake
.PHONY : CMakeFiles/pl2_6_3.dir/clean

CMakeFiles/pl2_6_3.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\WiskiW\Desktop\TODO\olef\pl2_6.3 C:\Users\WiskiW\Desktop\TODO\olef\pl2_6.3 C:\Users\WiskiW\Desktop\TODO\olef\pl2_6.3\cmake-build-debug C:\Users\WiskiW\Desktop\TODO\olef\pl2_6.3\cmake-build-debug C:\Users\WiskiW\Desktop\TODO\olef\pl2_6.3\cmake-build-debug\CMakeFiles\pl2_6_3.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/pl2_6_3.dir/depend

