#include "SimulatedAnnealing.h"
#include<time.h>

const double STARTING_TEMP = 300;
const int NO_OF_CYCLES = 10;
const double COOLING_RATE = 0.1;
//#include<stdio.h>
SimulatedAnnealing::SimulatedAnnealing(Box * g, Piece * p[])
{
	//load the box and pieces
	_logFile = fopen("SimulatedAnnealingLogFile.txt", "w");
	_box = g;
	_currentTemperature = STARTING_TEMP;
	_cycles = 0;
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
	_cycles = 0;
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

void SimulatedAnnealing::solve()
{
	char dateStr [9];
	char timeStr [9];
	_strdate( dateStr);
	_strtime( timeStr );
	int intTemp = STARTING_TEMP;
	int intCool = COOLING_RATE * 100;
	fprintf(_logFile, "Simulated Annealing started on %s at %s\n", dateStr, timeStr);
	fprintf(_logFile, "Starting Temperature = : %i\n Cooling Rate = %i/100\n Number of Cycles = %i\n", intTemp, intCool, NO_OF_CYCLES);
	srand((unsigned)time(NULL));
	generateSolution();
	while (_cycles < NO_OF_CYCLES && _currentEnergy > 0)
	{
		if (_currentTemperature < 3)
		{
			_currentTemperature = STARTING_TEMP;
			_cycles++;
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
		//Allow the user to manually increase the temperature
		if(::GetAsyncKeyState(VK_SPACE))
		{
			
			_currentTemperature += 2;
			cout << "Increasing temperature to " << _currentTemperature;
			fprintf(_logFile, "Increasing Temperature To = %d\n", _currentTemperature);

		}
		//Generate a neighbour
		generateNeighbour(_currentStep % 13);
		double randNum = 0;
		randNum = rand() % 1000;
		randNum = randNum/1000;
		//Decide whether or not to move to the neighbour state
		if (_neighbourEnergy[_currentStep%13] < _currentEnergy || randNum > assignProbability(_currentStep%13))
		{
			//remove the piece to be changed
			_box->removePiece(_pieces[_currentStep%13]);
			for (int i=0; i<13; i++) 
			{
				//Place all the other pieces again in case pieces were overlapping and removing piece causes an element to be empty that actually isn't
				if(i != _currentStep%13)
				{
					_box->placePiece(_pieces[i],_pieceDetails[i][1], _pieceDetails[i][2]);
				}
			}
			//place the new piece
			_box->placePiece(_pieces[_currentStep%13],_neighbourChange[_currentStep%13][1], _neighbourChange[_currentStep%13][2]);
			//update the piece details array
			_pieceDetails[_currentStep%13][1] = _neighbourChange[_currentStep%13][1];
			_pieceDetails[_currentStep%13][2] = _neighbourChange[_currentStep%13][2];
			//calculate teh energy of the current solution
			calculateCurrentEnergy();
			cout << "Temperature = " << _currentTemperature << "\n";
			
		}
		_currentStep++;
		//If the temperature is low reduce the cooling rate
		if (_currentTemperature < 30)
		{
			_currentTemperature = _currentTemperature - (COOLING_RATE/150);
		}
		else
		{
			_currentTemperature = _currentTemperature - COOLING_RATE;
		}
		
	}
	fprintf(_logFile, "Search Finished\nNumber of steps:%i\n", _currentStep);
	fclose(_logFile);
}

double SimulatedAnnealing::assignProbability(int neighbour)
{
	double value = 0;
	value = _currentEnergy - ((_currentEnergy - _neighbourEnergy[neighbour])/(_currentTemperature/STARTING_TEMP)); 
	return value;
}

void SimulatedAnnealing::generateNeighbour(int pieceToMove) //moves the piece specified by the parameter to a random position/orientation
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

void SimulatedAnnealing::calculateCurrentEnergy() //calculates the current energy of the solution
{
	double count = 0;
	int intTemp = _currentTemperature;
	fprintf(_logFile, "Piece %i moved\n", _currentStep % 13);
	fprintf(_logFile, "Current Temperature : %i\n", intTemp);
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

void SimulatedAnnealing::generateSolution() //Generates random positions/orientations for each piece
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