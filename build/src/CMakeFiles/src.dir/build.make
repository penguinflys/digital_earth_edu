# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/d/Sub_Ubuntu/Digital_Earth

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/d/Sub_Ubuntu/Digital_Earth/build

# Include any dependencies generated for this target.
include src/CMakeFiles/src.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/src.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/src.dir/flags.make

src/CMakeFiles/src.dir/ElevationAndTexture.cpp.o: src/CMakeFiles/src.dir/flags.make
src/CMakeFiles/src.dir/ElevationAndTexture.cpp.o: ../src/ElevationAndTexture.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/Sub_Ubuntu/Digital_Earth/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/src.dir/ElevationAndTexture.cpp.o"
	cd /mnt/d/Sub_Ubuntu/Digital_Earth/build/src && /usr/bin/g++-7  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/src.dir/ElevationAndTexture.cpp.o -c /mnt/d/Sub_Ubuntu/Digital_Earth/src/ElevationAndTexture.cpp

src/CMakeFiles/src.dir/ElevationAndTexture.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/src.dir/ElevationAndTexture.cpp.i"
	cd /mnt/d/Sub_Ubuntu/Digital_Earth/build/src && /usr/bin/g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/Sub_Ubuntu/Digital_Earth/src/ElevationAndTexture.cpp > CMakeFiles/src.dir/ElevationAndTexture.cpp.i

src/CMakeFiles/src.dir/ElevationAndTexture.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/src.dir/ElevationAndTexture.cpp.s"
	cd /mnt/d/Sub_Ubuntu/Digital_Earth/build/src && /usr/bin/g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/Sub_Ubuntu/Digital_Earth/src/ElevationAndTexture.cpp -o CMakeFiles/src.dir/ElevationAndTexture.cpp.s

src/CMakeFiles/src.dir/ElevationAndTexture.cpp.o.requires:

.PHONY : src/CMakeFiles/src.dir/ElevationAndTexture.cpp.o.requires

src/CMakeFiles/src.dir/ElevationAndTexture.cpp.o.provides: src/CMakeFiles/src.dir/ElevationAndTexture.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/src.dir/build.make src/CMakeFiles/src.dir/ElevationAndTexture.cpp.o.provides.build
.PHONY : src/CMakeFiles/src.dir/ElevationAndTexture.cpp.o.provides

src/CMakeFiles/src.dir/ElevationAndTexture.cpp.o.provides.build: src/CMakeFiles/src.dir/ElevationAndTexture.cpp.o


src/CMakeFiles/src.dir/Image.cpp.o: src/CMakeFiles/src.dir/flags.make
src/CMakeFiles/src.dir/Image.cpp.o: ../src/Image.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/Sub_Ubuntu/Digital_Earth/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/src.dir/Image.cpp.o"
	cd /mnt/d/Sub_Ubuntu/Digital_Earth/build/src && /usr/bin/g++-7  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/src.dir/Image.cpp.o -c /mnt/d/Sub_Ubuntu/Digital_Earth/src/Image.cpp

src/CMakeFiles/src.dir/Image.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/src.dir/Image.cpp.i"
	cd /mnt/d/Sub_Ubuntu/Digital_Earth/build/src && /usr/bin/g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/Sub_Ubuntu/Digital_Earth/src/Image.cpp > CMakeFiles/src.dir/Image.cpp.i

src/CMakeFiles/src.dir/Image.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/src.dir/Image.cpp.s"
	cd /mnt/d/Sub_Ubuntu/Digital_Earth/build/src && /usr/bin/g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/Sub_Ubuntu/Digital_Earth/src/Image.cpp -o CMakeFiles/src.dir/Image.cpp.s

src/CMakeFiles/src.dir/Image.cpp.o.requires:

.PHONY : src/CMakeFiles/src.dir/Image.cpp.o.requires

src/CMakeFiles/src.dir/Image.cpp.o.provides: src/CMakeFiles/src.dir/Image.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/src.dir/build.make src/CMakeFiles/src.dir/Image.cpp.o.provides.build
.PHONY : src/CMakeFiles/src.dir/Image.cpp.o.provides

src/CMakeFiles/src.dir/Image.cpp.o.provides.build: src/CMakeFiles/src.dir/Image.cpp.o


src/CMakeFiles/src.dir/TriFace.cpp.o: src/CMakeFiles/src.dir/flags.make
src/CMakeFiles/src.dir/TriFace.cpp.o: ../src/TriFace.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/Sub_Ubuntu/Digital_Earth/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/CMakeFiles/src.dir/TriFace.cpp.o"
	cd /mnt/d/Sub_Ubuntu/Digital_Earth/build/src && /usr/bin/g++-7  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/src.dir/TriFace.cpp.o -c /mnt/d/Sub_Ubuntu/Digital_Earth/src/TriFace.cpp

src/CMakeFiles/src.dir/TriFace.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/src.dir/TriFace.cpp.i"
	cd /mnt/d/Sub_Ubuntu/Digital_Earth/build/src && /usr/bin/g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/Sub_Ubuntu/Digital_Earth/src/TriFace.cpp > CMakeFiles/src.dir/TriFace.cpp.i

src/CMakeFiles/src.dir/TriFace.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/src.dir/TriFace.cpp.s"
	cd /mnt/d/Sub_Ubuntu/Digital_Earth/build/src && /usr/bin/g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/Sub_Ubuntu/Digital_Earth/src/TriFace.cpp -o CMakeFiles/src.dir/TriFace.cpp.s

src/CMakeFiles/src.dir/TriFace.cpp.o.requires:

.PHONY : src/CMakeFiles/src.dir/TriFace.cpp.o.requires

src/CMakeFiles/src.dir/TriFace.cpp.o.provides: src/CMakeFiles/src.dir/TriFace.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/src.dir/build.make src/CMakeFiles/src.dir/TriFace.cpp.o.provides.build
.PHONY : src/CMakeFiles/src.dir/TriFace.cpp.o.provides

src/CMakeFiles/src.dir/TriFace.cpp.o.provides.build: src/CMakeFiles/src.dir/TriFace.cpp.o


src/CMakeFiles/src.dir/main.cpp.o: src/CMakeFiles/src.dir/flags.make
src/CMakeFiles/src.dir/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/Sub_Ubuntu/Digital_Earth/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/CMakeFiles/src.dir/main.cpp.o"
	cd /mnt/d/Sub_Ubuntu/Digital_Earth/build/src && /usr/bin/g++-7  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/src.dir/main.cpp.o -c /mnt/d/Sub_Ubuntu/Digital_Earth/src/main.cpp

src/CMakeFiles/src.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/src.dir/main.cpp.i"
	cd /mnt/d/Sub_Ubuntu/Digital_Earth/build/src && /usr/bin/g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/Sub_Ubuntu/Digital_Earth/src/main.cpp > CMakeFiles/src.dir/main.cpp.i

src/CMakeFiles/src.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/src.dir/main.cpp.s"
	cd /mnt/d/Sub_Ubuntu/Digital_Earth/build/src && /usr/bin/g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/Sub_Ubuntu/Digital_Earth/src/main.cpp -o CMakeFiles/src.dir/main.cpp.s

src/CMakeFiles/src.dir/main.cpp.o.requires:

.PHONY : src/CMakeFiles/src.dir/main.cpp.o.requires

src/CMakeFiles/src.dir/main.cpp.o.provides: src/CMakeFiles/src.dir/main.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/src.dir/build.make src/CMakeFiles/src.dir/main.cpp.o.provides.build
.PHONY : src/CMakeFiles/src.dir/main.cpp.o.provides

src/CMakeFiles/src.dir/main.cpp.o.provides.build: src/CMakeFiles/src.dir/main.cpp.o


# Object files for target src
src_OBJECTS = \
"CMakeFiles/src.dir/ElevationAndTexture.cpp.o" \
"CMakeFiles/src.dir/Image.cpp.o" \
"CMakeFiles/src.dir/TriFace.cpp.o" \
"CMakeFiles/src.dir/main.cpp.o"

# External object files for target src
src_EXTERNAL_OBJECTS =

src/libsrc.a: src/CMakeFiles/src.dir/ElevationAndTexture.cpp.o
src/libsrc.a: src/CMakeFiles/src.dir/Image.cpp.o
src/libsrc.a: src/CMakeFiles/src.dir/TriFace.cpp.o
src/libsrc.a: src/CMakeFiles/src.dir/main.cpp.o
src/libsrc.a: src/CMakeFiles/src.dir/build.make
src/libsrc.a: src/CMakeFiles/src.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/d/Sub_Ubuntu/Digital_Earth/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX static library libsrc.a"
	cd /mnt/d/Sub_Ubuntu/Digital_Earth/build/src && $(CMAKE_COMMAND) -P CMakeFiles/src.dir/cmake_clean_target.cmake
	cd /mnt/d/Sub_Ubuntu/Digital_Earth/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/src.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/src.dir/build: src/libsrc.a

.PHONY : src/CMakeFiles/src.dir/build

src/CMakeFiles/src.dir/requires: src/CMakeFiles/src.dir/ElevationAndTexture.cpp.o.requires
src/CMakeFiles/src.dir/requires: src/CMakeFiles/src.dir/Image.cpp.o.requires
src/CMakeFiles/src.dir/requires: src/CMakeFiles/src.dir/TriFace.cpp.o.requires
src/CMakeFiles/src.dir/requires: src/CMakeFiles/src.dir/main.cpp.o.requires

.PHONY : src/CMakeFiles/src.dir/requires

src/CMakeFiles/src.dir/clean:
	cd /mnt/d/Sub_Ubuntu/Digital_Earth/build/src && $(CMAKE_COMMAND) -P CMakeFiles/src.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/src.dir/clean

src/CMakeFiles/src.dir/depend:
	cd /mnt/d/Sub_Ubuntu/Digital_Earth/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/d/Sub_Ubuntu/Digital_Earth /mnt/d/Sub_Ubuntu/Digital_Earth/src /mnt/d/Sub_Ubuntu/Digital_Earth/build /mnt/d/Sub_Ubuntu/Digital_Earth/build/src /mnt/d/Sub_Ubuntu/Digital_Earth/build/src/CMakeFiles/src.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/src.dir/depend
