# TMP README: Proposal

Names: Jeremy Ku-Benjet, Lucas Lee

## Description
### Problem
The problem we try to solve is the video game market is only mostly oversaturated with poorly made 2d platformers and we try to remedy that.

The goal is a simple sprite based 2d platforming game where the player can roam around premade levels, jump and potentially use other abilities (such as an air dash or wall jump). The goal would be to make it from the left of the level to the right. The screen would scroll with the player to allow for larger levels.

### UI
It should take input from the keyboard or possibly a joystick to control a character around premade levels. There will be a start and and end screen upon loading or attempting to quit the game. 

The start and end screen will be a background image (possibly just a solid color) and text which can be selected with a cursor to progress or exit the program. This will most likely be controlled with arrow keys or wasd on the keyboard and a selection button.

When the game has started, the player will see a screen with sprites and have the option to control a character with various button inputs.

### Technical Design
The game will be built with [SDL](https://www.libsdl.org) which we will use for actually taking the images from their stored form on the computer and putting them on the screen. In addition we will be using SDL to take input (eg. Keyboard input, Exiting the window).

The program will be split into three parts. A input reader which will read inputs and wrap them into a custom format (probably an integer representing a certain value) which the processor can interpret. These inputs will then be piped to the processor in a format probably consisting of a "begin" number, various player inputs, and a "finish" number. As the processor will block on this pipe, how many frames will run in a certain period of time will be decided here. In addition, the input reader would read from the processer after it sends inputs to make sure everything is all right and it shouldn't die.

These formatted inputs will be piped to the processer, a process which will load levels, compute physics and generally make any other decsions about the gameplay. Any game state will be composed of a series of entities. Entities could be background or foreground objects, player sprites, enemie sprites or ui elements. Each entity would have an absolute position, an accleration, a velocity, a size (l,w), a type (like is this a player controlled entity, is it a wall?), four booleans representing collision with other sprites in each of the cardinal directions (maybe redundant to type), a boolean representing vissablility, an ID, assosiated sprite (don't quite know what form this would be in yet) and possibly other features if we find them nessisary. This would be a struct. These would be placed in either an large array (kind of easy to work with and IDs could just be indecies) or a linked list (easy adding and deleting entitites no matter where they are). In addition game values would exist. This holds information such as score or if the game is in a menu or paused. The game values would act kind of like a special entity which represents the entire game. There would also be a special camera entity who's position would tell where the screen is (for example its absolute coordinates might be the center of the screen).

During a frame, an sequence of inputs ("begin" to "finish") would be read from the "input" pipe. For each of these input, the game values would be updated if needed (like maybe the game was paused) and an assosiated action based on the current game values and input would run. This process CAN and WILL change other entities. Things like level loading or saving scores (if we have that) will be done here. A similar process would than occur for each entity. For example, an "exit game" action might corrospond to freeing all the entities, stopping processes and closing the game window. Another example could be if the game state is "gameplay" then an input of "keyboard left" would increase the "player" entity's acceleration by 1. Each entity needs to be processed in a certain order. This order would likely be maintained though the storage list. So we don't drown in if else statements, we might implementing this by making an array of function pointers so arr\[*type*\]\[*action*\] = *assosiated action function*. 

The processor will then pipe the entites to the renderer. This could be done through first writting a number which signifies the amount of entities and then send that amount of entities. The camera entity would always be sent first. The processsor would than send any other data it needs (like commands asking for special visual effects or asking the drawer to die). These would likely be integers and wrapped the same way as how the reader sent information.

The drawer will read these entities and for each entity in the order they appear (unless we decide to make some priority system) read the assosiated sprite and write it to the screen in the desiganted area (given by position relative to the camera). The drawer would then display the frame. 

The data structures (outside of those provided by SDL) would not be much more than simple structs. We might end up using a linked list as well. Algorithm wise, except for what was described above, a sorting algorithm might be used to sort entities in terms of a special priority. Either a quick-sort or a merge sort would be used for their efficiency and relative simplicity. IF we find there are few sprites using an insertion sort could be efffective as well. We will use vairious algorithms related to geometry like intersection of two lines, though some of these are closer to formulas than algorithms. I don't think we will end up implementing many, if any, advanced algorithms or data structures for this project.

Concept Summary:
- Allocating memory
    - This is needed for various library structs and structs we will create.
- Working with files
    - Spites and levels will be loaded from files. Additional player information may also be saved through files.
- Finding information about files
    - ¯\\\_(ツ)\_/¯ Might not use.
- Processes
    - We will have to start run multiple processes for the reader, processer and drawer.
- Signals
    - We will have to catch exit signals to cleanly exit the program.
- Pipes
    - There are multiple processes which will use pipes to communicate.
- Shared Memory
    - ¯\\\_(ツ)\_/¯ I don't think we went over this yet so I am really not sure
- Semaphores
    - ¯\\\_(ツ)\_/¯ I don't think we went over this yet so I am really not sure

## Timeline
- [x] Proposal 11
- [ ] Sprite To  
- [ ] 
- [ ] 
- [ ] 
- [ ] 
- [ ] 
- [ ] 
