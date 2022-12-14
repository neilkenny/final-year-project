#ifndef Gene_H
#define Gene_H
#include "Piece.h"
class Gene
{
protected:
	//int _pieceId;
	int _orientation;
	int _position;
	Piece * _piece;
	bool _tagged;

public:
	Gene();
	Gene(Piece * piece, int position, int orie ntation);
	void mutate();
	void setTag(bool value){_tagged = value;};
	bool getTag(){return _tagged;};
	void setPiece(Piece * piece){_piece = piece;};
	void setOrientation(int ori){_orientation = ori;};
	void setPosition(int pos){_position = pos;};
	Piece *  getPiece(){return _piece;};
	int getOrientation(){return _orientation;};
	int getPosition(){return _position;};
};

#endif
