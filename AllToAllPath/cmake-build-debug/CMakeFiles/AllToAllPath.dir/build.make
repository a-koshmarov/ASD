# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.8

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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2017.2.2\bin\cmake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2017.2.2\bin\cmake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\ITMO\ASD\AllToAllPath

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\ITMO\ASD\AllToAllPath\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/AllToAllPath.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/AllToAllPath.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/AllToAllPath.dir/flags.make

CMakeFiles/AllToAllPath.dir/main.cpp.obj: CMakeFiles/AllToAllPath.dir/flags.make
CMakeFiles/AllToAllPath.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\ITMO\ASD\AllToAllPath\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/AllToAllPath.dir/main.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\AllToAllPath.dir\main.cpp.obj -c C:\ITMO\ASD\AllToAllPath\main.cpp

CMakeFiles/AllToAllPath.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AllToAllPath.dir/main.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\ITMO\ASD\AllToAllPath\main.cpp > CMakeFiles\AllToAllPath.dir\main.cpp.i

CMakeFiles/AllToAllPath.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AllToAllPath.dir/main.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\ITMO\ASD\AllToAllPath\main.cpp -o CMakeFiles\AllToAllPath.dir\main.cpp.s

CMakeFiles/AllToAllPath.dir/main.cpp.obj.requires:

.PHONY : CMakeFiles/AllToAllPath.dir/main.cpp.obj.requires

CMakeFiles/AllToAllPath.dir/main.cpp.obj.provides: CMakeFiles/AllToAllPath.dir/main.cpp.obj.requires
	$(MAKE) -f CMakeFiles\AllToAllPath.dir\build.make CMakeFiles/AllToAllPath.dir/main.cpp.obj.provides.build
.PHONY : CMakeFiles/AllToAllPath.dir/main.cpp.obj.provides

CMakeFiles/AllToAllPath.dir/main.cpp.obj.provides.build: CMakeFiles/AllToAllPath.dir/main.cpp.obj


# Object files for target AllToAllPath
AllToAllPath_OBJECTS = \
"CMakeFiles/AllToAllPath.dir/main.cpp.obj"

# External object files for target AllToAllPath
AllToAllPath_EXTERNAL_OBJECTS =

AllToAllPath.exe: CMakeFiles/AllToAllPath.dir/main.cpp.obj
AllToAllPath.exe: CMakeFiles/AllToAllPath.dir/build.make
AllToAllPath.exe: CMakeFiles/AllToAllPath.dir/linklibs.rsp
AllToAllPath.exe: CMakeFiles/AllToAllPath.dir/objects1.rsp
AllToAllPath.exe: CMakeFiles/AllToAllPath.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\ITMO\ASD\AllToAllPath\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable AllToAllPath.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\AllToAllPath.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/AllToAllPath.dir/build: AllToAllPath.exe

.PHONY : CMakeFiles/AllToAllPath.dir/build

CMakeFiles/AllToAllPath.dir/requires: CMakeFiles/AllToAllPath.dir/main.cpp.obj.requires

.PHONY : CMakeFiles/AllToAllPath.dir/requires

CMakeFiles/AllToAllPath.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\AllToAllPath.dir\cmake_clean.cmake
.PHONY : CMakeFiles/AllToAllPath.dir/clean

CMakeFiles/AllToAllPath.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\ITMO\ASD\AllToAllPath C:\ITMO\ASD\AllToAllPath C:\ITMO\ASD\AllToAllPath\cmake-build-debug C:\ITMO\ASD\AllToAllPath\cmake-build-debug C:\ITMO\ASD\AllToAllPath\cmake-build-debug\CMakeFiles\AllToAllPath.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/AllToAllPath.dir/depend

