#ifndef _Chromosome_H_
#define	_Chromosome_H_
#include "Gene.h"
#include "Piece.h"
#include "Box.h" 

class Chromosome
{

public:
	Chromosome();
	~Chromosome();
	Chromosome(Box * box);
	void evaluateFitness(FILE * logFile);
	void createGene(Piece * piece, int ori, int pos);
	int getFitness(){return _fitness;};
	Gene * getGene(int geneNumber){return _genes[geneNumber];};
	void emptyBox();
private:
	Box * _box;
	Gene * _genes[13];
	int _fitness;
	
};


#endif