# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/thomas/Desktop/programmation/C++/Cours/TP03

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/thomas/Desktop/programmation/C++/Cours/build

# Include any dependencies generated for this target.
include CMakeFiles/exercice1.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/exercice1.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/exercice1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/exercice1.dir/flags.make

CMakeFiles/exercice1.dir/exercice1/Visage.cpp.o: CMakeFiles/exercice1.dir/flags.make
CMakeFiles/exercice1.dir/exercice1/Visage.cpp.o: /home/thomas/Desktop/programmation/C++/Cours/TP03/exercice1/Visage.cpp
CMakeFiles/exercice1.dir/exercice1/Visage.cpp.o: CMakeFiles/exercice1.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/thomas/Desktop/programmation/C++/Cours/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/exercice1.dir/exercice1/Visage.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/exercice1.dir/exercice1/Visage.cpp.o -MF CMakeFiles/exercice1.dir/exercice1/Visage.cpp.o.d -o CMakeFiles/exercice1.dir/exercice1/Visage.cpp.o -c /home/thomas/Desktop/programmation/C++/Cours/TP03/exercice1/Visage.cpp

CMakeFiles/exercice1.dir/exercice1/Visage.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/exercice1.dir/exercice1/Visage.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/thomas/Desktop/programmation/C++/Cours/TP03/exercice1/Visage.cpp > CMakeFiles/exercice1.dir/exercice1/Visage.cpp.i

CMakeFiles/exercice1.dir/exercice1/Visage.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/exercice1.dir/exercice1/Visage.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/thomas/Desktop/programmation/C++/Cours/TP03/exercice1/Visage.cpp -o CMakeFiles/exercice1.dir/exercice1/Visage.cpp.s

CMakeFiles/exercice1.dir/exercice1/Exercice1.cpp.o: CMakeFiles/exercice1.dir/flags.make
CMakeFiles/exercice1.dir/exercice1/Exercice1.cpp.o: /home/thomas/Desktop/programmation/C++/Cours/TP03/exercice1/Exercice1.cpp
CMakeFiles/exercice1.dir/exercice1/Exercice1.cpp.o: CMakeFiles/exercice1.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/thomas/Desktop/programmation/C++/Cours/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/exercice1.dir/exercice1/Exercice1.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/exercice1.dir/exercice1/Exercice1.cpp.o -MF CMakeFiles/exercice1.dir/exercice1/Exercice1.cpp.o.d -o CMakeFiles/exercice1.dir/exercice1/Exercice1.cpp.o -c /home/thomas/Desktop/programmation/C++/Cours/TP03/exercice1/Exercice1.cpp

CMakeFiles/exercice1.dir/exercice1/Exercice1.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/exercice1.dir/exercice1/Exercice1.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/thomas/Desktop/programmation/C++/Cours/TP03/exercice1/Exercice1.cpp > CMakeFiles/exercice1.dir/exercice1/Exercice1.cpp.i

CMakeFiles/exercice1.dir/exercice1/Exercice1.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/exercice1.dir/exercice1/Exercice1.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/thomas/Desktop/programmation/C++/Cours/TP03/exercice1/Exercice1.cpp -o CMakeFiles/exercice1.dir/exercice1/Exercice1.cpp.s

# Object files for target exercice1
exercice1_OBJECTS = \
"CMakeFiles/exercice1.dir/exercice1/Visage.cpp.o" \
"CMakeFiles/exercice1.dir/exercice1/Exercice1.cpp.o"

# External object files for target exercice1
exercice1_EXTERNAL_OBJECTS =

exercice1: CMakeFiles/exercice1.dir/exercice1/Visage.cpp.o
exercice1: CMakeFiles/exercice1.dir/exercice1/Exercice1.cpp.o
exercice1: CMakeFiles/exercice1.dir/build.make
exercice1: CMakeFiles/exercice1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/thomas/Desktop/programmation/C++/Cours/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable exercice1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/exercice1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/exercice1.dir/build: exercice1
.PHONY : CMakeFiles/exercice1.dir/build

CMakeFiles/exercice1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/exercice1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/exercice1.dir/clean

CMakeFiles/exercice1.dir/depend:
	cd /home/thomas/Desktop/programmation/C++/Cours/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/thomas/Desktop/programmation/C++/Cours/TP03 /home/thomas/Desktop/programmation/C++/Cours/TP03 /home/thomas/Desktop/programmation/C++/Cours/build /home/thomas/Desktop/programmation/C++/Cours/build /home/thomas/Desktop/programmation/C++/Cours/build/CMakeFiles/exercice1.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/exercice1.dir/depend

