#include "SimulatedAnnealing.h"
#include<time.h>

const double STARTING_TEMP = 10000;

//#include<stdio.h>
SimulatedAnnealing::SimulatedAnnealing(Box * g, Piece * p[])
{
	//load the box and pieces
	_logFile = fopen("SimulatedAnnealingLogFile.txt", "w");
	_box = g;
	_currentTemperature = STARTING_TEMP;
	_currentEnergy = 1;
	_currentStep = 0;
	_solutionsFound = 0;
	_bestResult = 59;
	for(int i=0; i<13; i++)
	{
		_pieces[i] = p[i];
		_pieceDetails[i][0] = i;
		_pieceDetails[i][1] = _pieceDetails[i][2] = 0;
	}
}

SimulatedAnnealing::SimulatedAnnealing(Box * g)
{
	_box = g;
	_logFile = fopen("SimulatedAnnealingLogFile.txt", "w");
	_solutionsFound = 0;
	_bestResult = 59;
	_currentStep = 0;
	_currentEnergy = 1;
	_currentTemperature = STARTING_TEMP;
	for(int i=0; i<13; i++)
	{
		_neighbourChange[i][0] = i;
		_neighbourChange[i][1] = _neighbourChange[i][2] = 0;
		_pieceDetails[i][0] = i;
		_pieceDetails[i][1] = _pieceDetails[i][2] = 0;
	}
}
/*
s := s0
e := E(s)
k := 0
while k < kmax and e > emax
	sn := neighbour(s)
	en := E(sn)
	if en < e or random() < P(en - e, temp(k/kmax)) then
		s := sn; e := en
	k := k + 1
return s
*/
void SimulatedAnnealing::solve()
{
	char dateStr [9];
	char timeStr [9];
	_strdate( dateStr);
	_strtime( timeStr );
	fprintf(_logFile, "Simulated Annealing started on %s at %s\n", dateStr, timeStr);
	srand((unsigned)time(NULL));
	generateSolution();
	while (_currentTemperature > 0 || _currentEnergy == 0)
	{
		if (_currentTemperature < 20 && _currentStep < 100000000)
		{
			_currentTemperature = STARTING_TEMP;
		}
		//Allow the user to quit at any time
		if(::GetAsyncKeyState(VK_ESCAPE))
		{
			cout << "Exiting....";
			_strdate( dateStr);
			_strtime( timeStr );
			fprintf(_logFile, "Simulated Annealing search exited before finished on %s at %s\n", dateStr, timeStr);
			break;

		}
		if(::GetAsyncKeyState(VK_SPACE))
		{
			
			_currentTemperature += 1000;
			cout << "Increasing temperature to " << _currentTemperature;
			fprintf(_logFile, "Current Temperature = %d\n", _currentTemperature);

		}
		generateSimulatedAnnealing(_currentStep % 13);
		double randNum = 0;
		randNum = rand() % 1000;
		randNum = randNum/1000;
		
		if (_neighbourEnergy[_currentStep%13] < _currentEnergy || randNum > assignProbability(_currentStep%13))
		{
			_box->removePiece(_pieces[_currentStep%13]);
			for (int i=0; i<13; i++) 
			{
				if(i != _currentStep%13)
				{
					_box->placePiece(_pieces[i],_pieceDetails[i][1], _pieceDetails[i][2]);
				}
			}
			_box->placePiece(_pieces[_currentStep%13],_neighbourChange[_currentStep%13][1], _neighbourChange[_currentStep%13][2]);
			_pieceDetails[_currentStep%13][1] = _neighbourChange[_currentStep%13][1];
			_pieceDetails[_currentStep%13][2] = _neighbourChange[_currentStep%13][2];
			calculateCurrentEnergy();
			cout << "Probability:" << assignProbability(_currentStep%13) << "\n" << "Rand Num:"<<  randNum << "\n" << _currentEnergy << "\n";
		}
		_currentStep++;
		_currentTemperature = _currentTemperature - 0.1;
	}
	fprintf(_logFile, "Search Finished\nNumber of steps:%i\n", _currentStep);
	fclose(_logFile);
}

double SimulatedAnnealing::assignProbability(int SimulatedAnnealing)
{
	double value = 0;
	value = _currentEnergy - ((_currentEnergy - _neighbourEnergy[SimulatedAnnealing])/(_currentTemperature/STARTING_TEMP)); //no dividing by zero
	return value;
}

void SimulatedAnnealing::generateSimulatedAnnealing(int pieceToMove)
{
	int randPos = 0;
	int randOri = 0;
	Box * newBox = new Box();
	randPos = rand() % _pieces[pieceToMove]->getNoOfPositions();
	randOri = rand() % _pieces[pieceToMove]->getNoOfOrientations();
	//_box->removePiece(_piece[pieceToMove]);
	for (int i=0; i<13; i++) 
	{
		if(i != pieceToMove)
		{
			newBox->placePiece(_pieces[i],_pieceDetails[i][1], _pieceDetails[i][2]);
			
		}
	}
	newBox->placePiece(_pieces[pieceToMove],randOri, randPos);
	_neighbourChange[pieceToMove][1] = randOri;
	_neighbourChange[pieceToMove][2] = randPos;
	double count = 0;
	for (int x=0; x<4; x++)
	{
		for (int y=0; y<4; y++)
		{
			for (int z=0; z<4; z++)
			{
				if (newBox->getCurrentStateElement(x,y,z) == -1)
				{
					count++;
				}
			}
		}
	}
	count = count/59;
	_neighbourEnergy[pieceToMove] = count;

}

void SimulatedAnnealing::calculateCurrentEnergy()
{
	double count = 0;
	fprintf(_logFile, "Piece %i moved\n", _currentStep % 13);
	for (int x=0; x<4; x++)
	{
		for (int y=0; y<4; y++)
		{
			for (int z=0; z<4; z++)
			{
				if (_box->getCurrentStateElement(x,y,z) == -1)
				{
					count++;
				}
			}
		}
	}
	if(count < 16)
	{
		for (int x=0; x<4; x++)
		{
			for (int y=0; y<4; y++)
			{
				for (int z=0; z<4; z++)
				{
					fprintf(_logFile, "%i%i%i %i\n",x,y,z,_box->getCurrentStateElement(x,y,z));
				}
			}
		}
		int emptySpaces = count;
		int curEnergy = _currentEnergy * 1000;
		fprintf(_logFile, "Current Energy:%i\nNumber of empty spaces:%d\n", curEnergy, emptySpaces);
	}
	
	count = count/59;
	_currentEnergy = count;
}

void SimulatedAnnealing::generateSolution()
{
	int randPos = 0;
	int randOri = 0;
	for (int i=0; i<13; i++)
	{
		randPos = rand() % _pieces[i]->getNoOfPositions();
		randOri = rand() % _pieces[i]->getNoOfOrientations();
		_box->placePiece(_pieces[i], randOri, randPos);
		_pieceDetails[i][1] = randOri;
		_pieceDetails[i][2] = randPos;
		
	}
	double count = 0;
	for (int x=0; x<4; x++)
	{
		for (int y=0; y<4; y++)
		{
			for (int z=0; z<4; z++)
			{
				if (_box->getCurrentStateElement(x,y,z) == -1)
				{
					count++;
				}
			}
		}
	}
	count = count /59;
	_currentEnergy = count;
}