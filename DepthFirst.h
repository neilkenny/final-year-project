#ifndef DepthFirst_H
#define DepthFirst_H

#include"Box.h"
#include "World.h"
#include "DrawableEntity.h"
#include<Vector>
using namespace std;

typedef std::vector<int> piecePositions; //Stores the piece, its orientation and its position. e.g. piece 0, ori 0, pos 1 = -1 -1 -1 -1
typedef std::vector<piecePositions>positionStore; //stores which piecePositions have/haven't been used					    -1 -1 -1 -1
typedef std::vector<positionStore>stateStore; //stores a position store for each state of the puzzle.				        -1 -1 01 -1
class DepthFirst																										 // -1  0  0  0
{																														
private:
	bool _randomize;
	int _rndPiece;
	Box * box;
	long noOfSolutions;
	Piece * pieces[13];
	stateStore open;
	stateStore closed;
	int nextEmptyElement[3];
	
	void findNextEmptyElement();

public:
	void setPiece(int i, Piece * p){pieces[i] = p;};
	DepthFirst();
	DepthFirst(Box * box);
	DepthFirst(Box * box, Piece * pieces[]);
	//Box getBox();
	void solve();
};

#endif