#include "DepthFirst.h"
#include<time.h>

//#include<stdio.h>
char convertToChar(int value);
int charToInt(char value);
int StringToInt(string num);
DepthFirst::DepthFirst(Box * g, Piece * p[])
{
	//load the box and pieces
	box = g;
	_randomize = false;
	for(int i=0; i<13; i++)
	{
		pieces[i] = p[i];
	}
	nextEmptyElement[0] = nextEmptyElement[1] = nextEmptyElement[2] = 0;
	noOfSolutions=0;
}

DepthFirst::DepthFirst(Box * g)
{
	box = g;
	_randomize = false;
	nextEmptyElement[0] = nextEmptyElement[1] = nextEmptyElement[2] = 0;
	noOfSolutions=0;
}
void DepthFirst::solve()
{
	bool exiting = false;
	int noOfCorrectAnswers = 0;
	char dateStr [9];
    char timeStr [9];	
	srand((unsigned)time(NULL));

	//Clear all the log files
	FILE * logFile;
	logFile = fopen("logFile.txt", "w");
	fclose(logFile);
	logFile = fopen("piecesPlaced.txt", "w");
	fclose(logFile);
	logFile = fopen("piecesRemoved.txt", "w");
	fclose(logFile);
	
	//Print the date and time into the log file
    _strdate( dateStr);
    _strtime( timeStr );
    logFile = fopen("logFile.txt", "a");
	if(!_randomize)
	{
		fprintf(logFile, "Depth-first search started on %s at %s \n",dateStr, timeStr);
	}
	else
	{
		fprintf(logFile, "Randomized search started on %s at %s \n",dateStr, timeStr);
	}
	fclose(logFile);	//log file is closed so time and date is saved no matter what happens
	logFile = fopen("logFile.txt", "a");
	positionStore posStore;
	///Check which pieces fit in the next empty element		->(0,0,0)
	for(int h=0; h<13; h++)											//Piece
	{
		for(int j=0; j<pieces[h]->getNoOfOrientations(); j++)		//Orientation
		{
			for(int k=0; k<pieces[h]->getNoOfPositions() ; k++)		//Position
			{
				//if the piece occupies the next empty element then add it to the list
				if(pieces[h]->getOrientationPos(j,k,nextEmptyElement[0], nextEmptyElement[2]) != "-1" && pieces[h]->getOrientationPos(j,k, nextEmptyElement[0], nextEmptyElement[2]).find(convertToChar(nextEmptyElement[1]),0) != string::npos)
				{
					piecePositions x;
					x.push_back(h);
					x.push_back(j);
					x.push_back(k);
					posStore.push_back(x);
				}
			}
		}
	}

	open.push_back(posStore);
	posStore.clear();	
	int i=0;
	while(open[0].size() != 0) //While all possible solutions have not been checked
	{
		while(open[i].size() != 0) 
		{
			//Allow the user to quit at any time
			if(::GetAsyncKeyState(VK_ESCAPE))
			{
				cout << "Exiting....";
				_strdate( dateStr);
				_strtime( timeStr );
				fprintf(logFile, "Depth-first search exited before finished on %s at %s\n", dateStr, timeStr);
				exiting = true;
				break;

			}
			//Randomize the choice of pieces that are placed.
			if(::GetAsyncKeyState('R') && 0x8000f)
			{
				if(!_randomize)
				{
					_randomize = true;
				}
				else
				{
					_randomize = false; 
				}
				cout << "Randomize = " << _randomize << "\n";
				fprintf(logFile, "Randomize set to %i\n", _randomize);
			}
			//Place the next piece
			if(!_randomize)
			{
				box->placePiece(pieces[open[i][0][0]], open[i][0][1], open[i][0][2]);	//(piece, orientation, position);
			}
			else
			{
				_rndPiece = rand()% open[i].size();
				box->placePiece(pieces[open[i][_rndPiece][0]],open[i][_rndPiece][1], open[i][_rndPiece][2]);
			}

			//Add the placed piece to closed
			if(closed.size() > i)
			{
				if (!_randomize) 
				{
					closed[i].push_back(open[i][0]);
				}
				else
				{
					closed[i].push_back(open[i][_rndPiece]);
				}
				
			}
			else
			{
				if (!_randomize)
				{
					posStore.push_back(open[i][0]);
					closed.push_back(posStore);  
				}
				else
				{
					posStore.push_back(open[i][_rndPiece]);
					closed.push_back(posStore);  
				}
			}

			posStore.clear();
			//Remove the placed piece from open
			if(!_randomize)
			{
                open[i].erase(open[i].begin());
			}
			else
			{
				positionStore::iterator it;
				//it = &open[i][_rndPiece];
				open[i].erase(it);
			}
			i++;
			
			//Find The Next Empty Element and add all suitable piece orientations/positions
			findNextEmptyElement();
			for(int p=0; p<13; p++)	///Check which pieces fit in the next empty element
			{
				if(pieces[p]->getPlaced() != true)
				{
					for(int o=0; o<pieces[p]->getNoOfOrientations(); o++)
					{
						for(int pos=0; pos<pieces[p]->getNoOfPositions(); pos++)
						{
							if( pieces[p]->getOrientationPos(o,pos,nextEmptyElement[0], nextEmptyElement[2]) != "-1"	&& pieces[p]->getOrientationPos(o,pos, nextEmptyElement[0], nextEmptyElement[2]).find(convertToChar(nextEmptyElement[1])) != string::npos)	//if the pos/orientation of this piece occupies the next empty element
							{
								bool match = true;
								//This loop checks to see whether the pos/orientation of the piece clashes with any of the pieces in the box
								for(int a=0; a<4; a++)
								{
									for(int b=0; b<4; b++)
									{
										if(pieces[p]->getOrientationPos(o,pos,a, b) != "-1") 
										{
											for(int c=0; c<pieces[p]->getOrientationPos(o,pos,a, b).length(); c++)
											{
                                                if(box->getCurrentStateElement(a, charToInt(pieces[p]->getOrientationPos(o,pos,a, b)[c]), b) != -1)
												{
													match = false;
												}
											}
										}
									}
								}
								if(match == true)
								{
                                    piecePositions x;
									x.push_back(p);
									x.push_back(o);
									x.push_back(pos);
									posStore.push_back(x);
								}
							}
						}				
					}
				}	
			}
			open.push_back(posStore);
			if(open.size() > i)
			{
				for (int j=0; j<posStore.size(); j++)
				{
					open[i].push_back(posStore[j]);
				}	
			}
			else
			{
				open.push_back(posStore); 
			}

			posStore.clear();
		}
		
		if(exiting == true)	//if the user has chosen to exit then skip this section
		{
			break;
		}

		//check to see how many empty spaces are left in the box
		int count =0;
		for (int a=0; a<4; a++)
		{
			for(int b=0; b<4; b++)
			{
				for (int c=0; c<4; c++)
				{
					
					if(box->getCurrentStateElement(a,b,c) == -1)
					{
						count++;
					}
				}
			}
		}
		//if there are less than five empty spaces in the box then record the solution in the log
		if (count == 0)			//*/(count < 5)
		{
			//cout <<  "Number Of Empty Spaces:" << count << "\n";
			fprintf(logFile, "Number Of Empty Spaces:%i\n", count);
			noOfCorrectAnswers ++;
			for (int a=0; a<4; a++)
			{
				for(int b=0; b<4; b++)
				{
					for (int c=0; c<4; c++)
					{
						fprintf(logFile, "%i%i%i %i\n",a,b,c,box->getCurrentStateElement(a,b,c));
						cout << a << b << c << " " << box->getCurrentStateElement(a,b,c) << "\n";
					}
				}
			}
			for (int a=0 ;a<closed.size(); a++)
			{
				fprintf(logFile, "Place Piece %i next in the following position:\n", a);
				cout << "closed[a][closed[a].size()-1][0] = " << closed[a][closed[a].size()-1][0] << "\n";
				cout << "closed[a][closed[a].size()-1][1] = " << closed[a][closed[a].size()-1][1] << "\n";
				cout << "closed[a][closed[a].size()-1][2] = " << closed[a][closed[a].size()-1][2] << "\n";
				
				for (int b=0; b<4; b++)
				{
					for (int c=0; c<4; c++)
					{
						fprintf(logFile, "%i", StringToInt(pieces[closed[a][closed[a].size()-1][0]]->getOrientationPos(closed[a][closed[a].size()-1][1],closed[a][closed[a].size()-1][2],b,c)));
					}
					fprintf(logFile, "\n");
				}
				fprintf(logFile, "\n");
				
			}
		}
		//remove the last placed piece and decrement i
		noOfSolutions++;
		box->removePiece(pieces[closed[i-1][closed[i-1].size()-1][0]]);	
		i--;
	}
	//Search finished, record time and date in log and close file
	_strdate( dateStr);
	_strtime( timeStr );
	fprintf(logFile, "Depth-first search ended on %s at %s\n",dateStr,timeStr);
	fprintf(logFile, "Number of correct answers = %i", noOfCorrectAnswers);
	fprintf(logFile, "Number of solutions searched = %i", noOfSolutions);
	fclose(logFile);
	//empty the box
	for (int x=0; x<4; x++)
	{
		for (int y=0; y<4; y++)
		{
			for (int z=0; z<4; z++)
			{
				box->setCurrentStateElement(x,y,z,-1);
			}
		}
	}
	cout << "Exited\n";
}

void DepthFirst::findNextEmptyElement()
{
	int lowest=4;
	for(int y=0; y<4; y++)
	{
		if(y>lowest)
		{
			break;
		}
		for(int z=0; z<4; z++)
		{
			for(int x=0; x<4; x++)
			{
				if(box->getCurrentStateElement(x,y,z) == -1)
				{
					if(y < lowest)
					{
						lowest = y;
						nextEmptyElement[0] = x;
						nextEmptyElement[1] = y;
						nextEmptyElement[2] = z;
					}
					
				}
			}
		}
	}
}


int StringToInt(string num)  //Converts a string to an integer
{
	string n = num;
	int sum=0;
	for(int i=0; i < n.length(); i++)
	{
		if(num[i] == '0')
		{
		}
		else if(num[i] == '1')
		{
			sum = sum + pow(10, (double)(n.length() - (i+1)));
		}
		else if(num[i] == '2')
		{
			sum = sum + (2 * pow(10, (double)(n.length() - (i+1))));
		}
		else if(num[i] =='3')
		{
			sum = sum + (3 * pow(10, (double)(n.length() - (i+1))));		
		}
		else if(num[i]=='4')
		{
			sum = sum + (4 * pow(10, (double)(n.length() - (i+1))));
		}
		else if(num[i]=='5')
		{
			sum = sum + (5 * pow(10, (double)(n.length() - (i+1))));
		}
		else if(num[i]=='6')
		{
			sum = sum + (6 * pow(10, (double)(n.length() - (i+1))));
		}
		else if(num[i]=='7')
		{
			sum = sum + (7 * pow(10, (double)(n.length() - (i+1))));
		}
		else if(num[i]=='8')
		{
			sum = sum + (8 * pow(10, (double)(n.length() - (i+1))));
		}
		else if(num[i]=='9')
		{
			sum = sum + (9 * pow(10, (double)(n.length() - (i+1))));
		}
	}
	cout << num << " " << sum << "\n";
	return sum;
}
