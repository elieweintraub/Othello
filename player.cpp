/********************************************************************************/
/*  Elie Weintraub                                                              */
/*  AI -  Project #1 - Othello                                                  */
/*                                                                              */ 
/*  player.cpp                                                                  */
/*                                                                              */
/*  This sourcefile implementss all of the data members and member functions of */
/*  the Player class.                                                           */
/*                                                                              */
/********************************************************************************/
#include <climits>
#include <sys/time.h>
#include "player.hpp"

using namespace std;

//Constructors
Player::Player(char c, bool computer){
	color=c;
	isComputer=computer;
}

//MAKEMOVE
int Player::makeMove(Board &b, int timeLimit){
	int n_flipped=0;
	const int MAX_DEPTH=15; //Depth gt what could be reached in time limit
	cout<<printColor()<<"'s turn to move:"<<endl;
	if (color==b.getTurn()){ //there exists a legal move
		if (!isComputer){ //isHuman
			char r,c;
			do{	getUserMove(r,c,b);
			}while(!(n_flipped=b.makeMove(r,c)));			
		}
		else{ //isComputer
			struct timeval start, curr;
			double s_time,curr_time,diff=0;
			int tmpMove,move=0,depth=1,r,c;
				
			gettimeofday(&start,NULL);	
			s_time=(double)start.tv_sec+(double)start.tv_usec/1000000.0;
			
			if (b.getNumLegalMoves()==1){ //only one legal move
				for(r=0;r<8;r++){
					for(c=0;c<8;c++){
						if(b.isLegal(r,c)){n_flipped=b.makeMove(r,c);goto end_loop;}
					}
				}
				end_loop:  ; //NO_OP	
			}
			else{ //more than one legal move exists				
// /**/	 	    cout<<endl;			
				for(depth=1;diff<(double)timeLimit/2.0 && depth<MAX_DEPTH;depth++){
// /**/				cout<<"Beginning depth "<<depth<<" search... \t\t";
					tmpMove=getBestMove(b,depth,timeLimit,s_time);
					if(tmpMove==-1){break;} else{move=tmpMove;}
					gettimeofday(&curr,NULL);
					curr_time=(double)curr.tv_sec+(double)curr.tv_usec/1000000.0;
					diff=curr_time-s_time;
				}					
				r=move/8; c=move%8;  
				n_flipped=b.makeMove(r,c); 
			}
			
			gettimeofday(&curr,NULL);
			curr_time=(double)curr.tv_sec+(double)curr.tv_usec/1000000.0;
			diff=curr_time-s_time;

// /**/		cout<<endl;				
			if(depth==MAX_DEPTH){
				cout<<"Computer searched to the end of the search tree"<<endl;
			}			
			else{cout<<"Computer searched to depth "<<depth-1<<endl;}
			printf("Searched for a total of %.2f seconds\n",diff);
			cout<<"Computer has chosen ("<<r<<","<<c<<")"<<endl;			
		}
	}
	else{ //no legal moves exist	
		cout<<printColor()<<" must pass!"<<endl;
	}
	return n_flipped;
}

//ALPHA_BETA
int Player::alphaBeta(Board &b,int depth,int alpha,int beta,int timeLimit,double s_time){
	struct timeval curr;
	double curr_time,diff;
	
	gettimeofday(&curr,NULL);
	curr_time=(double)curr.tv_sec+(double)curr.tv_usec/1000000.0;
	diff=curr_time-s_time;
	if(((double)timeLimit-diff)<0.01){
		return -1; //out of time		
	}
					
	Board child=b;
	if (depth==0 || b.isEndOfGame()){return child.eval(color);}
	if (b.getTurn()==BLACK){ //MAX
		if (b.getNumLegalMoves()==0){ 
			child.pass();
			alpha=max(alpha,alphaBeta(child,depth-1,alpha,beta,timeLimit,s_time));
		}	
		else{
			for(int r=0;r<8;r++){
				for(int c=0;c<8;c++){
					if(b.isLegal(r,c)){
						child=b;
						child.makeMove(r,c);
						alpha=max(alpha,alphaBeta(child,depth-1,alpha,beta,timeLimit,s_time));
						if(beta<=alpha){goto max_return_statement;}		
					}		
				}
			}
		}	
		max_return_statement:
		return alpha;	
	}				
	else { //MIN 
		if (b.getNumLegalMoves()==0){ 
			child.pass();
			beta=min(beta,alphaBeta(child,depth-1,alpha,beta,timeLimit,s_time));
		}	
		else{
			for(int r=0;r<8;r++){
				for(int c=0;c<8;c++){
					if(b.isLegal(r,c)){
						child=b;
						child.makeMove(r,c);
						beta=min(beta,alphaBeta(child,depth-1,alpha,beta,timeLimit,s_time));
						if(beta<=alpha){goto min_return_statement;}	 
					}	
				}
			}
		}	
		min_return_statement:
		return beta;	
	}		
}						

//GET_BEST_MOVE
int Player::getBestMove(Board &b,int depth,int timeLimit,double s_time){
	int bestMoves[b.getNumLegalMoves()];
	int	alpha=-1000000, beta=1000000, alphaTmp, betaTmp, numMoves=0,n=0;	
	struct timeval curr;
	double curr_time,diff;
	Board child=b;
	
	//collect best moves
	if (b.getTurn()==BLACK){ //MAX
		for(int r=0;r<8;r++){
			for(int c=0;c<8;c++){
				if(b.isLegal(r,c)){
					n++;
					child=b;
					child.makeMove(r,c);
					alphaTmp=alphaBeta(child,depth-1,alpha-1,beta,timeLimit,s_time);
					if(alphaTmp>alpha){
						numMoves=0;
						bestMoves[numMoves++]=r*8+c;
						alpha=alphaTmp;
					}
					else if(alphaTmp==alpha){
						bestMoves[numMoves++]=r*8+c;
					}
					gettimeofday(&curr,NULL);
					curr_time=(double)curr.tv_sec+(double)curr.tv_usec/1000000.0;
					diff=curr_time-s_time;
					if(((double)timeLimit-diff)<0.01 && n<b.getNumLegalMoves()){
// /**/					cout<<"out of time"<<endl;
						return -1; //out of time
					}
				}					
			}
		}
// /**/printf("alpha: %.2f",(double)alpha/512);
	}				
	else { //MIN 
		for(int r=0;r<8;r++){
			for(int c=0;c<8;c++){
				if(b.isLegal(r,c)){
					n++;
					child=b;
					child.makeMove(r,c);
					betaTmp=alphaBeta(child,depth-1,alpha,beta+1,timeLimit,s_time);
					if(betaTmp<beta){
						numMoves=0;
						bestMoves[numMoves++]=r*8+c;
						beta=betaTmp;
					}
					else if(betaTmp==beta){
						bestMoves[numMoves++]=r*8+c;
					}
					gettimeofday(&curr,NULL);
					curr_time=(double)curr.tv_sec+(double)curr.tv_usec/1000000.0;
					diff=curr_time-s_time;
					if(((double)timeLimit-diff)<0.01 && n<b.getNumLegalMoves()){
// /**/					cout<<"out of time"<<endl;						
						return -1; //out of time
					}	
				}
			}
		}	
// /**/printf("beta: %.2f",(double)beta/512);
	}
	//choose best move randomly if necessary
	int retval=(numMoves>1)?bestMoves[rand()%numMoves]:bestMoves[0];
// /**/cout<<"\t\tmove: ("<<retval/8<<","<<retval%8<<")"<<endl;
	return retval;
}	

//GET_USER_MOVE
void Player::getUserMove(char &r,char &c, Board &b){	
	char rr,cc;
	while(1){
		cout<<"Please enter row of move (0-7): ";
		cin>>rr; 
		if(cin.get() != '\n'){
			while (cin.get() != '\n'); // clear buffer
			cout<<"Invalid response!"<<endl;
			continue; 
		}
		if (rr=='s'){b.saveGame(); continue;} 
		else if (rr=='q') {if(!b.exitGame())continue;}
		r=rr-'0';
		if ( r>=0 && r<8 ) break;
		cout<<"Invalid response!"<<endl;
	}
	while(1){
		cout<<"Please enter column of move (0-7): ";
		cin>>cc; 
		if(cin.get() != '\n'){
			while (cin.get() != '\n'); // clear buffer
			cout<<"Invalid response!"<<endl;
			continue; 
		}
		if (cc=='s'){b.saveGame(); continue;} 
		else if (cc=='q') {if(!b.exitGame()) continue;}
		c=cc-'0';
		if ( c>=0 && c<8 ) break;
		cout<<"Invalid response!"<<endl;
	}
	cout<<"You have chosen ("<<rr<<","<<cc<<")"<<endl;
}