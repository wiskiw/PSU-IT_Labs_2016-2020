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
CMAKE_SOURCE_DIR = C:\Users\WiskiW\Desktop\TODO\oap2_8\ts1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\WiskiW\Desktop\TODO\oap2_8\ts1\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/ts1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ts1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ts1.dir/flags.make

CMakeFiles/ts1.dir/main.cpp.obj: CMakeFiles/ts1.dir/flags.make
CMakeFiles/ts1.dir/main.cpp.obj: CMakeFiles/ts1.dir/includes_CXX.rsp
CMakeFiles/ts1.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\WiskiW\Desktop\TODO\oap2_8\ts1\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ts1.dir/main.cpp.obj"
	C:\MinGW\bin\g++.exe   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\ts1.dir\main.cpp.obj -c C:\Users\WiskiW\Desktop\TODO\oap2_8\ts1\main.cpp

CMakeFiles/ts1.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ts1.dir/main.cpp.i"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\WiskiW\Desktop\TODO\oap2_8\ts1\main.cpp > CMakeFiles\ts1.dir\main.cpp.i

CMakeFiles/ts1.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ts1.dir/main.cpp.s"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\WiskiW\Desktop\TODO\oap2_8\ts1\main.cpp -o CMakeFiles\ts1.dir\main.cpp.s

CMakeFiles/ts1.dir/main.cpp.obj.requires:

.PHONY : CMakeFiles/ts1.dir/main.cpp.obj.requires

CMakeFiles/ts1.dir/main.cpp.obj.provides: CMakeFiles/ts1.dir/main.cpp.obj.requires
	$(MAKE) -f CMakeFiles\ts1.dir\build.make CMakeFiles/ts1.dir/main.cpp.obj.provides.build
.PHONY : CMakeFiles/ts1.dir/main.cpp.obj.provides

CMakeFiles/ts1.dir/main.cpp.obj.provides.build: CMakeFiles/ts1.dir/main.cpp.obj


CMakeFiles/ts1.dir/StackList.cpp.obj: CMakeFiles/ts1.dir/flags.make
CMakeFiles/ts1.dir/StackList.cpp.obj: CMakeFiles/ts1.dir/includes_CXX.rsp
CMakeFiles/ts1.dir/StackList.cpp.obj: ../StackList.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\WiskiW\Desktop\TODO\oap2_8\ts1\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/ts1.dir/StackList.cpp.obj"
	C:\MinGW\bin\g++.exe   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\ts1.dir\StackList.cpp.obj -c C:\Users\WiskiW\Desktop\TODO\oap2_8\ts1\StackList.cpp

CMakeFiles/ts1.dir/StackList.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ts1.dir/StackList.cpp.i"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\WiskiW\Desktop\TODO\oap2_8\ts1\StackList.cpp > CMakeFiles\ts1.dir\StackList.cpp.i

CMakeFiles/ts1.dir/StackList.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ts1.dir/StackList.cpp.s"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\WiskiW\Desktop\TODO\oap2_8\ts1\StackList.cpp -o CMakeFiles\ts1.dir\StackList.cpp.s

CMakeFiles/ts1.dir/StackList.cpp.obj.requires:

.PHONY : CMakeFiles/ts1.dir/StackList.cpp.obj.requires

CMakeFiles/ts1.dir/StackList.cpp.obj.provides: CMakeFiles/ts1.dir/StackList.cpp.obj.requires
	$(MAKE) -f CMakeFiles\ts1.dir\build.make CMakeFiles/ts1.dir/StackList.cpp.obj.provides.build
.PHONY : CMakeFiles/ts1.dir/StackList.cpp.obj.provides

CMakeFiles/ts1.dir/StackList.cpp.obj.provides.build: CMakeFiles/ts1.dir/StackList.cpp.obj


# Object files for target ts1
ts1_OBJECTS = \
"CMakeFiles/ts1.dir/main.cpp.obj" \
"CMakeFiles/ts1.dir/StackList.cpp.obj"

# External object files for target ts1
ts1_EXTERNAL_OBJECTS =

ts1.exe: CMakeFiles/ts1.dir/main.cpp.obj
ts1.exe: CMakeFiles/ts1.dir/StackList.cpp.obj
ts1.exe: CMakeFiles/ts1.dir/build.make
ts1.exe: CMakeFiles/ts1.dir/linklibs.rsp
ts1.exe: CMakeFiles/ts1.dir/objects1.rsp
ts1.exe: CMakeFiles/ts1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\WiskiW\Desktop\TODO\oap2_8\ts1\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable ts1.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\ts1.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ts1.dir/build: ts1.exe

.PHONY : CMakeFiles/ts1.dir/build

CMakeFiles/ts1.dir/requires: CMakeFiles/ts1.dir/main.cpp.obj.requires
CMakeFiles/ts1.dir/requires: CMakeFiles/ts1.dir/StackList.cpp.obj.requires

.PHONY : CMakeFiles/ts1.dir/requires

CMakeFiles/ts1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\ts1.dir\cmake_clean.cmake
.PHONY : CMakeFiles/ts1.dir/clean

CMakeFiles/ts1.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\WiskiW\Desktop\TODO\oap2_8\ts1 C:\Users\WiskiW\Desktop\TODO\oap2_8\ts1 C:\Users\WiskiW\Desktop\TODO\oap2_8\ts1\cmake-build-debug C:\Users\WiskiW\Desktop\TODO\oap2_8\ts1\cmake-build-debug C:\Users\WiskiW\Desktop\TODO\oap2_8\ts1\cmake-build-debug\CMakeFiles\ts1.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ts1.dir/depend

