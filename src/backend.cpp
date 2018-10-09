#include <stdio.h>
#include <vector>
#include <thread>

#include "backend.h"

/********************************************************************************************************
 GLOBAL VARIABLES.
********************************************************************************************************/
int pieceCount = -1;
int pathCount = 0;
std::array<std::string,32> _b;
int xy_to_char[97] = {33,33,33,33,33,33,33,33,33,33,333,3,33,0,1,2,33,33,33,33,33,33,33,3,4,5,33,33,33,33,33,6,7,8,9,10,11,12,33,33,33,13,14,15,16,17,18,19,33,33,33,20,21,22,23,24,25,26,33,33,33,33,33,27,28,29,33,33,33,33,33,33,33,30,31,32,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33};
int char_to_xy[33] = {13,14,15,23,24,25,\
											31,32,33,34,35,36,37,\
											41,42,43,44,45,46,47,\
											51,52,53,54,55,56,57,\
											63,64,65,73,74,75};
/********************************************************************************************************
 The main function fills the _b vector with the starting layout then finds out how many peices are in the starting layout,
 this is so the program knows how many of the _b vector to print out when completed. It then proceeds to call the attempt()
 function with the starting layout.
********************************************************************************************************/
void backend(std::string in){
	_b.fill(in);

	for(int m = 0; m <= 32; ++m)
		if(in[m] == '@')
			pieceCount++;

	attempt(in);
}


/********************************************************************************************************
 attempt() function scans from top left to bottom right of the board looking for moves North to West, if a move is found,
 it saves the new layout, having done the move, and calls itself with the new board layout and pauses. If it  gets to the end without finding
 a move, it will return 0. If it was called directly then the attempt() that came before will continue to scan for any moves
 available prior to having moved the last peice. Eventually, when the attempt() that was called by backend() reaches the bottom right (the end)
 it will return 0 and the backend() will end, as it will have checked for every possible move by then. If however the program finds a way to
 complete it, it will return the steps to the interface showing the moves to complete it then returns.
********************************************************************************************************/
int compass = 0; int direc = 0; int _direc = 0; int coords;
int move(int direc, int _direc, int coords);
int attempt(std::string in) {
	if(pathCount==pieceCount && in[16] == '@'){
  	return 0;
  }
  for(int c = 0; c < 33; c++){
		int coords = char_to_xy[c];
	  if( _b[pathCount][c] == '@'){
	    for (compass = 0; compass < 4; compass++){
	    	switch(compass){
	      	case(0): if(coords < 58){direc = 10; _direc= 20; move(direc, _direc, coords);} break;
	        case(1): if(coords < 76){direc = 1; _direc= 2; move(direc, _direc, coords);} break;
	        case(2): if(coords > 30){direc = -10; _direc= -20; move(direc, _direc, coords);} break;
	        case(3): if(coords > 12){direc = -1; _direc= -2; move(direc, _direc, coords);} break;
	      }
	    }
		}
  }
  pathCount--;
  return 0;
}

inline int move(int direc, int _direc, int coords){
  	if( _b[pathCount][xy_to_char[coords+direc]] == '@'){
    	if( _b[pathCount][xy_to_char[coords+_direc]] == 'O'){
      	pathCount++;
        _b[pathCount] = _b[pathCount-1];
        _b[pathCount][xy_to_char[coords]] = 'O';
        _b[pathCount][xy_to_char[coords+direc]] = 'O';
        _b[pathCount][xy_to_char[coords+_direc]] = '@';
        attempt(_b[pathCount]);
      }
    }
  return 0;
}

std::string printOut(){
	std::string fullB;
	for(int arrayPos = 0; arrayPos < 2+pathCount; arrayPos++) {
		fullB.append("..").append(_b[arrayPos].substr(0, 3).c_str()).append("..\n");
		fullB.append("..").append(_b[arrayPos].substr(3, 3).c_str()).append("..\n");
		fullB.append(_b[arrayPos].substr(6, 7).c_str()).append("\n");
		fullB.append(_b[arrayPos].substr(13, 7).c_str()).append("\n");
		fullB.append(_b[arrayPos].substr(20, 7).c_str()).append("\n");
		fullB.append("..").append(_b[arrayPos].substr(27, 3).c_str()).append("..\n");
		fullB.append("..").append(_b[arrayPos].substr(30, 3).c_str()).append("..\n");
		fullB.append("\n");
	}
	return fullB;
}
