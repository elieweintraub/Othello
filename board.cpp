/********************************************************************************/
/*  Elie Weintraub                                                              */
/*  AI -  Project #1 - Othello                                                  */
/*                                                                              */ 
/*  board.cpp                                                                   */
/*                                                                              */
/*  This sourcefile implementss all of the data members and member functions of */
/*  the Board class.                                                            */
/*                                                                              */
/********************************************************************************/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "board.hpp"
#include "vt100.h"

using namespace std;

//Default constructor
Board::Board(){
	//Initialize board
	for(int r=0;r<8;r++){                
		for(int c=0;c<8;c++){
			brd[r][c]=EMPTY;
		}
	}
	brd[3][3]=WHITE;brd[4][4]=WHITE;
	brd[3][4]=BLACK;brd[4][3]=BLACK;
	//Initialize turn
	turn=BLACK;
	//Initialize legalBoard and numLegalMoves
	updateLegalMoves();
	//Initialize number of pieces
	nWhite=2;nBlack=2;
	//Initialize gameOver
	endOfGame=false;
}

//Load Game Constructor
Board::Board(char b[8][8],char t,int n_b,int n_w){
	//Initialize board
	memcpy(brd,b,64);
	//Initialize turn
	turn=t;
	//Initialize legal board and numLegalMoves
	updateLegalMoves();
	//Initialize number of pieces
	nWhite=n_w; nBlack=n_b;
	//Initialize gameOver
	endOfGame=false;
}

//PRINTROW
void Board::printRow(int r, bool l_flag){	
	for(int c=0;c<8;c++){
		(c) ? cout<<"  ": cout<<"\t"<<r<<" |  " ;
		switch(brd[r][c]){
			case BLACK:
				cout<<set_colors( VT_BLACK, VT_GREEN)<<' '<<finalize;
				break;
			case WHITE:
				cout<<set_colors( VT_BLACK, VT_WHITE)<<' '<<finalize;
				break;
			case EMPTY:
				if(l_flag && lbrd[r][c]){ //show_legal_moves is on and is legal
					cout<<set_colors( VT_YELLOW, VT_DEFAULT)<<'-'<<finalize;
				}	
				else{
					cout<<' ';
				}
				break;	
			default:
				cerr<<"This should never occur\n";
		}
		(c==7) ? cout<<"  | "<<r : cout<<"  |";
	}
}

//PRINTBOARD		
void Board::printBoard(bool l_flag){
	cout<<endl<<endl;
	cout<<  "\t                       OTHELLO\n";
	cout<<"\n\t     0     1     2     3     4     5     6     7  ";
	cout<<"\n\t  *-----*-----*-----*-----*-----*-----*-----*-----*";
	for(int r=0;r<8;r++){  
		cout<<"\n\t  |     |     |     |     |     |     |     |     |\n";
		printRow(r,l_flag);		
		cout<<"\n\t  |     |     |     |     |     |     |     |     |";
		cout<<"\n\t  *-----*-----*-----*-----*-----*-----*-----*-----*";
		
	}	
	cout<<"\n\t     0     1     2     3     4     5     6     7  \n";
	cout<<"\n\t     Black's Score: "<<nBlack<<"\t\t";
	cout<<"White's Score: "<<nWhite<<endl<<endl<<endl;
}
	
//UPDATELEGALMOVES
int Board::updateLegalMoves(){
	int r,c,i,j;
	char color, opp_color; 
	int n_moves=0;
	
	color=turn; 
	(color==BLACK)?opp_color=WHITE:opp_color=BLACK; 
	
	for (r=0;r<8;r++){
		for(c=0;c<8;c++){ 
			lbrd[r][c]=false;
			//Check that position is open 
			if (brd[r][c]!=EMPTY) continue;	 //check next (r,c)
			//Check to the left
			if(c-2>=0 && brd[r][c-1]==opp_color){	
				for(j=c-2;j>0 && brd[r][j]==opp_color;j--){;} //NO_OP	
				if (brd[r][j]==color){lbrd[r][c]=true;n_moves++; continue;}
			}	
			//Check to the right
			if(c+2<=7 && brd[r][c+1]==opp_color){	
				for(j=c+2;j<7 && brd[r][j]==opp_color;j++){;} //NO_OP	
				if (brd[r][j]==color){lbrd[r][c]=true;n_moves++; continue;}
			}	
			//Check directly up
			if(r-2>=0 && brd[r-1][c]==opp_color){	
				for(i=r-2;i>0 && brd[i][c]==opp_color;i--){;} //NO_OP	
				if (brd[i][c]==color){lbrd[r][c]=true;n_moves++; continue;}
			}
			//Check directly down
			if(r+2<=7 && brd[r+1][c]==opp_color){	
				for(i=r+2;i<7 && brd[i][c]==opp_color;i++){;} //NO_OP	
				if (brd[i][c]==color){lbrd[r][c]=true;n_moves++; continue;}
			}
			//Check up and to the left
			if(r-2>=0 && c-2>=0 && brd[r-1][c-1]==opp_color){	
				for(i=r-2,j=c-2;i>0 && j>0 && brd[i][j]==opp_color;i--,j--){;} //NO_OP	
				if (brd[i][j]==color){lbrd[r][c]=true;n_moves++; continue;}
			}
			//Check up and to the right
			if(r-2>=0 && c+2<=7 && brd[r-1][c+1]==opp_color){	
				for(i=r-2,j=c+2;i>0 && j<7 && brd[i][j]==opp_color;i--,j++){;} //NO_OP	
				if (brd[i][j]==color){lbrd[r][c]=true;n_moves++; continue;}
			}
			//Check down and to the left
			if(r+2<=7 && c-2>=0 && brd[r+1][c-1]==opp_color){	
				for(i=r+2,j=c-2;i<7 && j>0 && brd[i][j]==opp_color;i++,j--){;} //NO_OP	
				if (brd[i][j]==color){lbrd[r][c]=true;n_moves++; continue;}
			}
			//Check down and to the right
			if(r+2<=7 && c+2<=7 && brd[r+1][c+1]==opp_color){	
				for(i=r+2,j=c+2;i<7 && j<7 && brd[i][j]==opp_color;i++,j++){;} //NO_OP	
				if (brd[i][j]==color){lbrd[r][c]=true;n_moves++; continue;}
			}			
		}
	}
	numLegalMoves=n_moves;
	return n_moves;
}	

//MAKEMOVE -returns n_flipped, 0 if illegal
int Board::makeMove(char r, char c){
	char color, opp_color; 
	int i,j,n_flipped=0;
	
	color=turn;
	(color==BLACK)?opp_color=WHITE:opp_color=BLACK; 
	
	if(!lbrd[r][c]){cout<<"Illegal move!"<<endl; return 0;}
	//Update board
	brd[r][c]=color;
	//Check to the left
	if(c-2>=0 && brd[r][c-1]==opp_color){	
		for(j=c-2;j>0 && brd[r][j]==opp_color;j--){;} //NO_OP	
		if (brd[r][j]==color){while(++j<c){brd[r][j]=color;n_flipped++;}}
	}		
	//Check to the right
	if(c+2<=7 && brd[r][c+1]==opp_color){	
		for(j=c+2;j<7 && brd[r][j]==opp_color;j++){;} //NO_OP	
		if (brd[r][j]==color){while(--j>c){brd[r][j]=color;n_flipped++;}}
	}	
	//Check directly up
	if(r-2>=0 && brd[r-1][c]==opp_color){	
		for(i=r-2;i>0 && brd[i][c]==opp_color;i--){;} //NO_OP	
		if (brd[i][c]==color){while(++i<r){brd[i][c]=color;n_flipped++;}}
	}
	//Check directly down
	if(r+2<=7 && brd[r+1][c]==opp_color){	
		for(i=r+2;i<7 && brd[i][c]==opp_color;i++){;} //NO_OP	
		if (brd[i][c]==color){while(--i>r){brd[i][c]=color;n_flipped++;}}
	}
	//Check up and to the left
	if(r-2>=0 && c-2>=0 && brd[r-1][c-1]==opp_color){	
		for(i=r-2,j=c-2;i>0 && j>0 && brd[i][j]==opp_color;i--,j--){;} //NO_OP	
		if (brd[i][j]==color){while(++i<r){brd[i][++j]=color;n_flipped++;}}
	}
	//Check up and to the right
	if(r-2>=0 && c+2<=7 && brd[r-1][c+1]==opp_color){	
		for(i=r-2,j=c+2;i>0 && j<7 && brd[i][j]==opp_color;i--,j++){;} //NO_OP	
		if (brd[i][j]==color){while(++i<r){brd[i][--j]=color;n_flipped++;}}
	}
	//Check down and to the left
	if(r+2<=7 && c-2>=0 && brd[r+1][c-1]==opp_color){	
		for(i=r+2,j=c-2;i<7 && j>0 && brd[i][j]==opp_color;i++,j--){;} //NO_OP	
		if (brd[i][j]==color){while(--i>r){brd[i][++j]=color;n_flipped++;}}
	}
	//Check down and to the right
	if(r+2<=7 && c+2<=7 && brd[r+1][c+1]==opp_color){	
		for(i=r+2,j=c+2;i<7 && j<7 && brd[i][j]==opp_color;i++,j++){;} //NO_OP	
		if (brd[i][j]==color){while(--i>r){brd[i][--j]=color;n_flipped++;}}
	}
	//Update turn counter
	turn=opp_color;
	//update legal moves
	updateLegalMoves();	
	//update number of pieces of each color
	if(color==BLACK){nBlack+=n_flipped+1;nWhite-=n_flipped;}
	else{nBlack-=n_flipped;nWhite+=n_flipped+1;}
	return n_flipped;
}

// PASS - AI level: returns true if player must pass, false if end of game
bool Board::pass(){
	flipTurn();
	updateLegalMoves();	
	if(numLegalMoves==0){
		endOfGame=true;
		return false;
	}
	return true;
}	

// SAVE_GAME
void Board::saveGame(){
	string filename;
	while(1){
		cout<<"Please enter a valid filename for the saved game: ";
		cin>>filename;
		
		ofstream output(filename.c_str());
		if(!output){
			cerr<<"Error: Could not open "<<filename<< " for writing!"<<endl;
			continue;
		}
		for(int i=0;i<8;i++){
			for(int j=0;j<8;j++){
				output<<brd[i][j]<<' ';
			}
			output<<endl;
		}	
		output<<turn<<endl;
		output.close();
		cout<<"Game was successfully saved to "<<filename<< "."<<endl;
		break;
	}
}	

//EXIT_GAME
bool Board::exitGame(){
	char resp;
	while(1){
		cout<<"Are you sure you want to exit the game? (Y/N): ";
		cin>>resp;
		if(cin.get() != '\n'){
			while (cin.get() != '\n'); // clear buffer
			cout<<"Invalid response!"<<endl;
			continue; 
		}
		if(resp=='y' || resp=='Y'){ break;}
		else if(resp=='n' || resp=='N') {return false;}
		else {cout<<"Invalid response!"<<endl;}
	}	
	while(1){	
		cout<<"Would like to save the game before exiting? (Y/N): ";
		cin>>resp;
		if(cin.get() != '\n'){
			while (cin.get() != '\n'); // clear buffer
			cout<<"Invalid response!"<<endl;
			continue; 
		}
		if(resp=='y' || resp=='Y') {saveGame();}
		else if(resp=='n' || resp=='N');//NO_OP
		else{cout<<"Invalid response!"<<endl; continue;}
		cout<< "Thank you for playing othello!"<<endl;
		exit(0);
	}
}
	
// EVAL
int Board::eval(char color){
	int p=0,c=0,d=0,e=0,l=0,m=0,f=0,v=0,i,j,x,y,k;
	int w=(turn==BLACK)?1:-1;
	int X[8]={-1,-1,-1,0,0,1,1,1};
	int Y[8]={-1,0,1,-1,1,-1,0,1};
	int V[8][8]={ 50, -1,  5,  2,  2,  5, -1, 50, /**/  -1,-10,  1,  1,  1,  1,-10, -1,  /**/
	               5,  1,  1,  1,  1,  1,  1,  5, /**/   2,  1,  1,  0,  0,  1,  1,  2,  /**/
				   2,  1,  1,  0,  0,  1,  1,  2, /**/   5,  1,  1,  1,  1,  1,  1,  5,  /**/
				  -1,-10,  1,  1,  1,  1,-10, -1, /**/  50, -1,  5,  2,  2,  5, -1, 50}; /**/
				  
	switch(color){
		case WHITE:
		case BLACK:
		default:
			if(!endOfGame){
				
				//Piece count
				p=100*(float)(nBlack-nWhite)/(float)(nBlack+nWhite);
				
				//Corner Occupancy
				if(brd[0][0]==BLACK) c+=25; else if(brd[0][0]==WHITE) c-=25; 
				if(brd[0][7]==BLACK) c+=25; else if(brd[0][7]==WHITE) c-=25; 
				if(brd[7][0]==BLACK) c+=25; else if(brd[7][0]==WHITE) c-=25; 
				if(brd[7][7]==BLACK) c+=25; else if(brd[7][7]==WHITE) c-=25; 
				
				//Corner closeness
				if(brd[0][0]==EMPTY){
					if(brd[1][1]==BLACK) l-=13; else if(brd[1][1]==WHITE) l+=13; 
					if(brd[1][0]==BLACK) l-=6; else if(brd[1][0]==WHITE) l+=6; 
					if(brd[0][1]==BLACK) l-=6; else if(brd[0][1]==WHITE) l+=6;
				}
				if(brd[0][7]==EMPTY){				
					if(brd[1][6]==BLACK) l-=13; else if(brd[1][6]==WHITE) l+=13; 
					if(brd[1][7]==BLACK) l-=6; else if(brd[1][7]==WHITE) l+=6; 
					if(brd[0][6]==BLACK) l-=6; else if(brd[0][6]==WHITE) l+=6;
				}
				if(brd[7][0]==EMPTY){	
					if(brd[6][1]==BLACK) l-=13; else if(brd[6][1]==WHITE) l+=13; 
					if(brd[7][1]==BLACK) l-=6; else if(brd[7][1]==WHITE) l+=6; 
					if(brd[6][0]==BLACK) l-=6; else if(brd[6][0]==WHITE) l+=6;
				}
				if(brd[7][7]==EMPTY){
					if(brd[6][6]==BLACK) l-=13; else if(brd[6][6]==WHITE) l+=13;
					if(brd[7][6]==BLACK) l-=6; else if(brd[7][6]==WHITE) l+=6; 
					if(brd[6][7]==BLACK) l-=6; else if(brd[6][7]==WHITE) l+=6;
				}	
				
				//Mobility
				int m1=numLegalMoves;
				flipTurn();updateLegalMoves();
				int m2=numLegalMoves;
				if(m1!=m2) {m=100*w*(float)(m1-m2)/(float)(m1+m2);}
				
				//Frontier discs and disk values
				int f1=0,f2=0,v1=0,v2=0;
				for(i=0;i<8;i++){
					for(j=0;j<8;j++){
						if (brd[i][j]==EMPTY) continue; 
						(brd[i][j]==BLACK)?v1+=V[i][j]:v2+=V[i][j];
						for(k=0;k<8;k++){
							x=i+X[k]; y=j+Y[k];
							if(x>=0 && x<8 && y>=0 && y<7 && brd[x][y] == EMPTY){
								(brd[i][j]==BLACK)?f1+=1:f2+=1;
								break;
							}	
						}
					}			
				}
				if(f1!=f2) {f=100*(float)(f2-f1)/(float)(f1+f2);}
				if(v1!=v2) {v=100*(float)(v1-v2)/(float)(v1+v2);}
				
				//Return evaluation	
				return 2*p+120*c+80*l+60*m+45*f+20*v; // approx nomalized to [-64,64]*512~=100*327
			}
			else{return 512*(nBlack-nWhite);}
	}
}	
