#include "Genetic.h"
#include<time.h>

//#include<stdio.h>
Genetic::Genetic(Box * g, Piece * p[])
{
	//load the box and pieces
	_box = g;
	_noOfGenerations = 0;
	_solutionsFound = 0;
	_bestResult = 59;
	for(int i=0; i<13; i++)
	{
		pieces[i] = p[i];
	}
}

Genetic::Genetic(Box * g)
{
	_box = g;
	_noOfGenerations = 0;
	_solutionsFound = 0;
	_bestResult = 59;
}
void Genetic::solve()
{
	char dateStr [9];
	char timeStr [9];
	_logFile = fopen("genetic.txt", "w");
	fclose(_logFile);
	_logFile = fopen("genetic.txt", "a");
	_strdate( dateStr);
	_strtime( timeStr );
	fprintf(_logFile, "Genetic Algorithm Started on %s at %s \n",dateStr, timeStr);
	srand((unsigned)time(NULL));
	//Generate Population
	generatePopulation(POP_SIZE);
 	while (_noOfGenerations < MAX_NO_OF_GENERATIONS)
	{	
		if(::GetAsyncKeyState(VK_ESCAPE))
		{
			_strdate( dateStr);
			_strtime( timeStr );
			fprintf(_logFile, "Genetic Algorithm  before finished on %s at %s\n", dateStr, timeStr);
			break;

		}
		cout << "Number of solutions found:" << _solutionsFound << "\n";

		//Select chromosomes for mating and produce offspring
		cout << "Creating Offspring...\n";
		while (_newPopulation.size() < POP_SIZE)
		{
			createOffspring(chooseChromosomeForMating(), chooseChromosomeForMating());
			if (rand() % 100 >= 95)
			{
				mutateChromosome(&_newPopulation[_newPopulation.size()-1]);
			}
		}
		cout << "Generation:" << _noOfGenerations << " Best Result:" << _bestResult << "\n"; 
		_bestResult = 59;
		_currentPopulation.clear();
		for (int i=0; i<POP_SIZE; i++)
		{
			_currentPopulation.push_back(_newPopulation[i]);
			_currentPopulation[i].evaluateFitness(_logFile);
			if(_currentPopulation[i].getFitness() < _bestResult)
			{
				_bestResult = _currentPopulation[i].getFitness();
			}
		}
		_newPopulation.clear();
		_noOfGenerations++;
	}
	_strdate( dateStr);
	_strtime( timeStr );
	fprintf(_logFile, "Genetic search ended on %s at %s\n",dateStr,timeStr);
	fprintf(_logFile, "Number of Generations searched = %i\n", _noOfGenerations);
	fprintf(_logFile, "Best result = %i empty Spaces\n", _bestResult);
	fclose(_logFile);
}

void Genetic::mutateChromosome(Chromosome * x)
{
	x->getGene(rand()%12)->mutate();

}
void Genetic::generatePopulation(int popSize)
{
	
	int randPos = 0;
	int randOri = 0;
	cout << "Generation Population...\n"; 
	for (int i=0; i<popSize; i++)
	{
		Chromosome * chro = new Chromosome(_box);
		
		for (int g=0; g<13; g++) 
		{
			randPos = rand() % pieces[g]->getNoOfPositions();
			randOri = rand() % pieces[g]->getNoOfOrientations();
			chro->createGene(pieces[g],randOri,randPos);
			chro->getGene(g)->setPiece(pieces[g]);
		}
		chro->evaluateFitness(_logFile);
		if (chro->getFitness() < _bestResult)
		{
			_bestResult = chro->getFitness();
		}
		if(chro->getFitness() == 0)
		{
			_solutionsFound++;
		}
		_currentPopulation.push_back(*chro);
		delete chro;
	}
}

int Genetic::chooseChromosomeForMating()
{
	srand( (unsigned)time( NULL ) );
	int choice = 0;
	while(true)
	{
		choice = rand() % POP_SIZE;
		if(_currentPopulation[choice].getFitness()/59 + (rand()%20) < 3)
		{
			return choice;
		}
		//cout << "Choice:" << choice << " Fitness:" << _currentPopulation[choice].getFitness() << "Result:" << _currentPopulation[choice].getFitness() + (rand()%10) << "\n";
	}
}

void Genetic::createOffspring(int parent1, int parent2)
{
	Chromosome * off1 = new Chromosome(_box);
	Chromosome * off2 = new Chromosome(_box);
	srand( (unsigned)time( NULL ) );
	
	for (int i=0; i<13; i++)
	{
		if (rand()%10 + _currentPopulation[parent1].getFitness() > rand()%10 + _currentPopulation[parent2].getFitness())
		{
			_currentPopulation[parent1].getGene(i)->setTag(true);
		}
		else
		{
			_currentPopulation[parent2].getGene(i)->setTag(true);
		}
		
		//cout << "CreateOffspring: parent1->Gene(" << i << ")PieceID = " << _currentPopulation[parent1].getGene(i)->getPiece()->getPieceId() << "\n";
		//cout << "CreateOffspring: parent2->Gene(" << i << ")PieceID = " << _currentPopulation[parent2].getGene(i)->getPiece()->getPieceId() << "\n";
		if (_currentPopulation[parent1].getGene(i)->getTag() == true)
		{
			
			off1->createGene(_currentPopulation[parent1].getGene(i)->getPiece(),_currentPopulation[parent1].getGene(i)->getOrientation(), _currentPopulation[parent1].getGene(i)->getPosition());
			off1->getGene(i)->setPiece(_currentPopulation[parent1].getGene(i)->getPiece());
			off2->createGene(_currentPopulation[parent2].getGene(i)->getPiece(),_currentPopulation[parent2].getGene(i)->getOrientation(), _currentPopulation[parent2].getGene(i)->getPosition());
			off2->getGene(i)->setPiece(_currentPopulation[parent2].getGene(i)->getPiece());
		}
		else
		{
            off2->createGene(_currentPopulation[parent1].getGene(i)->getPiece(),_currentPopulation[parent1].getGene(i)->getOrientation(), _currentPopulation[parent1].getGene(i)->getPosition());
			off2->getGene(i)->setPiece(_currentPopulation[parent2].getGene(i)->getPiece());
			off1->createGene(_currentPopulation[parent2].getGene(i)->getPiece(),_currentPopulation[parent2].getGene(i)->getOrientation(), _currentPopulation[parent2].getGene(i)->getPosition());
			off1->getGene(i)->setPiece(_currentPopulation[parent1].getGene(i)->getPiece());
		}
	}

	_newPopulation.push_back(*off1);
	_newPopulation.push_back(*off2);
	delete off1;
	delete off2;


}