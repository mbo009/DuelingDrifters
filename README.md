# [PROI Project L23] - Dueling Drifters

## General information
* Subject code: PROI - L23
* Author:
    * Filip Ryniewicz
    * Cieśla Miłosz
    * Binh Vuong Le Duc
* Instructor: mgr inż. Mateusz Modrzejewski

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
    * Information about the game can be found in the [documentation](documentation) folder.
## **Project Implementation**
* The project is implemented in C++ language with the SFML library and developed in Visual Studio Code IDE and using makefile to build the project (with command support for Windows OS only).
* We have 4 main folders: [code](code), [assets](assets), [test](test), [release](release).
    * [code](code) folder contains the source code of the project.
    * [assets](assets) folder contains the resources of the project.
    * [test](test) folder contains the unit tests of the project.
    * [release](release) folder contains the executable file of the project.
* This project is implemented in OOP style with the MVC design pattern (most of the time).
* Class in the project:
    * carObj (carObj.h, carObj.cpp): Represent the properties of a car in the game include it position, velocity, acceleration, direction.
    * carSprite (carSprite.h, carSprite.cpp): Represent a car in 2D space with a texture and a carObj.
    * item (item.h, item.cpp):
        * Class represent for items with unique effects in the game.
        * Each type of item is a inherited class of this class with different texture and effect.
    * button (button.h, button.cpp): This class is used to create a button in the game. It has 2 states: normal and chosen. Select the button using keyboard and hit enter to choose it.
    * game (game.h, game.cpp): Handle event and update the game state.
    * menu (menu.h, menu.cpp): Handle event and update the menu state. (include setting menu, main menu, game mode selection menu)
## **Documentation**
* The project mostly be self-documented by using the Doxygen tool. Hover over the function name to see the documentation.
## **Testing**
* Unit tests are written in the [test](test) folder using the Catch2 library.
* Tests are using to test the logic of the game and also how an object change it state through specific scenarios. It don't guarantee the UI will work correctly since there is no efficient way to test it.
## **Demo**
* Below is some pictures and videos of the game in action. Enjoy it yourself and give us feedbacks at any time. Thank you!
### **Game play:**
![gameplay](/documentation/img/gameplay.gif)
### **Game main menu:**
![main menu](/documentation/img/main_menu.png)
### **Game mode selection:**
![game mode](/documentation/img/game_mode.png)
### **Game settings:**
![game settings](/documentation/img/game_setting.png)
### **Playground in duel mode:**
![duel mode](/documentation/img/duel.png)
### **Playground in tag mode:**
![tag mode](/documentation/img/tag.png)
