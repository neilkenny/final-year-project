#include"piece.h"
#include<cmath>
//*************************************************************************************
//*To do:fix getPieceOrientation()??       Are all these needed????
//*droppedPieceStats()
//*orientation/position
//*StringToInt to generate a solution id
//*
//*
//**************************************************************************************

int Piece::StringToInt(string num)  //Converts a string to an integer
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

char convertToChar(int value)	//converts an integer to a char
{
	string result = "";
	if(value == 0)
	{
		return '0';
	}
	else if(value == 1)
	{
		return '1';
	}
	else if(value == 2)
	{
		return '2';
	}
	else if(value == 3)
	{
		return '3';
	}
	else if(value == 4)
	{
		return '4';
	}
}

int charToInt(char value)   //converts a char to an integer
{

	if(value == '0')
	{
		return 0;
	}
	else if(value == '1')
	{
		return 1;
	}
	else if(value == '2')
	{
		return 2;
	}
	else if(value == '3')
	{
		return 3;
	}
	else if(value == '4')
	{
		return 4;
	}
	else if(value == '5')
	{
		return 5;
	}
	else if(value == '6')
	{
		return 6;
	}
	else if(value == '7')
	{
		return 7;
	}
	else if(value == '8')
	{
		return 8;
	}
	else if(value == '9')
	{
		return 9;
	}
}
string translatePosition(string num, int yValue)
{
	if(num[0] == '0')
	{
		num[0] = convertToChar(yValue);
		for(int i=1; i< num.length(); i++)
		{
			int x;
			x = charToInt(num[i])+yValue;
			num[i] = convertToChar(x);
		}
	}
	else
	{
		for(int i=0; i<num.length(); i++)
		{
			int x;
			x = charToInt(num[i])+yValue;
			num[i] = convertToChar(x);
		}
	}
	return num;
}

Piece::Piece()		//Piece default constructor - Not used
{
	setDimensionsToZero();
	colour = 'r';
	GraPiece::GraPiece();

}
Piece::Piece(int pieceId)  //Piece Constructor
{
	setDimensionsToZero();
	definePiece(pieceId);
	_elapsedTime=0;
	_pieceId = pieceId;
	_pos.x = 0;
	_pos.y = 5;
	_pos.z = 0;
	_rX = 0;
	_rY = 0;
	_rZ = 0;
	_rotCorrectionX = 0;
	_rotCorrectionY = 0;
	_rotCorrectionZ = 0;

}

int Piece::getNoOfOrientations()
{
	return noOfOrientations;
}

void Piece::loadOrientations()
{
	using namespace std;
	cout << "Loading Orientations and Positions of Piece " << _pieceId << " Into Memory..." << "\n";
	noOfOrientations = 0;
	//For each possible orientation of the piece
	for(int i=0; i<24; i++)
	{
		string tempString[4][4] = {{"-1","-1","-1", "-1"}, {"-1","-1","-1", "-1"}, {"-1","-1","-1","-1"},{"-1","-1","-1","-1"}};
		//For each element in the pieces dimension array
		for(int y=0; y<3; y++)
		{
			for(int x=0; x<3; x++)
			{
				for(int z=0; z<3; z++)
				{
					//If the piece occupies this element
					if(dimension[x][y][z] == 1)
					{
						//If the piece occupies no other space in this column change the -1 to the Y value
						if(tempString[x][z] == "-1")
						{
							//tempString[x][z] = y;
							if(y == 0)
							{
								tempString[x][z] = "0";
							}
							else if(y==1)
							{
								tempString[x][z] = "1";
							}
							else
							{
								tempString[x][z] = "2";
							}
						}
						else
						{
							//If the piece occupies another space in this column append the Y value to the element
							//tempString[x][z]+=y;
							if(y == 0)
							{
								
								tempString[x][z] += "0";
							}
							else if(y==1)
							{
								tempString[x][z] += "1";
							}
							else
							{
								tempString[x][z] += "2";
							}
						}
					}
					
				}
			}
		}

		bool match = true;
		//If this isn't the first orientation
		if(noOfOrientations > 0)
		{
			//Search through each of the previous orientations to check if this is the same as any previous ones
			for(int j=0; j < noOfOrientations; j++)
			{
				if(match == true && j!=0)
				{
					break;
				}
				match = true;
				for(int x=0; x<3; x++)
				{
					if(match == false)
					{
						break;
					}
					for(int z=0; z<3; z++)
					{
						if(orientation[j][0][x][z] != tempString[x][z])
						{
							match = false;
							break;
						}
					}
				}
			}
		}
		//If this orientation of the piece is unique
		if(match == false || noOfOrientations == 0)
		{
			vector<positionVector>position;
			//Load Each Position for this orientation
			
			for(int y=0; y<(4-getHeight()+1); y++)
			{
				for(int z=0; z<(4-getDepth()+1); z++)
				{
					for(int x=0; x<(4-getLength()+1); x++)
					{
						//if this is position 0
						if(x==0 && y==0 && z==0)
						{
                            Xvector tempX;
							for(int n=0; n<4; n++)
							{
								Zvector tempZ;
								for(int m=0; m<4; m++)
								{
									tempZ.push_back(tempString[n][m]);
								}
								tempX.push_back(tempZ);
							}
							position.push_back(tempX);
							orientation.push_back(position);
						}
						else
						{
							//calculate where the piece 
							string newPosString[4][4] = {{"-1","-1","-1","-1"},{"-1","-1","-1","-1"},{"-1","-1","-1","-1"},{"-1","-1","-1","-1"}};
							Xvector tempX;
							for(int n=0; n<4; n++)
							{
								Zvector tempZ;
								for(int m=0; m<4; m++)
								{
                                    if(orientation[noOfOrientations][0][n][m] != "-1")
									{
										newPosString[n+x][m+z] = translatePosition(orientation[noOfOrientations][0][n][m], y);
									}
									tempZ.push_back(newPosString[n][m]);
								}
								
								tempX.push_back(tempZ);
							}
							orientation[noOfOrientations].push_back(tempX);
					
						}
					}
				}
			}
			noOfOrientations++;
		}
		//This is used to rotate the piece to every orientation
		rotateY();
		if (i % 4 == 3 && i != 0 && i < 19)
		{
			rotateX();
		}
		if(i == 15)
		{
			rotateZ();
		}
		if(i == 19)
		{
			rotateZ();
			rotateZ();
		}
	
	}
	rotateZ(); //rotate piece to original position
	cout << "NO OF ORIENTATIONS:" << noOfOrientations;
	
}

string Piece::getOrientationElement(int i, int x, int z)
{
	return orientation[i][0][x][z] /*orientation[i][x][z]*/;
}
void Piece::setDimensionsToZero()
{
	int x,y,z;
	for (x=0; x<3 ; x++)
	{
		for(y=0; y<3; y++)
		{
			for(z=0; z<3; z++)
			{
				dimension[x][y][z] = 0;
			}
		}
	}
}

int Piece::getHeight()
{
	int x,y,z;
	for(y=2; y>=0; y--)
	{
		for(x=0; x<3 ; x++)
		{
			for(z=0; z<3; z++)
			{
				if (getDimension(x,y,z) == 1)
				{
					return y+1;
				}
			}
		}
	}
}

int Piece::getLength()
{
	int x,y,z;
	for(x=2; x>=0; x--)
	{
		for(y=0; y<3 ; y++)
		{
			for(z=0; z<3; z++)
			{
				if (getDimension(x,y,z) == 1)
				{
					return x+1;
				}
			}
		}
	}
}

int Piece::getDepth()
{
	int x,y,z;
	for(z=2; z>=0; z--)
	{
		for(x=0; x<3 ; x++)
		{
			for(y=0; y<3 ; y++)
			{
				if (getDimension(x,y,z) == 1)
				{
					return z+1;
				}
			}
		}
	}
}
char Piece::getColour()
{
	return colour;
}
void Piece::setDimension(int x, int y, int z, int value)
{
	dimension[x][y][z] = value;
}
int Piece::getDimension(int x, int y, int z)
{
	return dimension[x][y][z];
}
int * Piece::getDimensions()
{
	return &dimension[0][0][0];
}
void Piece::setColour(char col)
{
	colour = col;
}
bool Piece::getPlaced()
{
	return placed;
}
void Piece::displayDimensions()
{
	using namespace std;
	int x,y,z;
	
	for( x=0; x<3; x++)
	{
		for(y=0; y<3; y++)
		{
			for(z=0; z<3; z++)
			{
				
				cout << x << y << z << " " << dimension[x][y][z] << "\n"; //<< " ";

			}
		}
	}
}
void Piece::rotateZ() //rotate the piece around the Z axis
{
	int x,y,z;
	int temp[3][3][3];
	loadTemp(&temp[0][0][0]);
	setDimensionsToZero();
	for (x=0;x<3;x++)
	{
		for(y=0; y<3; y++)
		{
			for(z=0; z<3 ; z++)
			{
				int t = 1;
				if(y==0)
				{
					t = 2;
				}
				else if(y==2)
				{
					t = 0;
				}
					
				dimension[t][x][z] = temp[x][y][z];
			}
		}
	}
	while(checkNearZ() == false)
	{
		moveCloserZ();
	}
	while(checkNearX() == false)
	{
		moveCloserX();
	}
	while(checkNearY() == false)
	{
		moveCloserY();
	}
}
void Piece::rotateY() //rotate the piece around the Z axis
{
	int x,y,z;
	int temp[3][3][3];
	loadTemp(&temp[0][0][0]);
	setDimensionsToZero();
	for (x=0;x<3;x++)
	{
		for(y=0; y<3; y++)
		{
			for(z=0; z<3 ; z++)
			{
				if (temp[x][y][z] == 1)
				{
					int t = 1;
					if(z==0)
					{
						t = 2;
					}
					else if(z==2)
					{
						t = 0;
					}
						
					dimension[t][y][x] = 1;
				}
			}
		}
	}
	while(checkNearZ() == false)
	{
		moveCloserZ();
	}
	while(checkNearX() == false)
	{
		moveCloserX();
	}
	while(checkNearY() == false)
	{
		moveCloserY();
	}
}
void Piece::rotateX() //rotate the piece around the Z axis
{
	int x,y,z;
	bool occupied = false;
	int temp[3][3][3];
	loadTemp(&temp[0][0][0]);
	setDimensionsToZero();
	for (x=0;x<3;x++)
	{
		for(y=0; y<3; y++)
		{
            for(z=0; z<3 ; z++)
			{
				if (temp[x][y][z] == 1)
				{
					int t = 1;
					if(y==0)
					{
						t = 2;
					}
					else if(y==2)
					{
						t = 0;
					}
						
					dimension[x][z][t] = 1;
				}
			}
		}
	}
	while(checkNearZ() == false)
	{
		moveCloserZ();
		_rotCorrectionZ += 1;
	}
	while(checkNearX() == false)
	{
		moveCloserX();
		_rotCorrectionX += 1;
	}
	while(checkNearY() == false)
	{
		moveCloserY();
		_rotCorrectionY += 1;
	}
}

void Piece::moveCloserZ()
{
	
	for(int z=1; z<3; z++)
	{
		for(int x=0; x<3; x++)
		{
			for(int y=0; y<3; y++)
			{
				dimension[x][y][z-1] = dimension[x][y][z];
			}
		}
	}
	for(int x=0; x<3; x++)
	{
		for(int y=0; y<3; y++)
		{
			dimension[x][y][2] = 0;
		}
	}
	
}
void Piece::moveCloserX()
{
	
	for(int x=1; x<3; x++)
	{
		for(int y=0; y<3; y++)
		{
			for(int z=0; z<3; z++)
			{
				dimension[x-1][y][z] = dimension[x][y][z];
			}
		}
	}
	for(int z=0; z<3; z++)
	{
		for(int y=0; y<3; y++)
		{
			dimension[2][y][z] = 0;
		}
	}
	
}
void Piece::moveCloserY()
{
	
	for(int y=1; y<3; y++)
	{
		for(int x=0; x<3; x++)
		{
			for(int z=0; z<3; z++)
			{
				dimension[x][y-1][z] = dimension[x][y][z];
			}
		}
	}
	for(int x=0; x<3; x++)
	{
		for(int z=0; z<3; z++)
		{
			dimension[x][2][z] = 0;
		}
	}
}
bool Piece::checkNearZ()
{
	for(int x=0; x<3; x++)
	{
		for(int y=0; y<3; y++)
		{
			if(dimension[x][y][0] == 1)
			{
				return true;
			}
		}
	}
	return false;
}
bool Piece::checkNearX()
{
	for(int z=0; z<3; z++)
	{
		for(int y=0; y<3; y++)
		{
			if(dimension[0][y][z] == 1)
			{
				return true;
			}
		}
	}
	return false;
}
bool Piece::checkNearY()
{
	for(int x=0; x<3; x++)
	{
		for(int z=0; z<3; z++)
		{
			if(dimension[x][0][z] == 1)
			{
				return true;
			}
		}
	}
	return false;
}
	


void Piece::loadTemp(int * temp)
{
	int x,y,z;
	for(x=0;x<3;x++)
	{
		for(y=0;y<3;y++)
		{
			for(z=0;z<3;z++)
			{
				*(temp+(x*9+y*3+z)) = dimension[x][y][z];
			}
		}
	}
	
}
int Piece::getId()
{
	return _pieceId;
}
void Piece::setPlaced(bool newValue)
{
	placed = newValue;
}
void Piece::setNumberOfPositions()
{
	cout << "Length:" << getLength() << "Height:" << getHeight() << "Depth:" << getDepth();
	noOfPositions = ((4-getLength()+1)*(4-getHeight()+1)*(4-getDepth()+1));
	cout << "Positions :" << noOfPositions<< "\n";
}
void Piece::definePiece(int pieceNo)
{
	_pieceId = pieceNo;
	setPlaced(false);
	switch(pieceNo)
	{
	case 0:
		setColour('b');
		setDimension(0,0,0,1);
		setDimension(1,0,0,1);
		setDimension(1,0,1,1);
		setDimension(2,0,0,1);
		setDimension(1,1,1,1);
		
		break;
	case 1:
		setColour('b');
		setDimension(0,0,0,1);
		setDimension(1,0,0,1);
		setDimension(1,0,1,1);
		setDimension(1,1,1,1);
		setDimension(2,1,1,1);
		break;
	case 2:
		setColour('b');
		setDimension(0,0,0,1);
		setDimension(1,0,0,1);
		setDimension(1,0,1,1);
		setDimension(2,0,0,1);
		setDimension(0,1,0,1);
		break;
	case 3:
		setColour('b');
		setDimension(0,0,0,1);
		setDimension(0,0,1,1);
		setDimension(1,0,1,1);
		setDimension(1,0,2,1);
		setDimension(2,0,1,1);
		break;
	case 4:
		setColour('y');
		setDimension(0,0,0,1);
		setDimension(0,0,1,1);
		setDimension(1,0,1,1);
		setDimension(1,0,2,1);
		setDimension(2,0,2,1);
		break;
	case 5:
		setColour('y');
		setDimension(0,0,0,1);
		setDimension(0,0,1,1);
		setDimension(1,0,0,1);
		setDimension(2,0,0,1);
		setDimension(0,1,1,1);
		break;
	case 6:
		setColour('y');
		setDimension(0,0,0,1);
		setDimension(1,0,0,1);
		setDimension(1,0,1,1);
		setDimension(1,1,0,1);
		setDimension(2,0,0,1);
		break;
	case 7:
		setColour('y');
        setDimension(0,0,0,1);
		setDimension(0,0,1,1);
		setDimension(1,0,0,1);
		setDimension(1,1,0,1);
		break;
	case 8:
		setColour('y');
		setDimension(0,0,0,1);
		setDimension(1,0,0,1);
		setDimension(2,0,0,1);
		setDimension(2,0,1,1);
		setDimension(0,1,0,1);
		break;
	case 9:
		setColour('r');
		setDimension(0,0,0,1);
		setDimension(0,0,1,1);
		setDimension(1,0,0,1);
		setDimension(2,0,0,1);
		setDimension(0,1,0,1);
		break;
	case 10:
		setColour('r');
		setDimension(1,0,0,1);
		setDimension(1,1,1,1);
		setDimension(2,0,0,1);
		setDimension(0,1,0,1);
		setDimension(1,1,0,1);
		break;
	case 11:
		setColour('r');
		setDimension(0,0,0,1);
		setDimension(1,0,0,1);
		setDimension(1,0,1,1);
		setDimension(2,0,1,1);
		setDimension(2,1,1,1);
		break;
	case 12:
		setColour('r');
		setDimension(0,0,1,1);
		setDimension(1,0,0,1);
		setDimension(1,0,1,1);
		setDimension(1,0,2,1);
		setDimension(2,0,1,1);
		break;
	}
	loadOrientations();
	setNumberOfPositions();
}
