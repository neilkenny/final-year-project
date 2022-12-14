#include "Gene.h"
#include "time.h"
Gene::Gene(Piece * piece, int position, int orientation)
{
	_tagged = false;
	_piece = piece;
	_position = position;
	_orientation = orientation;
}

Gene::Gene()
{
	_position =  0;
	_orientation =0;
}


void Gene::mutate()
{
	srand((unsigned)time(NULL));
	_position = rand() % _piece->getNoOfPositions();
	_orientation = rand() % _piece->getNoOfOrientations();
}