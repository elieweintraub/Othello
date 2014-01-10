README

Artificial Intelligence Project 1: Othello
- Elie Weintraub   11/1/13

Overview
For this project an Othello playing program was implemented in C++.  
A simple and intuitive ASCII interface was created to support the program.
The program allows for the user to select if black or white (or both) will be a computer.
If a computer is playing, the program employs iterative deepening and an alpha-beta search
to make the computer’s moves. Additional parameters set by the user include a time limit
for the computer (from 3-60 seconds) and whether to start play from the standard position 
or from an arbitrary starting position specified in a text file.
Finally, the user can save the board position at any point in the game so that it can be 
loaded in and resumed at a subsequent time.

Implementation
As mentioned the program was implemented in C++. Two main classes were created to support
the program, a Board class and a Player class. The majority of game state information was
stored in the Board class. This was done primarily to aid in efficient implementation of 
the AI part of the program. Specifically, the Board class’s data members include the board
(implemented as an 8x8 2-dimensional char array), a list of currently legal moves
(implemented as an 8x8 2-dimensional bool array), the number of currently legal moves,
which player’s turn it is, and the number of black and white pieces currently on the board.
The Player class’s data members were limited to a color (implemented as a char) and a mode
(implemented as an isComputer bool). Moves were made on the Player level by calling lower
level Board methods.
The most significant part of this program was the implementation of the AI. As mentioned
above the program employs iterative deepening and an alpha-beta search to make the
computer’s moves. Additionally, a multi-component heuristic was developed for state
evaluation.  With the current implementation, and under a three second time limit, the
computer is able to search to an average depth of 7-8 in the mid-game, with higher depths in
the opening and closing part of the game. Components of the heuristic include corner occupancy,
corner closeness (meaning the occupancy of a piece adjacent to a corner), disc count, number of
frontier discs, mobility, and a position-weight component (which gives a static value to each 
location on the board). Each of these components is first individually scaled so that it can 
take on an integer value in the range of [-100,100]. The scaled components are each then given 
a weight to reflect their relative importance and summed together to obtain the final value. If
the end-of-game state was reached then only the piece count component is used. Additionally,
the weighting is done in such a way that the value obtained for a non-end-of-game state is scaled
so as to be comparable to the values obtained from an end-of-game state. Significant weight is 
given to the frontier and mobility components of the heuristic, as it was found empirically that
this leads to strong play.

User Interface 
Upon running the executable, the user is prompted to answer several questions (i.e. will black be
a computer, will white be a computer, enter a time limit, and would you like to load a game from
a file). User input is checked for validity and if invalid the user is told so and prompted again.
The board is displayed using “ASCII art” with white pieces represented by white squares and Black
pieces by green squares. Additionally legal moves are represented by yellow dashes. For each turn
if a valid move exists the user is prompted to enter first the row number and then, when prompted,
the column number. Both are clearly demarcated on the displayed board. Finally the user can also
choose to enter ‘q’ which quits the program (after first being prompted as to whether or not the 
user would like to save the game before exiting) or ‘s’ which saves the current game state to a 
text file and then continues play. Finally, upon completion of each game a winner is declared and 
the user is asked whether s/he would like to play another game or exit the program. 

Game File Format
Game files are simple text files which indicate the state of the game. The first 64 non-white space
characters represent the board. 0 represents an empty square, 1 represents a black piece, and 2 
represents a white piece. The next non-white space character is a 1 or 2 and represents whose turn 
it is. All subsequent characters are ignored.