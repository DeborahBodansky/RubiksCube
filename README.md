# How to build this Rubik's cube game

Simply run 'make' within this directory. This will construct the 'main' executable.

# How to play this Rubik's cube game

Run the 'main' executable with the command './main'. You should see a representation of a Rubik's cube in its initial (solved) configuration.

To rotate a face, you have to type in the first letter of the face you want to rotate (this is defined by the color of its central cell, which will remain constant), followed by a space, and then 'R' or 'L' for the direction in which you want to rotate it, right or left. For example, if you want to rotate the yellow face (the one with Y5 as its central cell) clockwise, you should type 'Y R' and hit enter. Note that both letters should be capitalized. The valid faces you can rotate in this game are (Y, B, O, G, R, W). Any input where the first letter does not match one of the letters in this set or the second letter doesn't match either 'R' or 'L' will be ignored. Upon a valid command, the cube rotate operation will be performed and you will see an output of the cube's new state.

To end the game, simply input 'END GAME' and the game will exit.# RubiksCube
