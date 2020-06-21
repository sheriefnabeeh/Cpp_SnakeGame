# CPPND: Capstone Snake Game Example

This is a modified version of the Snake Project made by Udacity, where the A*Search algorithm is integrated in the code to guide the snake to the target.

Further information about the covered rubric points are in the last section of the Readme

<img src="snake_game.gif"/>

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.

## Rubric covered Points/Topics
In this project, i tried turning the algorithm into an object and define it's struct (Node) to be able
to manipulate data easier and if possible add it to it's own thread but time is limited. In a better situation: I could have turned it too into a templatized class to make it's usage generic. suggestions are of course welcomed for future reference and learning.

 In class "path.h" and "path.cpp":
1. The project uses Object Oriented Programming techniques.
2. Classes use appropriate access specifiers for class members.
3. Classes abstract implementation details from their interfaces.
4. Classes encapsulate behavior.

in Class renderer.h, line 15,16
5. Overloaded functions allow the same function to operate on different parameters.

in Class "path.h" line 16 and 37 references are used
6. The project makes use of references in function declarations.	

in Class "path.cpp" line 28->34
7. The project uses destructors appropriately.

in Class "path.h" and "path.cpp" 
8. The project follows the Rule of 5.

in Class "game.cpp" line 36 and path.cpp ->run method 

9. The project uses move semantics to move data, instead of copying it, where possible.

in Class "game.h" line 26 and "game.cpp" line 24 

10. The project uses smart pointers instead of raw pointers 
