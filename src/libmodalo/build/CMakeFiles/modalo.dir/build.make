# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.27

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\mingw64\bin\cmake.exe

# The command to remove a file.
RM = C:\mingw64\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\alina\projects\modscan\src\libmodalo

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\alina\projects\modscan\src\libmodalo\build

# Include any dependencies generated for this target.
include CMakeFiles/modalo.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/modalo.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/modalo.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/modalo.dir/flags.make

CMakeFiles/modalo.dir/modalo.cpp.obj: CMakeFiles/modalo.dir/flags.make
CMakeFiles/modalo.dir/modalo.cpp.obj: CMakeFiles/modalo.dir/includes_CXX.rsp
CMakeFiles/modalo.dir/modalo.cpp.obj: C:/Users/alina/projects/modscan/src/libmodalo/modalo.cpp
CMakeFiles/modalo.dir/modalo.cpp.obj: CMakeFiles/modalo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\alina\projects\modscan\src\libmodalo\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/modalo.dir/modalo.cpp.obj"
	C:\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/modalo.dir/modalo.cpp.obj -MF CMakeFiles\modalo.dir\modalo.cpp.obj.d -o CMakeFiles\modalo.dir\modalo.cpp.obj -c C:\Users\alina\projects\modscan\src\libmodalo\modalo.cpp

CMakeFiles/modalo.dir/modalo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/modalo.dir/modalo.cpp.i"
	C:\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\alina\projects\modscan\src\libmodalo\modalo.cpp > CMakeFiles\modalo.dir\modalo.cpp.i

CMakeFiles/modalo.dir/modalo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/modalo.dir/modalo.cpp.s"
	C:\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\alina\projects\modscan\src\libmodalo\modalo.cpp -o CMakeFiles\modalo.dir\modalo.cpp.s

# Object files for target modalo
modalo_OBJECTS = \
"CMakeFiles/modalo.dir/modalo.cpp.obj"

# External object files for target modalo
modalo_EXTERNAL_OBJECTS =

libmodalo.dll: CMakeFiles/modalo.dir/modalo.cpp.obj
libmodalo.dll: CMakeFiles/modalo.dir/build.make
libmodalo.dll: CMakeFiles/modalo.dir/linkLibs.rsp
libmodalo.dll: CMakeFiles/modalo.dir/objects1.rsp
libmodalo.dll: CMakeFiles/modalo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Users\alina\projects\modscan\src\libmodalo\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libmodalo.dll"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\modalo.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/modalo.dir/build: libmodalo.dll
.PHONY : CMakeFiles/modalo.dir/build

CMakeFiles/modalo.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\modalo.dir\cmake_clean.cmake
.PHONY : CMakeFiles/modalo.dir/clean

CMakeFiles/modalo.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\alina\projects\modscan\src\libmodalo C:\Users\alina\projects\modscan\src\libmodalo C:\Users\alina\projects\modscan\src\libmodalo\build C:\Users\alina\projects\modscan\src\libmodalo\build C:\Users\alina\projects\modscan\src\libmodalo\build\CMakeFiles\modalo.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/modalo.dir/depend
