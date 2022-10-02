#include "Chromosome.h"

Chromosome::Chromosome()
{
	for (int i=0; i<13; i++)
	{
		_genes[i] = new Gene();
	}
	_fitness = 0;
}

Chromosome::~Chromosome()
{
	/*for (int i=0; i<13; i++)
	{
		delete _genes[i];
	}*/
}
Chromosome::Chromosome(Box * box)
{
	_box = box;
	for (int i=0; i<13; i++)
	{
		_genes[i] = new Gene();
	}
	_fitness = 0;
}

void Chromosome::emptyBox()
{
	for (int x=0; x<4; x++)
	{
		for (int y=0; y<4; y++)
		{
			for (int z=0; z<4; z++)
			{
				_box->setCurrentStateElement(x,y,z,-1);
			}
		}
	}
}

void Chromosome::createGene(Piece * piece, int ori, int pos)
{
	_genes[piece->getPieceId()]->setOrientation(ori);
	_genes[piece->getPieceId()]->setPosition(pos);
}

void Chromosome::evaluateFitness(FILE * logFile)
{
	//Box * box = 
	int count = 0;
	for (int i=0; i<13; i++)
	{
		_box->placePiece(_genes[i]->getPiece(),_genes[i]->getOrientation(),_genes[i]->getPosition());
	}
	fprintf(logFile, "\n");
	for (int x=0; x<4; x++)
	{
		for (int y=0; y<4; y++)
		{
			for (int z=0; z<4; z++)
			{
				cout << x << y << z << " " << _box->getCurrentStateElement(x,y,z) << "\n";
				fprintf(logFile, "%i%i%i %i\n",x,y,z,_box->getCurrentStateElement(x,y,z));
				if (_box->getCurrentStateElement(x,y,z) == -1)
				{
					count++;
				}
			}
		}

	}
	_fitness =  count;
	emptyBox();
}