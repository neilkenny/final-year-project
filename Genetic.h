#ifndef Genetic_H
#define Genetic_H

#include"Box.h"
#include"Chromosome.h"
#include<Vector>
using namespace std;
const int POP_SIZE = 20;
const long MAX_NO_OF_GENERATIONS = 1000;
class Genetic
{
private:
	
	vector<Chromosome> _currentPopulation;
	vector<Chromosome> _newPopulation;
	Box * _box;
	FILE * _logFile;
	Piece * pieces[13];
	int _solutionsFound;
	int _bestResult;
	long _noOfGenerations;
public:
	void generatePopulation(int sizeOfPopulation);
	int chooseChromosomeForMating();
	Genetic(Box * box);
	Genetic(Box * box, Piece * pieces[]);
	//Box getBox();
	void solve();
	void setPiece(Piece * piece, int i){pieces[i] = piece;};
	void mutateChromosome(Chromosome * c);
	void createOffspring(int parent1, int parent2);
};

#endif