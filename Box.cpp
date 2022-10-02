#include<iostream>
//#include<vector>
#include"Piece.h"
#include"Box.h"

int charToInt(char value);
Box::Box()
{

	int x,y,z;
	for(x=0;x<4;x++)
	{
		for(y=0; y<7; y++)
		{
			for(z=0; z<4; z++)
			{
				currentState[x][y][z] = -1;
			}
		}
	}
	for(x=0; x<4; x++)
	{
		for(z=0; z<4; z++)
		{
			piecePos[x][z] = 0;
		}
	}
}

int Box::getCurrentStateElement(int x, int y, int z)
{
	return currentState[x][y][z];
}
int * Box::getPtrElement(int x, int y, int z)
{
	return &currentState[x][y][z];
}

bool Box::dropPiece()	//Drops the current piece from its current position above the box
{
	using namespace std;
	int x,y,z;
	int level = 0;
	bool flat = true;
	bool fit = true;
	for(y=0; y<4; y++)
	{
		if (fit == true && y != 0)
		{
			break;
		}
		level = y;
		fit = true;
		for(x = getPieceLeftX(); x< getPieceLeftX()+ currentPiece->getLength(); x++)
		{
			if(fit==false)
			{
				break;
			}
			for(z = getPieceNearZ(); z< getPieceNearZ() + currentPiece->getDepth(); z++)
			{
				if(fit==false)
				{
					break;
				}
				if(piecePos[x][z] != -1)
				{
					int l = y-1;
					int m = piecePos[x][z] - 1;
					do
					{
						l++;
						
						if(l > y) 
						{
							flat = false;
						}
						if(piecePos[x][z] + l >= 4)
						{
							fit = false;
							break;
						}
						if(currentState[x][piecePos[x][z]+l][z] != -1)
						{
							fit = false;
							break;
						}
						if(m==-1)
						{
							m=0;
						}
						m++;
					}while(currentPiece->getDimension(x-getPieceLeftX(),piecePos[x][z]+m,z-getPieceNearZ()) != 0 && piecePos[x][z]+m <= 3);
					

				}
			}
		}
	}
	if (fit == true)
	{
		currentPiece->setPlaced(true);
		for(x = getPieceLeftX(); x< getPieceLeftX()+ currentPiece->getLength(); x++)
		{
			for(z = getPieceNearZ(); z< getPieceNearZ() + currentPiece->getDepth(); z++)
			{
				if(piecePos[x][z] != -1)
				{
					
					currentState[x][piecePos[x][z]+level][z] = currentPiece->getId();
					if(flat == false)
					{
						if(currentPiece->getDimension(x-getPieceLeftX(),piecePos[x][z]+ 1,z) != 0 && piecePos[x][z]+1 < 3)
						{
							currentState[x][piecePos[x][z]+level+1][z] = currentPiece->getId();
						}
						if(currentPiece->getDimension(x-getPieceLeftX(),piecePos[x][z]+ 2,z) != 0&& piecePos[x][z]+2 < 3)
						{
							currentState[x][piecePos[x][z]+level+2][z] = currentPiece->getId();
						}
						
					}
				}
			}
		}
		for (int x=0; x<4; x++)
		{
			for (int y=0; y<4; y++)
			{
				for (int z=0; z<4; z++)
				{
					cout << x << y << z << " " << getCurrentStateElement(x,y,z) << "\n";
				}
			}
		}
		currentPiece->setPosition(new D3DXVECTOR3(getPieceLeftX()- currentPiece->getRotCorrectionX(), level - currentPiece->getRotCorrectionY(), getPieceNearZ()- currentPiece->getRotCorrectionZ()));
		currentPiece = NULL;
		return true;
	}
	else
	{	
		return false;
	}
	
}	



void Box::rotatePieceX() //Rotate the piece around the X axis
{
	cout << currentPiece->getRotationY() << "\n";
	if(currentPiece->getRotationY() == 0)
	{
		int correctionZ = 0;

		//Rotate the logical representation of the piece
		currentPiece->rotateX();
		if(getPieceNearZ() + currentPiece->getDepth() > 4)
		{
			correctionZ = getPieceNearZ() + currentPiece->getDepth() - 4;
		}
		//generate the piecePos array
		setPiecePos(currentPiece, getPieceLeftX(), getPieceNearZ()+ correctionZ);
		
		//Rotate the graphical version of the piece
		currentPiece->setRotationX(currentPiece->getRotationX() - (D3DX_PI/2));

		if(currentPiece->getRotationX() < -6)
		{
			currentPiece->setRotationX(0);
		}
		cout << "RotationX: " << currentPiece->getRotationX() << "\n";
		currentPiece->setPosition(&D3DXVECTOR3(this->getPieceLeftX(), 5,  this->getPieceNearZ()));

		//These IF statements compensate for the difference between the graphical and logical rotate methods
		if((currentPiece->getRotationX() == -D3DX_PI || currentPiece->getRotationX() == -D3DX_PI/2))
		{
			currentPiece->setRotCorrectionZ(3-currentPiece->getDepth());
		}
		if((currentPiece->getRotationX() == -D3DX_PI || currentPiece->getRotationX() == -3*(D3DX_PI/2)))
		{
			currentPiece->setRotCorrectionY(3-currentPiece->getHeight());
		}
		if(currentPiece->getRotationX() == 3*(-D3DX_PI/2))
		{
			currentPiece->setRotCorrectionZ(0);

		}
		if(currentPiece->getRotationX() == 0)
		{
			currentPiece->setRotCorrectionZ(0);
		}
		//set the position of the graphical version of the piece
		currentPiece->setPosition(&D3DXVECTOR3(getPieceLeftX() - currentPiece->getRotCorrectionX(), 5- currentPiece->getRotCorrectionY(), getPieceNearZ() - currentPiece->getRotCorrectionZ()));
		

		drawPiecePosPlan();
	}
	else if(currentPiece->getRotationY() == -D3DX_PI/2)
	{
		rotatePieceZ();
	}
	
	

}
void Box::rotatePieceY()
{
	int correctionX, correctionZ = 0;
	currentPiece->setRotCorrectionX(0);
	currentPiece->setRotCorrectionY(0);
	currentPiece->setRotCorrectionZ(0);
	//rotate the logical version of the piece
	currentPiece->rotateY();
	if(getPieceLeftX() + currentPiece->getLength() > 4)
	{
		correctionX = getPieceLeftX() + currentPiece->getLength() - 4;
	}
	if(getPieceNearZ() + currentPiece->getDepth() > 4)
	{
		correctionZ = getPieceNearZ() + currentPiece->getDepth() - 4;
	}
	//generate the piecePos array
	setPiecePos(currentPiece, (getPieceLeftX() - correctionX), (getPieceNearZ() - correctionZ));
	currentPiece->setRotationY(currentPiece->getRotationY() - (D3DX_PI/2));
	if(currentPiece->getRotationY() < -6)
	{
		currentPiece->setRotationY(0);
	}
	if((currentPiece->getRotationY() == -D3DX_PI || currentPiece->getRotationY() == -D3DX_PI/2))
	{
		currentPiece->setRotCorrectionX(3-currentPiece->getLength());
	}
	if((currentPiece->getRotationY() == -D3DX_PI || currentPiece->getRotationY() == -3*(D3DX_PI/2)))
	{
		currentPiece->setRotCorrectionZ(3-currentPiece->getDepth());
	}
	if(currentPiece->getRotationY() == 3*(-D3DX_PI/2))
	{
		currentPiece->setRotCorrectionX(0);
	}
	if(currentPiece->getRotationY() == 0)
	{
		currentPiece->setRotCorrectionX(0);
		currentPiece->setRotCorrectionZ(0);
	}
	cout << "X:" << getPieceLeftX() - currentPiece->getRotCorrectionX() << "\n Y:" << 5 - currentPiece->getRotCorrectionY() << "\n Z:" << getPieceNearZ() - currentPiece->getRotCorrectionZ();
	currentPiece->setPosition(new D3DXVECTOR3(getPieceLeftX() - currentPiece->getRotCorrectionX(), 5 - currentPiece->getRotCorrectionY(), getPieceNearZ()- currentPiece->getRotCorrectionZ()));
	drawPiecePosPlan();
}
void Box::rotatePieceZ()
{
	currentPiece->setRotCorrectionX(0);
	currentPiece->setRotCorrectionY(0);
	currentPiece->setRotCorrectionZ(0);
	int correctionX = 0;
	currentPiece->rotateZ();
	if(getPieceLeftX() + currentPiece->getLength() > 4)
	{
		correctionX = getPieceLeftX() + currentPiece->getLength() - 4;
	}
	setPiecePos(currentPiece,getPieceLeftX() - correctionX, getPieceNearZ());
	currentPiece->setRotationZ(currentPiece->getRotationZ() + (D3DX_PI/2));
	if(currentPiece->getRotationZ() > 6)
	{
		currentPiece->setRotationZ(0);
	}
	cout << currentPiece->getRotCorrectionX() << " " << currentPiece->getRotCorrectionY() << " " << currentPiece->getRotCorrectionZ() << "\n";
	currentPiece->setPosition(new D3DXVECTOR3(currentPiece->getPosition().x - currentPiece->getRotCorrectionX(), currentPiece->getPosition().y - currentPiece->getRotCorrectionY(), currentPiece->getPosition().z)- currentPiece->getRotCorrectionZ());
	drawPiecePosPlan();
}






 
void Box::setPiece(Piece * ptrPiece)
{
	currentPiece = ptrPiece;
	setPiecePos(ptrPiece,0,0);
}
bool Box::movePieceMoreX()
{
	if(getPieceLeftX() + currentPiece->getLength() > 3)
	{
		return false;
	}
	setPiecePos(currentPiece, getPieceLeftX()+1, getPieceNearZ());
	drawPiecePosPlan();
	currentPiece->setPosition(new D3DXVECTOR3(getPieceLeftX()-currentPiece->getRotationX(), 5-currentPiece->getRotCorrectionY(), getPieceNearZ()-currentPiece->getRotCorrectionZ()));
	return true;
}
bool Box::movePieceLessX()
{
	if(getPieceLeftX() <=0)
	{
		return false;
	}
	setPiecePos(currentPiece, getPieceLeftX()-1, getPieceNearZ());
	drawPiecePosPlan();
	currentPiece->setPosition(new D3DXVECTOR3(getPieceLeftX()-currentPiece->getRotationX(), 5-currentPiece->getRotCorrectionY(), getPieceNearZ()-currentPiece->getRotCorrectionZ()));
	return true;
}
bool Box::movePieceLessZ()
{
	if(getPieceNearZ() <= 0)
	{
		return false;
	}
	setPiecePos(currentPiece, getPieceLeftX(), getPieceNearZ()-1);
	drawPiecePosPlan();
	currentPiece->setPosition(new D3DXVECTOR3(getPieceLeftX()-currentPiece->getRotationX(), 5-currentPiece->getRotCorrectionY(), getPieceNearZ()-currentPiece->getRotCorrectionZ()));
	return true;
}
bool Box::movePieceMoreZ()
{
	if(getPieceNearZ() + currentPiece->getDepth() > 3)
	{
		return false;
	}
	setPiecePos(currentPiece, getPieceLeftX(), getPieceNearZ()+1);
	drawPiecePosPlan();
	currentPiece->setPosition(new D3DXVECTOR3(getPieceLeftX()-currentPiece->getRotationX(), 5-currentPiece->getRotCorrectionY(), getPieceNearZ()-currentPiece->getRotCorrectionZ()));
	return true;

}
void Box::drawPiecePosPlan()
{
	using namespace std;
	int x,z;
	for(z=3; z>=0; z--)
	{
		cout << "\n";
		for(x=0 ; x<4; x++)
        {
			if (piecePos[x][z] == -1)
			{
				cout << piecePos[x][z];
			}
			else
			{
				cout << " " << piecePos[x][z];
			}
		}
	}
	cout << "\n";
}
int Box::getPieceLeftX()
{
	int x,z;
	for(x=0; x<4; x++)
	{
		for(z=0; z<4; z++)
		{
			if(piecePos[x][z] != -1)
			{
				return x;
			}
		}
	}
}
int Box::getPieceNearZ()
{
	int x,z;
	for(z=0; z<4; z++)
	{
		for(x=0; x<4; x++)
		{
			if(piecePos[x][z] != -1)
			{
				return z;
			}
		}
	}
}
void Box::setPiecePos(Piece * ptrPiece, int leftX, int backZ)
{
	
	for(int x=0; x<4; x++)
	{
		for(int z=0; z<4; z++)
		{
			piecePos[x][z] = -1;
		}
	}

	for(int x=0; x<3; x++)
	{
		for(int y=0; y<3; y++)
		{
			for(int z=0; z<3; z++)
			{
				if(ptrPiece->getDimension(x,y,z) == 1)
				{
					if(y!=0)
					{
						if(ptrPiece->getDimension(x,y-1,z) != 1)
						{
							piecePos[x+leftX][z+backZ] = y;
						}
					}
					else
					{
                        piecePos[x+leftX][z+backZ] = 0;
					}
				}
			}
		}
	}
}
Piece * Box::getPiece()
{
	return currentPiece;
}

void Box::placePiece(Piece * piece, int ori, int pos)
{
	int nearZ, leftX = 0;
	int upY = 4;
	bool firstPart = false;
	for(int x=0; x<4; x++)
	{
		for(int z=0; z<4; z++)
		{
			if(piece->getOrientationPos(ori, pos, x, z) != "-1")
			{
				if(firstPart == false)
				{
					leftX = x;
					nearZ = z;
					firstPart = true;
				}
				for(int i=0; i<piece->getOrientationPos(ori, pos, x, z).length(); i++)
				{
					if (charToInt(piece->getOrientationPos(ori, pos, x, z)[i]) < upY)
					{
						upY = charToInt(piece->getOrientationPos(ori, pos, x, z)[i]);
					}
					currentState[x][charToInt(piece->getOrientationPos(ori, pos, x, z)[i])][z] = piece->getId();
				}
			}
		}
	}
	piece->setPosition(new D3DXVECTOR3(leftX, nearZ, upY ));
	//This is all the pieces modeled so far - this will be removed when I model the rest of the pieces
	if (piece->getPieceId() < 6)
	{
		for (int i=0; i<ori; i++)
		{
			piece->yaw(-(D3DX_PI/2));
			if (i % 4 == 3 && i != 0 && i < 19)
			{
				piece->pitch(-D3DX_PI/2);
			}
			if(i == 15)
			{
				piece->roll(D3DX_PI/2);
			}
			if(i == 19)
			{
				piece->roll(D3DX_PI/2);
				piece->roll(D3DX_PI/2);
			}
		}
		piece->setVisible(true);
	}
	piece->setPlaced(true);
}

void Box::removePiece(Piece * piece)
{

	for(int x=0; x<4; x++)
	{
		for(int y=0; y<4; y++)
		{
			for(int z=0; z<4; z++)
			{
				if(currentState[x][y][z] == piece->getId())
				{
					currentState[x][y][z] = -1;
				}
			}
		}
	}
	piece->setPlaced(false);
	if (piece->getPieceId() < 6)
	{
		piece->setVisible(false);
		piece->resetPiece();
	}
}

	