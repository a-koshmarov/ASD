# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.9

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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2017.3.1\bin\cmake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2017.3.1\bin\cmake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Programming\Cpp_Projects\Merge

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Programming\Cpp_Projects\Merge\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Merge.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Merge.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Merge.dir/flags.make

CMakeFiles/Merge.dir/main.cpp.obj: CMakeFiles/Merge.dir/flags.make
CMakeFiles/Merge.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Programming\Cpp_Projects\Merge\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Merge.dir/main.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Merge.dir\main.cpp.obj -c C:\Programming\Cpp_Projects\Merge\main.cpp

CMakeFiles/Merge.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Merge.dir/main.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Programming\Cpp_Projects\Merge\main.cpp > CMakeFiles\Merge.dir\main.cpp.i

CMakeFiles/Merge.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Merge.dir/main.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Programming\Cpp_Projects\Merge\main.cpp -o CMakeFiles\Merge.dir\main.cpp.s

CMakeFiles/Merge.dir/main.cpp.obj.requires:

.PHONY : CMakeFiles/Merge.dir/main.cpp.obj.requires

CMakeFiles/Merge.dir/main.cpp.obj.provides: CMakeFiles/Merge.dir/main.cpp.obj.requires
	$(MAKE) -f CMakeFiles\Merge.dir\build.make CMakeFiles/Merge.dir/main.cpp.obj.provides.build
.PHONY : CMakeFiles/Merge.dir/main.cpp.obj.provides

CMakeFiles/Merge.dir/main.cpp.obj.provides.build: CMakeFiles/Merge.dir/main.cpp.obj


# Object files for target Merge
Merge_OBJECTS = \
"CMakeFiles/Merge.dir/main.cpp.obj"

# External object files for target Merge
Merge_EXTERNAL_OBJECTS =

Merge.exe: CMakeFiles/Merge.dir/main.cpp.obj
Merge.exe: CMakeFiles/Merge.dir/build.make
Merge.exe: CMakeFiles/Merge.dir/linklibs.rsp
Merge.exe: CMakeFiles/Merge.dir/objects1.rsp
Merge.exe: CMakeFiles/Merge.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Programming\Cpp_Projects\Merge\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Merge.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Merge.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Merge.dir/build: Merge.exe

.PHONY : CMakeFiles/Merge.dir/build

CMakeFiles/Merge.dir/requires: CMakeFiles/Merge.dir/main.cpp.obj.requires

.PHONY : CMakeFiles/Merge.dir/requires

CMakeFiles/Merge.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Merge.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Merge.dir/clean

CMakeFiles/Merge.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Programming\Cpp_Projects\Merge C:\Programming\Cpp_Projects\Merge C:\Programming\Cpp_Projects\Merge\cmake-build-debug C:\Programming\Cpp_Projects\Merge\cmake-build-debug C:\Programming\Cpp_Projects\Merge\cmake-build-debug\CMakeFiles\Merge.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Merge.dir/depend

