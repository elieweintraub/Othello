#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>

#include "vt100.h"
#include "board.hpp"
#include "player.hpp"

 
using namespace std;
void getGameParameters(bool &,bool &, int &,char (&)[8][8],char &,int &,int &, bool &);
bool endOfGameCheck(Board &board);
bool read_gamefile(ifstream &gamefile,char (&b)[8][8],char &wt,int &n_w,int &n_b);
bool getYesNo(string message);
int getInteger(string message);

int main(){
	bool p1_flg,p2_flg,load_flag=false;
	int tl=0,n_b=2,n_w=2,n_flipped=-1;
	char b[8][8],wt=BLACK;
	
	while(1){				
		//Initialize Game
		getGameParameters(p1_flg,p2_flg,tl,b,wt,n_w,n_b,load_flag);
		Player p1=Player(BLACK,p1_flg);
		Player p2=Player(WHITE,p2_flg);
		Board board=(load_flag)?Board(b,wt,n_b,n_w):Board();
		int timeLimit=tl;
		//Print some initial information
		cout<<endl<<endl;
		cout<<"*==========================================================================*"<<endl;
		cout<<"| To save the game state to a file: Enter 's' when prompted to make a move |"<<endl;
		cout<<"| To exit the game: Enter 'q' when prompted to make a move                 |"<<endl;
		cout<<"*==========================================================================*"<<endl;	
		cout<<endl<<endl;
		cout<<"Black is a "<<p1.printMode()<<endl;
		cout<<"White is a "<<p2.printMode()<<endl;
		if(timeLimit){cout<<"time limit: "<<timeLimit<<endl;}
		//Main Loop
		board.printBoard(true);
		if(endOfGameCheck(board)) continue;
		if(board.getTurn()==BLACK){goto black;}else{goto white;}
		while(1){
			black:
			p1.makeMove(board,timeLimit);
			board.printBoard(true);
			if(endOfGameCheck(board))break;
			white:
			p2.makeMove(board,timeLimit);
			board.printBoard(true);
			if(endOfGameCheck(board))break;
		}
	}		
	return 0;
}

// Gets the various game parameters from the user, such as the mode of each player, the time limit when
// there is AI, and whether or not to load in a board
void getGameParameters(bool &p1_flg,bool &p2_flg, int &tl,char (&b)[8][8],char &wt,int &n_w,int &n_b, bool &load_flag){
	//Prompt user for player type (human/computer)
	p1_flg=getYesNo("Will black (Player 1) be a computer? (Y/N): ");
	p2_flg=getYesNo("Will white (Player 2) be a computer? (Y/N): ");
	//Prompt user for time limit
	if(p1_flg || p2_flg){
		while(1){
			tl=getInteger("Enter a time limit in seconds (3-60): ");
			if( tl>=3 && tl<=60) break;
			cout<<"Invalid response!"<<endl;
		}
		srand(time(NULL)); //initialize random number generator
	}	
	//Prompt user if s/he wants to load a gamefile
	load_flag=false;
	while(getYesNo("Would you like to load a game from a file?(Y/N): ")){
		ifstream gamefile;
		string filename;
		cout<<"Enter gamefile filename: ";
		cin>>filename;
		gamefile.open(filename.c_str());
		if(!gamefile){
			cerr<<"Error: Could not open "<<filename<< "! Perhaps try another file."<<endl;
			continue;
		}
		if(!read_gamefile(gamefile,b,wt,n_w,n_b)){
			cout<<"Perhaps try another file."<<endl;
			continue;
		}	
		gamefile.close();
		load_flag=true;
		break;
	}
}		

// End of game check and handling
bool endOfGameCheck(Board &b){	
	if(b.getNumLegalMoves()==0){
		b.flipTurn();
		b.updateLegalMoves();	
		if(b.getNumLegalMoves()==0){
			if(b.getBlackScore()>b.getWhiteScore()){cout<<"Black wins!"<<endl;} 
			else if(b.getWhiteScore()>b.getBlackScore()){cout<<"White wins!"<<endl;}
			else{cout<<"It's a tie!"<<endl;}
			bool playAgain=getYesNo("Would you like to play another game? (Y/N): ");
			if(!playAgain){
				cout<< "Thank you for playing othello!"<<endl;
				exit(0);
			}
			else {cout<<endl<<endl;}
			return true;	
		}
	}
	return false;	
}	

// Reads in gamefile with specified game state
bool read_gamefile(ifstream &gamefile,char (&b)[8][8],char &wt,int &n_w,int &n_b){
	char c;
	int  n_black(0),n_white(0); 
	//read in board
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			gamefile>>c;
			if(c!=BLACK && c!=WHITE && c!=EMPTY){
				cerr<<"Error loading in gamefile. Format is incorrect!"<<endl; return false;
			}
			b[i][j]=c;
			if(c==BLACK){n_black++;}
			else if(c==WHITE){n_white++;}	
		}
	}
	//read in whose turn
	gamefile>>wt;
	if(wt!=BLACK && wt!=WHITE){
		cerr<<"Error loading in gamefile. Format is incorrect!"<<endl; return false;
	}	
	//initialize scores
	n_w=n_white; 
	n_b=n_black;
	
	return true;	
}			

// Reads an integer from standard input
int getInteger(string message){
  int n;
  bool inputGood = false;
  while (!inputGood) {
    inputGood = true;
    cout << message;
    cin >>n;
    if (!cin) {
      // Non-integer in input buffer, get out of "fail" state
      cin.clear();
      inputGood = false;
	  cout<<"Invalid response!"<<endl;
    }
    while (cin.get() != '\n'); // clear buffer
  }
  return n;
}

// Reads a yes/no from standard input
bool getYesNo(string message){
	char c;		
	while (1) {
		cout << message;
		cin >> c;
		if(cin.get() != '\n'){
			while (cin.get() != '\n'); // clear buffer
			cout<<"Invalid response!"<<endl;
			continue; 
		}
		if(c=='y' || c=='Y'){ return true;}
		if(c=='n' || c=='N') {return false;}
		else {cout<<"Invalid response!"<<endl;}
	}	
}