#ifndef SimulatedAnnealing_H
#define SimulatedAnnealing_H

#include"Box.h"
#include<Vector>
using namespace std;

class SimulatedAnnealing
{
private:

	Box * _box;
	Piece * _pieces[13];
	FILE * _logFile;
	int _cycles;
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
	void generateNeighbour(int neighbour);
	SimulatedAnnealing(Box * box);
	SimulatedAnnealing(Box * box, Piece * pieces[]);
	//Box getBox();
	void solve();
	double assignProbability(int neighbour);
	void setPiece(Piece * piece, int i){_pieces[i] = piece;};
};

#endif