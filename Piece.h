#ifndef Piece_H
#define Piece_H
#include<iostream>
#include<Vector>
#include<String>
#include"GraPiece.h"
using namespace std;

typedef std::vector<string> Zvector;
typedef std::vector<Zvector> Xvector;
typedef std::vector<Zvector> positionVector;
typedef std::vector<positionVector> OrientationVector;
//typedef std::vector<Zvector> OrientationVector;

class Piece:public GraPiece
{
	
private:
	int dimension[3][3][3];
	char colour;
	bool placed;
	vector<OrientationVector>orientation;
	int noOfOrientations;
	int noOfPositions;
	
	void loadOrientations();
	void loadTemp(int * temp);
	void moveCloserZ();
	void moveCloserX();
	void moveCloserY();
	void setDimensionsToZero();
	bool checkNearZ();
	bool checkNearX();
	bool checkNearY();
	void setNumberOfPositions();
	
public:
	Piece();
	Piece(int pieceId);
	Piece(char col);
	Piece(int * dim, char col);
		int StringToInt(string num); //Piece class???
	void rotateX();
	void rotateY();
	void rotateZ();
	
	int getLength();
	int getHeight();
	int getDepth();
	int getId();
	int getNoOfOrientations();
	int getNoOfPositions(){return noOfPositions;};
	string getOrientationPos(int ori, int pos, int x, int z){return orientation[ori][pos][x][z];};
	int * getDimensions();
	char getColour();
	bool getPlaced();
	int getDimension(int x, int y, int z);
	string getOrientationElement(int i, int x, int z);
	void setDimensions(int * dim[]);
	void setDimension(int x, int y, int z, int value);
	void setColour(char col);
	void setPlaced(bool placed);
	
	void displayDimensions();
	void definePiece(int pieceNo);

	char convertToChar(int value);
};

#endif