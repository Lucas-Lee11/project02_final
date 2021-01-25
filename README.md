# Project Icarus

Names: Jeremy Ku-Benjet, Lucas Lee
Period: 10

## Description
The project is a renderer and processer for use in making a game, built off of SDL. It also has a little demo (opposed to a big demo to show off all the capabilities because time constraints and we are slow).

### Required Libraries
- SDL2
```
sudo apt-get install libsdl2-dev
```
### Usage
to run the game
```
make ; make run
```
WASD: move in the direction those keys seem to put you in

## Devlog (README version)
|Person|Date|Description|
|------|----|-----------|
|jeremy|20210110|drafted proposol|
|jeremy/lucas|20210111|edited proposol|
|lucas|20210112|created player struct, drafted input reading and rendering|
|jeremy|20210112|cleaned up Makefile|
|jeremy|20210115|wrote entity struct|
|jeremy|20210115|created input reading files|
|jeremy|20210119|created entity linked list|
|jeremy|20210119|integrated lucas's draft of input reading into its more final form|
|jeremy|20210119|created simulator.h and simulator.c to start simulating game play|
|lucas|20210120|created stage struct, movable camera, tile loading, and tile rendering|
|jeremy|20210120|made the entity linked list doubly linked and added a bit more functionality|
|jeremy|20210120|more simulator writting|
|jeremy|20210121|added id to entities|
|jeremy|20210121|added shared entity array for rendering|
|jeremy|20210122|added function to copy entity|
|jeremy|20210122|reformated some code and bugfixes|
|lucas|20210123|entity rendering, better tile rendering and camera, refactored everything to do with stage.c and stage.h (bascially a struct with level information)|
|lucas|20210123|camera follows player|
|jeremy|20210123|keyboard input version 2, new and improved|
|jeremy|20210123|integrated all of the stuff in the stage struct into other files and refactored code (AGAIN!!!). Bug fixes|
|jeremy|20210124|more code refactoring and got all the abstracted away input reading and rendering working|
|lucas|20210124|fixed issue with camera going out of bounds|
|jeremy/lucas|20210124|removed unused code|

## Timeline
- [x] Proposal 1/11
- [x] Entity struct 1/13
- [x] Basic rendering of sprite 1/15
- [x] User input, placeholder processor 1/19
- [x] Processor finished 1/21
- [ ] Levels and bug testing 1/25
