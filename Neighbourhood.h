#ifndef Neighbourhood_H
#define Neighbourhood_H

#include"Box.h"
#include<Vector>
using namespace std;

class Neighbourhood
{
private:

	Box * _box;
	Piece * _pieces[13];
	FILE * _logFile;
	double _currentEnergy;
	long _currentStep;
	int _solutionsFound;
	int _bestResult;
	double _currentTemperature;
	int _pieceDetails[13][3]; //pieceDetails[pieceId][0] == PieceId		pieceDetails[pieceId][1] == Ori		pieceDetails[pieceId][2] == Pos
	int _neighbourChange[13][3];
	double _neighbourEnergy[13]; // = energy
	void calculateCurrentEnergy();
public:
	void generateSolution();
	void generateNeighbourhood(int neighbourHood);
	Neighbourhood(Box * box);
	Neighbourhood(Box * box, Piece * pieces[]);
	//Box getBox();
	void solve();
	double assignProbability(int neighbourHood);
	void setPiece(Piece * piece, int i){_pieces[i] = piece;};
};

#endif