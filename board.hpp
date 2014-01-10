/********************************************************************************/
/*  Elie Weintraub                                                              */
/*  AI -  Project #1 - Othello                                                  */
/*                                                                              */ 
/*  board.hpp                                                                   */
/*                                                                              */
/*  This headerfile defines all of the data members and member functions of     */
/*  the Board class.                                                            */
/*                                                                              */
/********************************************************************************/

#ifndef _BOARD_H
#define _BOARD_H

#define EMPTY      '0'
#define BLACK      '1'
#define WHITE      '2'

#include <iostream>
#include <fstream>
class Board {

 public:
  //Constructors
  Board();                                        // initializes standard board
  Board(char b[8][8],char turn,int n_b,int n_w);  // initializes board w/ given state
 
  //Accessors
  bool isLegal(char posX, char posY) {return lbrd[posX][posY];}		
  bool isEndOfGame() {return endOfGame;}
  int getNumLegalMoves(){ return numLegalMoves;}
  char getTurn(){return turn;}
  int getBlackScore(){return nBlack;}
  int getWhiteScore(){return nWhite;}
  //Mutators
  void flipTurn() {(turn==BLACK)?turn=WHITE:turn=BLACK;}
  //Other methods
  void printBoard(bool l_flag=true);     // displays the present board
  void saveGame();                       // saves the current game state to file
  bool exitGame();                       // exits the program and allows for saving upon exit
  int updateLegalMoves();                // updates legal moves(lbrd) & returns # of legal moves
  int makeMove(char posX, char posY);    // makes a move and returns number of flipped pieces
  bool pass();                           // returns true if player must pass, false if end of game
  int eval(char color=0);	             // heuristic function
	 
 private:
  char brd[8][8];   // board position
  char turn;        // which player's turn it is
  bool lbrd[8][8];  // legal moves
  int nBlack;       // number of black pieces
  int nWhite;       // number of white pieces
  int numLegalMoves;// number of legal moves
  bool endOfGame;   // true if end state is reached (only set and used by AI)
  //Helper method
  void printRow(int r, bool l_flag);  // displays a single row of the board
};

#endif //_BOARD_H