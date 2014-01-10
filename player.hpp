/********************************************************************************/
/*  Elie Weintraub                                                              */
/*  AI -  Project #1 - Othello                                                  */
/*                                                                              */ 
/*  player.hpp                                                                  */
/*                                                                              */
/*  This headerfile defines all of the data members and member functions of     */
/*  the Player class.                                                           */
/*                                                                              */
/********************************************************************************/

#ifndef _PLAYER_H
#define _PLAYER_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include "board.hpp"


class Player {

 public:
  //Constructors
  Player(char color, bool isComputer);                          
  //Accessors
  char getColor(){return color;}
  bool getMode() {return isComputer;}
  //Other methods
  int makeMove(Board &b,int timeLimit);
  std::string printMode(){return (isComputer)?"computer":"human";}
  std::string printColor(){return (color==BLACK)?"Black":"White";}
 
 private:
  char color;
  bool isComputer;
  //Helper methods
  void getUserMove(char &r,char &c, Board &b); // helper method for human side of makemove
  int getBestMove(Board &b,int depth,int tLim,double s_time); // wrappper for AI side of makemove
  int alphaBeta(Board &b,int depth,int alpha,int beta,int tLim,double s_time); // core AI
  inline int min(int a, int b){return (a<b)? a : b;} // helper function for alpha-beta search
  inline int max(int a, int b){return (a>b)? a : b;} // helper function for alpha-beta search
};

#endif //_PLAYER_H