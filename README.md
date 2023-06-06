# [PROI Project L23] - Dueling Drifters

## General information
* Subject code: PROI - L23
* Author:
    * Filip Ryniewicz
    * Cieśla Miłosz
    * Binh Vuong Le Duc
* Instructor: mgr inż. Mateusz Mordrzejewski

## **Description**
This is the final project for Object Oriented Programming. Apply knowledge of the C++ programming language as well as the fundamentals of object-oriented programming, design patterns, the git version management system, the SFML graphics library, and the catch2 test library.

## **Requirements**
* For users:
    * Windows OS
* For developers:
    * Windows OS
    * C++17
    * MinGW x32 with g++ 12.2.0
    * SFML 2.5.1
    * Catch2 2.13.7
    * Visual Studio Code 1.52.1

## **How to use?**
* For users:
    * Run the executable file `DuelingDrifters.exe` in folder [release](release).
    * More information about the game can be found in the [README.txt](/release/README.md) file.
* For developers:
    * Feel free to modify the source code in folder [src](src).
    * Navigate to repository folder and run the command `make all` to build the project in a terminal. (Support for Windows OS only)
    * The executable file will move update in folder [release](release). You can run it buy `make launch` command or click on it.
    * Every information about the game can be found in the [documentation](documentation) folder.
## **Project Implementation**

## **Documentation**
* The project mostly be self-documented by using the Doxygen tool. Hover over the function name to see the documentation.
* Class diagram and object relationship diagram can be found in the [documentation](documentation) folder.
## **Testing**
* Unit tests are written in the [test](test) folder using the Catch2 library.
* Tests are using to test the logic of the game and also how an object change it state through specific scenarios. It don't guarantee the UI will work correctly since there is no efficient way to test it.
## **Demo**
* Below is some pictures and videos of the game in action. Enjoy it yourself and give us feedbacks at any time. Thank you!