# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\software\clion\CLion 2020.2.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\software\clion\CLion 2020.2.3\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\lidan\Desktop\result\project\VR

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\lidan\Desktop\result\project\VR\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles\VR.dir\depend.make

# Include the progress variables for this target.
include CMakeFiles\VR.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\VR.dir\flags.make

CMakeFiles\VR.dir\opengl\Sample2D.cpp.obj: CMakeFiles\VR.dir\flags.make
CMakeFiles\VR.dir\opengl\Sample2D.cpp.obj: ..\opengl\Sample2D.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\lidan\Desktop\result\project\VR\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/VR.dir/opengl/Sample2D.cpp.obj"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1427~1.291\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\VR.dir\opengl\Sample2D.cpp.obj /FdCMakeFiles\VR.dir\ /FS -c C:\Users\lidan\Desktop\result\project\VR\opengl\Sample2D.cpp
<<

CMakeFiles\VR.dir\opengl\Sample2D.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/VR.dir/opengl/Sample2D.cpp.i"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1427~1.291\bin\Hostx64\x64\cl.exe > CMakeFiles\VR.dir\opengl\Sample2D.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\lidan\Desktop\result\project\VR\opengl\Sample2D.cpp
<<

CMakeFiles\VR.dir\opengl\Sample2D.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/VR.dir/opengl/Sample2D.cpp.s"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1427~1.291\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\VR.dir\opengl\Sample2D.cpp.s /c C:\Users\lidan\Desktop\result\project\VR\opengl\Sample2D.cpp
<<

CMakeFiles\VR.dir\main.cpp.obj: CMakeFiles\VR.dir\flags.make
CMakeFiles\VR.dir\main.cpp.obj: ..\main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\lidan\Desktop\result\project\VR\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/VR.dir/main.cpp.obj"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1427~1.291\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\VR.dir\main.cpp.obj /FdCMakeFiles\VR.dir\ /FS -c C:\Users\lidan\Desktop\result\project\VR\main.cpp
<<

CMakeFiles\VR.dir\main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/VR.dir/main.cpp.i"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1427~1.291\bin\Hostx64\x64\cl.exe > CMakeFiles\VR.dir\main.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\lidan\Desktop\result\project\VR\main.cpp
<<

CMakeFiles\VR.dir\main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/VR.dir/main.cpp.s"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1427~1.291\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\VR.dir\main.cpp.s /c C:\Users\lidan\Desktop\result\project\VR\main.cpp
<<

CMakeFiles\VR.dir\render\Camera.cpp.obj: CMakeFiles\VR.dir\flags.make
CMakeFiles\VR.dir\render\Camera.cpp.obj: ..\render\Camera.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\lidan\Desktop\result\project\VR\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/VR.dir/render/Camera.cpp.obj"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1427~1.291\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\VR.dir\render\Camera.cpp.obj /FdCMakeFiles\VR.dir\ /FS -c C:\Users\lidan\Desktop\result\project\VR\render\Camera.cpp
<<

CMakeFiles\VR.dir\render\Camera.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/VR.dir/render/Camera.cpp.i"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1427~1.291\bin\Hostx64\x64\cl.exe > CMakeFiles\VR.dir\render\Camera.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\lidan\Desktop\result\project\VR\render\Camera.cpp
<<

CMakeFiles\VR.dir\render\Camera.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/VR.dir/render/Camera.cpp.s"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1427~1.291\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\VR.dir\render\Camera.cpp.s /c C:\Users\lidan\Desktop\result\project\VR\render\Camera.cpp
<<

CMakeFiles\VR.dir\geometry\Vertex.cpp.obj: CMakeFiles\VR.dir\flags.make
CMakeFiles\VR.dir\geometry\Vertex.cpp.obj: ..\geometry\Vertex.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\lidan\Desktop\result\project\VR\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/VR.dir/geometry/Vertex.cpp.obj"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1427~1.291\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\VR.dir\geometry\Vertex.cpp.obj /FdCMakeFiles\VR.dir\ /FS -c C:\Users\lidan\Desktop\result\project\VR\geometry\Vertex.cpp
<<

CMakeFiles\VR.dir\geometry\Vertex.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/VR.dir/geometry/Vertex.cpp.i"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1427~1.291\bin\Hostx64\x64\cl.exe > CMakeFiles\VR.dir\geometry\Vertex.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\lidan\Desktop\result\project\VR\geometry\Vertex.cpp
<<

CMakeFiles\VR.dir\geometry\Vertex.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/VR.dir/geometry/Vertex.cpp.s"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1427~1.291\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\VR.dir\geometry\Vertex.cpp.s /c C:\Users\lidan\Desktop\result\project\VR\geometry\Vertex.cpp
<<

# Object files for target VR
VR_OBJECTS = \
"CMakeFiles\VR.dir\opengl\Sample2D.cpp.obj" \
"CMakeFiles\VR.dir\main.cpp.obj" \
"CMakeFiles\VR.dir\render\Camera.cpp.obj" \
"CMakeFiles\VR.dir\geometry\Vertex.cpp.obj"

# External object files for target VR
VR_EXTERNAL_OBJECTS =

VR.exe: CMakeFiles\VR.dir\opengl\Sample2D.cpp.obj
VR.exe: CMakeFiles\VR.dir\main.cpp.obj
VR.exe: CMakeFiles\VR.dir\render\Camera.cpp.obj
VR.exe: CMakeFiles\VR.dir\geometry\Vertex.cpp.obj
VR.exe: CMakeFiles\VR.dir\build.make
VR.exe: external\imgui\imgui.lib
VR.exe: CMakeFiles\VR.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\lidan\Desktop\result\project\VR\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable VR.exe"
	"D:\software\clion\CLion 2020.2.3\bin\cmake\win\bin\cmake.exe" -E vs_link_exe --intdir=CMakeFiles\VR.dir --rc=C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x64\rc.exe --mt=C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x64\mt.exe --manifests  -- C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1427~1.291\bin\Hostx64\x64\link.exe /nologo @CMakeFiles\VR.dir\objects1.rsp @<<
 /out:VR.exe /implib:VR.lib /pdb:C:\Users\lidan\Desktop\result\project\VR\cmake-build-debug\VR.pdb /version:0.0  /machine:x64 /debug /INCREMENTAL /subsystem:console   -LIBPATH:C:\Users\lidan\Desktop\result\project\VR\external\glfw\lib-vc2019  -LIBPATH:C:\Users\lidan\Desktop\result\project\VR\external\SDL\lib-vc2019\lib\x64  external\imgui\imgui.lib glfw3.lib SDL2.lib kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<

# Rule to build all files generated by this target.
CMakeFiles\VR.dir\build: VR.exe

.PHONY : CMakeFiles\VR.dir\build

CMakeFiles\VR.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\VR.dir\cmake_clean.cmake
.PHONY : CMakeFiles\VR.dir\clean

CMakeFiles\VR.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" C:\Users\lidan\Desktop\result\project\VR C:\Users\lidan\Desktop\result\project\VR C:\Users\lidan\Desktop\result\project\VR\cmake-build-debug C:\Users\lidan\Desktop\result\project\VR\cmake-build-debug C:\Users\lidan\Desktop\result\project\VR\cmake-build-debug\CMakeFiles\VR.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles\VR.dir\depend

