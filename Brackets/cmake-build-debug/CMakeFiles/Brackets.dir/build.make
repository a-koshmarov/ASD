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
CMAKE_SOURCE_DIR = C:\Programming\Cpp_Projects\Brackets

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Programming\Cpp_Projects\Brackets\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Brackets.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Brackets.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Brackets.dir/flags.make

CMakeFiles/Brackets.dir/main.cpp.obj: CMakeFiles/Brackets.dir/flags.make
CMakeFiles/Brackets.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Programming\Cpp_Projects\Brackets\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Brackets.dir/main.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Brackets.dir\main.cpp.obj -c C:\Programming\Cpp_Projects\Brackets\main.cpp

CMakeFiles/Brackets.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Brackets.dir/main.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Programming\Cpp_Projects\Brackets\main.cpp > CMakeFiles\Brackets.dir\main.cpp.i

CMakeFiles/Brackets.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Brackets.dir/main.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Programming\Cpp_Projects\Brackets\main.cpp -o CMakeFiles\Brackets.dir\main.cpp.s

CMakeFiles/Brackets.dir/main.cpp.obj.requires:

.PHONY : CMakeFiles/Brackets.dir/main.cpp.obj.requires

CMakeFiles/Brackets.dir/main.cpp.obj.provides: CMakeFiles/Brackets.dir/main.cpp.obj.requires
	$(MAKE) -f CMakeFiles\Brackets.dir\build.make CMakeFiles/Brackets.dir/main.cpp.obj.provides.build
.PHONY : CMakeFiles/Brackets.dir/main.cpp.obj.provides

CMakeFiles/Brackets.dir/main.cpp.obj.provides.build: CMakeFiles/Brackets.dir/main.cpp.obj


# Object files for target Brackets
Brackets_OBJECTS = \
"CMakeFiles/Brackets.dir/main.cpp.obj"

# External object files for target Brackets
Brackets_EXTERNAL_OBJECTS =

Brackets.exe: CMakeFiles/Brackets.dir/main.cpp.obj
Brackets.exe: CMakeFiles/Brackets.dir/build.make
Brackets.exe: CMakeFiles/Brackets.dir/linklibs.rsp
Brackets.exe: CMakeFiles/Brackets.dir/objects1.rsp
Brackets.exe: CMakeFiles/Brackets.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Programming\Cpp_Projects\Brackets\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Brackets.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Brackets.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Brackets.dir/build: Brackets.exe

.PHONY : CMakeFiles/Brackets.dir/build

CMakeFiles/Brackets.dir/requires: CMakeFiles/Brackets.dir/main.cpp.obj.requires

.PHONY : CMakeFiles/Brackets.dir/requires

CMakeFiles/Brackets.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Brackets.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Brackets.dir/clean

CMakeFiles/Brackets.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Programming\Cpp_Projects\Brackets C:\Programming\Cpp_Projects\Brackets C:\Programming\Cpp_Projects\Brackets\cmake-build-debug C:\Programming\Cpp_Projects\Brackets\cmake-build-debug C:\Programming\Cpp_Projects\Brackets\cmake-build-debug\CMakeFiles\Brackets.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Brackets.dir/depend

