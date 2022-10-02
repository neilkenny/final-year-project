#ifndef Box_H
#define Box_H

#include "piece.h"
#include<iostream>
class Box
{
private:
	int currentState[4][4][4];     //y = 4 or 6?
	Piece * currentPiece;
	int piecePos[4][4];
public:
	Box();
	void setPiece(Piece * ptrPiece);
	int * getPtrElement(int x, int y, int z);
	void setPiecePos(Piece * ptrPiece, int leftX, int upZ);
    Piece * getPiece();
	bool dropPiece();
	
	int getCurrentStateElement(int x, int y, int z);
	void setCurrentStateElement(int x, int y, int z, int value){currentState[x][y][z] = value;};
	//int getPieceOrientation();
	void rotatePieceX();
	void rotatePieceY();
	void rotatePieceZ();
	bool movePieceMoreX();
	bool movePieceLessX();
	bool movePieceMoreZ();
	bool movePieceLessZ();
	int getPieceLeftX();
	int getPieceNearZ();
	void placePiece(Piece * piece, int orientation, int position);
	void removePiece(Piece * piece);
	void drawPiecePosPlan();
};

#endif