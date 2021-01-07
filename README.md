# Proposal

Names: Jeremy Ku-Benjet, Lucas Lee

## Problem
### Description
The goal is a simple sprite based 2d platforming game where the player can roam around premade levels, jump and potentially use other abilities (such as an air dash or wall jump). The goal would be to make it from the left of the level to the right. The screen would scroll with the player to allow for larger levels.

### UI
It should take input from the keyboard or possibly a joystick to control a character around premade levels. There will be a start and and end screen upon loading or attempting to quit the game. 

The start and end screen will be a background image (possibly just a solid color) and text which can be selected with a cursor to progress or exit the program. This will most likely be controlled with arrow keys or wasd on the keyboard and a selection button.

When the game has started, the player will see a screen with sprites and have the option to control a character with various button inputs.

### Technical Design
The game will be built with [SDL](https://www.libsdl.org) which we will use for rendering sprites and taking input FINISH THIS LATER WHEN WE KNOW MORE ON SDL. 

The program will be split into three parts. A input reader which will read and process inputs. These inputs will be piped to a processer which will load levels, compute physics and generally make any other decsions about the gameplay. The processor will than create and pipe a map to a drawer. This will read spites (which might just be rectangles) and draw them to the screen based on the simplifed map from the processor. 

FINISH DATA STRUCTURE/ALGORITHM DESCRIPTION AFTER SOME MORE READING/RESEARCH

Concept Summary:
- Allocating memory
    - This is needed for various library structs and structs we will create.
- Working with files
    - Spites and levels will be loaded from files
- Finding information about files
    - ¯\\\_(ツ)\_/¯ (MIGHT NOT USE, FINISH LATER)
- Processes
    - We will have to start run multiple processes for the reader, processer and drawer.
- Signals
    - We will have to catch exit signals to clearly exit the program.
- Pipes
    - There are multiple processes which will use pipes to communicate.
- Shared Memory
    - FINISH LATER
- Semaphores
    - FINISH LATER

