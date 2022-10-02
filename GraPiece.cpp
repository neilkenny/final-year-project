#include "GraPiece.h"
#include "Direct3DBase.h"
#include<iostream>
#include <d3dx9.h>
using namespace std;
GraPiece::GraPiece()
{


}
GraPiece::GraPiece(int id)
{
	_elapsedTime=0;
	_pieceId = id;
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

void GraPiece::setElapsedTime(float time)
{
	_elapsedTime = time;
}

void GraPiece::resetPiece()
{
	_pos.x = 0;
	_pos.y = 5;
	_pos.z = 0;
	_rX = 0;
	_rY = 0;
	_rZ = 0;
	_rotCorrectionX = 0;
	_rotCorrectionY = 0;
	_rotCorrectionZ = 0;
	_visible = false;
}
bool GraPiece::getVisible()
{
	return _visible;
}

int GraPiece::getPieceId()
{
	return _pieceId;
}

float GraPiece::getElapsedTime()
{
	return _elapsedTime;
}
int GraPiece::getNoOfTriangles()
{
	return _noOfTriangles;
}
void GraPiece::setVisible(bool value)
{
	_visible = value;
}

void GraPiece::setRotationX(float value)
{
	_rX = value;
	if(_rX > 2*D3DX_PI)
	{
		_rX = 0;
	}
}

void GraPiece::setRotationY(float value)
{
	_rY = value;
	if(_rY > 2*D3DX_PI)
	{
		_rY = 0;
	}
}

void GraPiece::setRotationZ(float value)
{
	_rZ = value;
	if(_rZ > 2*D3DX_PI)
	{
		_rZ = 0;								///Should these be less than???
	}
}

float GraPiece::getRotationX()
{
	return _rX;
}

float GraPiece::getRotationY()
{
	return _rY;
}

float GraPiece::getRotationZ()
{
	return _rZ;
}

void GraPiece::update(float timeDelta) 
{
	
	D3DXVECTOR3 look = _look * getSpeed();
	_pos = _pos + (look * timeDelta);

}

bool GraPiece::setup(IDirect3DDevice9 * device)
{
	_device = device;
	TexelVertex * vertex;
	cout << "PIECEID = " << _pieceId << "\n";
	if(_pieceId == 0)
	{
		D3DXCreateTextureFromFile(device, "bluepiece.bmp", &_pieceTexture);
		device->CreateVertexBuffer(
			78 * sizeof(TexelVertex), // size in bytes
			D3DUSAGE_WRITEONLY, // flags
			TexelVertex::FVF,        // vertex format
			D3DPOOL_MANAGED,    // managed memory pool
			&_vertices,          // return create vertex buffer
			0);     
		_vertices->Lock(0, 0, (void**)&vertex, 0);
		_noOfTriangles = 26;
		// The front of 000, 100, 200
		vertex[0] = TexelVertex(1.5,-0.5,-1.5, 0,1);
		vertex[1] = TexelVertex(1.5,-1.5,-1.5, 0,0);
		vertex[2] = TexelVertex(-1.5,-1.5,-1.5, 1,0);
		
		vertex[3] = TexelVertex(-1.5,-1.5,-1.5, 0,1);
		vertex[4] = TexelVertex(-1.5,-0.5,-1.5, 0,0);
		vertex[5] = TexelVertex(1.5,-0.5,-1.5, 1,0);

		//The right side of 200
		vertex[6] = TexelVertex(1.5,-0.5,-0.5, 0,1);
		vertex[7] = TexelVertex(1.5,-1.5,-0.5, 0,0);
		vertex[8] = TexelVertex(1.5,-1.5,-1.5, 1,0);

		vertex[9] = TexelVertex(1.5,-1.5,-1.5, 0,1);
		vertex[10] = TexelVertex(1.5,-0.5,-1.5, 0,0 );
		vertex[11] = TexelVertex(1.5,-0.5,-0.5, 1,0);
		//Back of 200
		vertex[12] = TexelVertex(1.5,-1.5,-0.5, 0,1);
		vertex[13] = TexelVertex(1.5,-0.5,-0.5, 0,0);
		vertex[14] = TexelVertex(0.5,-0.5,-0.5, 1,0);
		
		vertex[15] = TexelVertex(0.5,-0.5,-0.5, 0,1);
		vertex[16] = TexelVertex(0.5,-1.5,-0.5, 0,0);
		vertex[17] = TexelVertex(1.5,-1.5,-0.5, 1,0);
		
		//right side of 101 and 111
		vertex[18] = TexelVertex(0.5,0.5,0.5, 1,0);
		vertex[19] = TexelVertex(0.5,-1.5,0.5, 1,1);
		vertex[20] = TexelVertex(0.5,0.5,-0.5, 0,0);
		
		vertex[21] = TexelVertex(0.5,-1.5,0.5, 1,1);
		vertex[22] = TexelVertex(0.5,-1.5,-0.5, 0,1);
		vertex[23] = TexelVertex(0.5,0.5,-0.5, 0,0);
		//top of 000, 100 and 200
		vertex[24] = TexelVertex(1.5,-0.5,-0.5, 0,1);    //(3,1,1)   //1.5 = 3     -1.5 =0   -0.5 = 1      0.5=2       
		vertex[25] = TexelVertex(1.5,-0.5,-1.5, 0,0);   //(3,1,0)
		vertex[26] = TexelVertex(-1.5,-0.5,-1.5, 1,0);  //(0,1,0)
		
		vertex[27] = TexelVertex(-1.5,-0.5,-1.5,0,1);	//(0,1,0)
		vertex[28] = TexelVertex(-1.5,-0.5,-0.5,0,0);   //(0,1,1)
		vertex[29] = TexelVertex(1.5,-0.5,-0.5,1,0);	//(3,1,1)

		//bottom of 000,100 and 200
		
		vertex[30] = TexelVertex(1.5,-1.5,-1.5, 1,0);
		vertex[31] = TexelVertex(1.5,-1.5,-0.5,1,1);
		vertex[32] = TexelVertex(-1.5,-1.5,-1.5, 0,0);
		
		vertex[33] = TexelVertex(-1.5,-1.5,-0.5,0,1);
		vertex[34] = TexelVertex(-1.5,-1.5,-1.5,0,0);
		vertex[35] = TexelVertex(1.5,-1.5,-0.5,1,1);

		//left of 000
		vertex[36] = TexelVertex(-1.5,-1.5,-1.5, 1,1);	//(0,0,0)
		vertex[37] = TexelVertex(-1.5,-0.5,-0.5, 0,0);	//(0,1,1)
		vertex[38] = TexelVertex(-1.5,-0.5,-1.5, 1,0);	//(0,1,0)

		vertex[40] = TexelVertex(-1.5,-0.5,-0.5,  0,0);	//(0,1,1)
		vertex[39] = TexelVertex(-1.5,-1.5,-0.5,  0,1);	//(0,0,1)
		vertex[41] = TexelVertex(-1.5,-1.5,-1.5,  1,1);	//(0,0,0)
		
		//left of 101,111
		vertex[42] = TexelVertex(-0.5,-1.5,0.5, 0,1);	//(1,0,2)
		vertex[43] = TexelVertex(-0.5,0.5,0.5,  0,0);	//(1,2,2)
		vertex[44] = TexelVertex(-0.5,0.5,-0.5, 1,0);	//(1,2,1)
		
		vertex[45] = TexelVertex(-0.5,-1.5,-0.5, 1,1);	//(1,0,1)
		vertex[46] = TexelVertex(-0.5,-1.5,0.5,  0,1);	//(1,0,2)
		vertex[47] = TexelVertex(-0.5,0.5,-0.5,  1,0);	//(1,2,1)

		//front of 111
		vertex[48] = TexelVertex(-0.5,-0.5,-0.5, 0,1);
		vertex[49] = TexelVertex(-0.5,0.5,-0.5, 0,0);
		vertex[50] = TexelVertex(0.5,0.5,-0.5, 1,0);
		
		vertex[51] = TexelVertex(0.5,0.5,-0.5, 0,1);
		vertex[52] = TexelVertex(0.5,-0.5,-0.5, 0,0);
		vertex[53] = TexelVertex(-0.5,-0.5,-0.5, 1,0);

		//Back of 000
		vertex[54] = TexelVertex(-0.5,-1.5,-0.5, 0,1);
		vertex[55] = TexelVertex(-0.5,-0.5,-0.5, 0,0);
		vertex[56] = TexelVertex(-1.5,-0.5,-0.5, 1,0);
		
		vertex[57] = TexelVertex(-1.5,-0.5,-0.5, 0,1);
		vertex[58] = TexelVertex(-1.5,-1.5,-0.5, 0,0);
		vertex[59] = TexelVertex(-0.5,-1.5,-0.5, 1,0);
		//back of 101, 111
		vertex[60] = TexelVertex(0.5,0.5,0.5, 1,0);		//(2,2,2)
		vertex[61] = TexelVertex(-0.5,0.5,0.5, 0,0);	//(1,2,2)
		vertex[62] = TexelVertex(-0.5,-1.5,0.5, 0,1);	//(1,0,2)
		
		vertex[63] = TexelVertex(-0.5,-1.5,0.5,0,1);	//(1,0,2)
		vertex[64] = TexelVertex(0.5,-1.5,0.5,1,1);		//(2,0,2)
		vertex[65] = TexelVertex(0.5,0.5,0.5,1,0);		//(2,2,2)
		//top of 111
		vertex[66] = TexelVertex(-0.5,0.5,0.5,0,1);
		vertex[67] = TexelVertex(0.5,0.5,0.5, 0,0);
		vertex[68] = TexelVertex(0.5,0.5,-0.5, 1,0);
		
		vertex[69] = TexelVertex(0.5,0.5,-0.5,0,1);
		vertex[70] = TexelVertex(-0.5,0.5,-0.5,0,0);
		vertex[71] = TexelVertex(-0.5,0.5,0.5,1,0);
		//bottom of 101
 		vertex[73] = TexelVertex(-0.5,-1.5,0.5, 0,1);
		vertex[72] = TexelVertex(0.5,-1.5,0.5, 0,0);
		vertex[74] = TexelVertex(0.5,-1.5,-0.5, 1,0);
		
		vertex[76] = TexelVertex(0.5,-1.5,-0.5, 0,1);
		vertex[75] = TexelVertex(-0.5,-1.5,-0.5, 0,0);
		vertex[77] = TexelVertex(-0.5,-1.5,0.5, 1,0);
		_vertices->Unlock();
	}
	else if(_pieceId == 1)
	{
		D3DXCreateTextureFromFile(device, "bluepiece.bmp", &_pieceTexture);
		device->CreateVertexBuffer(
			84 * sizeof(TexelVertex), // size in bytes
			D3DUSAGE_WRITEONLY, // flags
			TexelVertex::FVF,        // vertex format
			D3DPOOL_MANAGED,    // managed memory pool
			&_vertices,          // return create vertex buffer
			0);     
		_vertices->Lock(0, 0, (void**)&vertex, 0);
	
		_noOfTriangles = 28;
				
		// The front of 000 and 100
		vertex[0] = TexelVertex(-1.5,-1.5,-1.5,0,1);
		vertex[1] = TexelVertex(-1.5,-0.5,-1.5,0,0);
		vertex[2] = TexelVertex(0.5,-0.5,-1.5,1,0);
		
		vertex[3] = TexelVertex(0.5,-0.5,-1.5,1,0);
		vertex[4] = TexelVertex(0.5,-1.5,-1.5,1,1);
		vertex[5] = TexelVertex(-1.5,-1.5,-1.5,0,1);

		// The side of 000 
		vertex[6] = TexelVertex(-1.5,-1.5,-1.5, 1,1);
		vertex[7] = TexelVertex(-1.5,-1.5,-0.5, 1,0);
		vertex[8] = TexelVertex(-1.5,-0.5,-0.5, 0,0);

		vertex[9] = TexelVertex(-1.5,-0.5,-0.5, 0,0);
		vertex[10] = TexelVertex(-1.5,-0.5,-1.5, 0,1);
		vertex[11] = TexelVertex(-1.5,-1.5,-1.5, 1,1);
		
		// The top of 000, 100 
		vertex[12] = TexelVertex(-1.5,-0.5,-1.5, 0,1);
		vertex[13] = TexelVertex(-1.5,-0.5,-0.5, 0,0);
		vertex[14] = TexelVertex(0.5,-0.5,-0.5, 1,0);
		
		vertex[15] = TexelVertex(0.5,-0.5,-0.5, 1,0);
		vertex[16] = TexelVertex(0.5,-0.5,-1.5, 1,1);
		vertex[17] = TexelVertex(-1.5,-0.5,-1.5, 0,1);
		
		// The left side of 101, 111
		vertex[18] = TexelVertex(-0.5,-1.5,-0.5, 0,1);
		vertex[19] = TexelVertex(-0.5,-1.5,0.5, 0,0);
		vertex[20] = TexelVertex(-0.5,0.5,0.5, 1,0);
		
		vertex[21] = TexelVertex(-0.5,0.5,0.5, 1,0);
		vertex[22] = TexelVertex(-0.5,0.5,-0.5, 1,1);
		vertex[23] = TexelVertex(-0.5,-1.5,-0.5, 0,1);

		// The front of 111, 211
		vertex[24] = TexelVertex(-0.5,0.5,-0.5, 0,0);
		vertex[25] = TexelVertex(1.5,0.5,-0.5, 1,0);
		vertex[26] = TexelVertex(1.5,-0.5,-0.5, 1,1);
		
		vertex[27] = TexelVertex(1.5,-0.5,-0.5, 1,1);
		vertex[28] = TexelVertex(-0.5,-0.5,-0.5, 0,1);
		vertex[29] = TexelVertex(-0.5,0.5,-0.5, 0,0);
		
		//The top of 111, 211
		vertex[30] = TexelVertex(-0.5,0.5,-0.5, 0,1);
		vertex[31] = TexelVertex(-0.5,0.5,0.5, 0,0);
		vertex[32] = TexelVertex(1.5,0.5,0.5, 1,0);
		
		vertex[33] = TexelVertex(1.5,0.5,0.5, 1,0);
		vertex[34] = TexelVertex(1.5,0.5,-0.5, 1,1);
		vertex[35] = TexelVertex(-0.5,0.5,-0.5, 0,1);
		
		//The side of 100,101
		vertex[36] = TexelVertex(0.5,-1.5,0.5, 1,1);
		vertex[37] = TexelVertex(0.5,-1.5,-1.5, 0,1);
		vertex[38] = TexelVertex(0.5,-0.5,0.5, 1,0);
		
		vertex[39] = TexelVertex(0.5,-0.5,-1.5, 0,0);
		vertex[40] = TexelVertex(0.5,-0.5,0.5, 1,0);
		vertex[41] = TexelVertex(0.5,-1.5,-1.5, 0,1);

		//The side of 211
		vertex[42] = TexelVertex(1.5,-0.5,0.5, 1,1);
		vertex[43] = TexelVertex(1.5,-0.5,-0.5, 0,1);
		vertex[44] = TexelVertex(1.5,0.5,0.5, 1,0);
		
		vertex[45] = TexelVertex(1.5,0.5,-0.5, 0,0);
		vertex[46] = TexelVertex(1.5,0.5,0.5, 1,0);
		vertex[47] = TexelVertex(1.5,-0.5,-0.5, 0,1);

		//The back of 111, 211
		vertex[48] = TexelVertex(1.5,0.5,0.5, 1,0);
		vertex[49] = TexelVertex(-0.5,0.5,0.5, 0,0);
		vertex[50] = TexelVertex(-0.5,-0.5,0.5, 0,1);

		vertex[51] = TexelVertex(-0.5,-0.5,0.5, 0,1);
		vertex[52] = TexelVertex(1.5,-0.5,0.5, 1,1);
		vertex[53] = TexelVertex(1.5,0.5,0.5, 1,0);

		//The Back Of 101
		vertex[54] = TexelVertex(-0.5,-1.5,0.5, 0,1);
		vertex[55] = TexelVertex(0.5,-1.5,0.5, 1,1);
		vertex[56] = TexelVertex(0.5,-0.5,0.5, 1,0);

		vertex[57] = TexelVertex(0.5,-0.5,0.5, 1,0);
		vertex[58] = TexelVertex(-0.5,-0.5,0.5, 0,0);
		vertex[59] = TexelVertex(-0.5,-1.5,0.5, 0,1);

		//Back of 000
		vertex[60] = TexelVertex(-1.5,-1.5,-0.5, 0,1);
		vertex[61] = TexelVertex(-0.5,-1.5,-0.5, 1,0);
		vertex[62] = TexelVertex(-0.5,-0.5,-0.5, 1,0);

		vertex[63] = TexelVertex(-0.5,-0.5,-0.5, 1,0);
		vertex[64] = TexelVertex(-1.5,-0.5,-0.5, 0,0);
		vertex[65] = TexelVertex(-1.5,-1.5,-0.5, 0,1);
		
		//Bottom of 000, 100
		vertex[67] = TexelVertex(-1.5,-1.5,-1.5, 0,1);
		vertex[66] = TexelVertex(-1.5,-1.5,-0.5, 0,0);
		vertex[68] = TexelVertex(0.5,-1.5,-0.5, 1,0);
		
		vertex[70] = TexelVertex(0.5,-1.5,-0.5, 1,0);
		vertex[69] = TexelVertex(0.5,-1.5,-1.5, 1,1);
		vertex[71] = TexelVertex(-1.5,-1.5,-1.5, 0,1);

		//Bottom of 101

		vertex[72] = TexelVertex(-0.5,-1.5,-0.5, 0,1);
		vertex[73] = TexelVertex(0.5,-1.5,-0.5, 0,0);
		vertex[74] = TexelVertex(0.5,-1.5,0.5, 1,0);
		
		vertex[75] = TexelVertex(0.5,-1.5,0.5, 1,0);
		vertex[76] = TexelVertex(-0.5,-1.5,0.5, 1,1);
		vertex[77] = TexelVertex(-0.5,-1.5,-0.5, 0,1);

		//Bottom of 211
		vertex[78] = TexelVertex(0.5,-0.5,-0.5, 0,1);
		vertex[79] = TexelVertex(1.5,-0.5,-0.5, 0,0);
		vertex[80] = TexelVertex(1.5,-0.5,0.5, 1,0);
		
		vertex[81] = TexelVertex(1.5,-0.5,0.5, 1,0);
		vertex[82] = TexelVertex(0.5,-0.5,0.5, 1,1);
		vertex[83] = TexelVertex(0.5,-0.5,-0.5, 0,1);
		_vertices->Unlock();
	}
	else if(_pieceId == 2)
	{
		D3DXCreateTextureFromFile(device, "bluepiece.bmp", &_pieceTexture);
		device->CreateVertexBuffer(
			90 * sizeof(TexelVertex), // size in bytes
			D3DUSAGE_WRITEONLY, // flags
			TexelVertex::FVF,        // vertex format
			D3DPOOL_MANAGED,    // managed memory pool
			&_vertices,          // return create vertex buffer
			0);     
		_vertices->Lock(0, 0, (void**)&vertex, 0);
		_noOfTriangles = 30;

		// The front of 000, 100, 200
		vertex[0] = TexelVertex(1.5,-0.5,-1.5, 0,1);
		vertex[1] = TexelVertex(1.5,-1.5,-1.5,0,0);
		vertex[2] = TexelVertex(-1.5,-1.5,-1.5, 1,0);
		
		vertex[3] = TexelVertex(-1.5,-1.5,-1.5, 0,1);
		vertex[4] = TexelVertex(-1.5,-0.5,-1.5,0,0);
		vertex[5] = TexelVertex(1.5,-0.5,-1.5, 1,0);

		//The right side of 200
		vertex[6] = TexelVertex(1.5,-0.5,-0.5, 0,1);
		vertex[7] = TexelVertex(1.5,-1.5,-0.5, 0,0);
		vertex[8] = TexelVertex(1.5,-1.5,-1.5, 1,0);

		vertex[9] = TexelVertex(1.5,-1.5,-1.5,0,1);
		vertex[10] = TexelVertex(1.5,-0.5,-1.5,0,0 );
		vertex[11] = TexelVertex(1.5,-0.5,-0.5,1,0);
		//Back of 200
		vertex[12] = TexelVertex(1.5,-1.5,-0.5,0,1);
		vertex[13] = TexelVertex(1.5,-0.5,-0.5, 0,0);
		vertex[14] = TexelVertex(0.5,-0.5,-0.5, 1,0);
		
		vertex[15] = TexelVertex(0.5,-0.5,-0.5,0,1);
		vertex[16] = TexelVertex(0.5,-1.5,-0.5,0,0);
		vertex[17] = TexelVertex(1.5,-1.5,-0.5,1,0);
		
		//right side of 101
		vertex[18] = TexelVertex(0.5,-0.5,-0.5,0,0); //211
		vertex[19] = TexelVertex(0.5,-0.5,0.5,1,0); //212
		vertex[20] = TexelVertex(0.5,-1.5,-0.5, 0,1);//201
		
		vertex[21] = TexelVertex(0.5,-1.5,0.5,1,1); //202
		vertex[22] = TexelVertex(0.5,-1.5,-0.5,0,1); //201
		vertex[23] = TexelVertex(0.5,-0.5,0.5,1,0); //212
		//left of 000 010
		vertex[24] = TexelVertex(-1.5,-1.5,-1.5,0,1); //000
		vertex[25] = TexelVertex(-1.5,-1.5,-0.5, 0,0);//001
		vertex[26] = TexelVertex(-1.5,0.5,-0.5, 1,0);//021
		
		vertex[27] = TexelVertex(-1.5,0.5,-0.5,0,1); //021
		vertex[28] = TexelVertex(-1.5,0.5,-1.5,0,0);//020
		vertex[29] = TexelVertex(-1.5,-1.5,-1.5,1,0); //000

		//bottom of 000,100 and 200
		
		vertex[30] = TexelVertex(1.5,-1.5,-1.5, 1,0);
		vertex[31] = TexelVertex(1.5,-1.5,-0.5,1,1);
		vertex[32] = TexelVertex(-1.5,-1.5,-1.5, 0,0);
		
		vertex[33] = TexelVertex(-1.5,-1.5,-0.5,0,1);
		vertex[34] = TexelVertex(-1.5,-1.5,-1.5,0,0);
		vertex[35] = TexelVertex(1.5,-1.5,-0.5,1,1);

		//top of 010
		vertex[36] = TexelVertex(-1.5,0.5,-1.5, 0,1); //020
		vertex[37] = TexelVertex(-1.5,0.5,-0.5, 0,0);//021
		vertex[38] = TexelVertex(-0.5,0.5,-0.5, 1,0);//121

		vertex[39] = TexelVertex(-0.5,0.5,-0.5,1,0);//121
		vertex[40] = TexelVertex(-0.5,0.5,-1.5,1,1);//120
		vertex[41] = TexelVertex(-1.5,0.5,-1.5,0,1);//020
		//front of 010
		vertex[42] = TexelVertex(-1.5,-0.5,-1.5,0,1);	//010
		vertex[43] = TexelVertex(-1.5,0.5,-1.5, 0,0);	//020
		vertex[44] = TexelVertex(-0.5,0.5,-1.5, 1,0);	//120
		
		vertex[45] = TexelVertex(-0.5,0.5,-1.5,0,1);	//120
		vertex[46] = TexelVertex(-0.5,-0.5,-1.5,0,0);	//110
		vertex[47] = TexelVertex(-1.5,-0.5,-1.5,1,0);	//010

		//top of 100 200
		vertex[48] = TexelVertex(-0.5,-0.5,-1.5,0,1);	//110
		vertex[49] = TexelVertex(-0.5,-0.5,-0.5, 0,0);	//111
		vertex[50] = TexelVertex(1.5,-0.5,-0.5, 1,0);	//311
		
		vertex[51] = TexelVertex(1.5,-0.5,-0.5,0,1);	//311
		vertex[52] = TexelVertex(1.5,-0.5,-1.5,0,0);	//310
		vertex[53] = TexelVertex(-0.5,-0.5,-1.5,1,0);	//110

		//Back of 000 010
		vertex[54] = TexelVertex(-1.5,-1.5,-0.5,0,1);   //001
		vertex[55] = TexelVertex(-0.5,-1.5,-0.5,0,0);	//101
		vertex[56] = TexelVertex(-0.5,0.5,-0.5, 1,0);	//121
		
		vertex[57] = TexelVertex(-0.5,0.5,-0.5,0,1);	//121
		vertex[58] = TexelVertex(-1.5,0.5,-0.5,0,0);	//021
		vertex[59] = TexelVertex(-1.5,-1.5,-0.5,1,0);	//001
		//right of 010
		vertex[60] = TexelVertex(-0.5,-0.5,-0.5, 0,0);	//111
		vertex[61] = TexelVertex(-0.5,-0.5,-1.5,0,1);	//110
		vertex[62] = TexelVertex(-0.5,0.5,-0.5, 1,0);	//121
		
		vertex[63] = TexelVertex(-0.5,0.5,-1.5,0,0);	//120
		vertex[64] = TexelVertex(-0.5,0.5,-0.5,0,1);	//121
		vertex[65] = TexelVertex(-0.5,-0.5,-1.5,1,0);	//110
		//back of 101
		vertex[66] = TexelVertex(-0.5,-1.5,0.5,0,1);	//102
		vertex[67] = TexelVertex(0.5,-1.5,0.5, 0,0);	//202
		vertex[68] = TexelVertex(0.5,-0.5,0.5, 1,0);	//212
		
		vertex[69] = TexelVertex(0.5,-0.5,0.5,0,1);		//212
		vertex[70] = TexelVertex(-0.5,-0.5,0.5,0,0);	//112
		vertex[71] = TexelVertex(-0.5,-1.5,0.5,1,0);	//102
		//bottom of 101
 		vertex[72] = TexelVertex(-0.5,-1.5,-0.5, 0,1);	//101
		vertex[73] = TexelVertex(0.5,-1.5,-0.5, 0,0);	//201
		vertex[74] = TexelVertex(0.5,-1.5,0.5, 1,0);	//202	
		
		vertex[75] = TexelVertex(0.5,-1.5,0.5, 0,1);	//202
		vertex[76] = TexelVertex(-0.5,-1.5,0.5, 0,0);	//102
		vertex[77] = TexelVertex(-0.5,-1.5,-0.5, 1,0);	//101

		//left of 101
		vertex[78] = TexelVertex(-0.5,-1.5,-0.5, 0,1);	//101
		vertex[79] = TexelVertex(-0.5,-1.5,0.5, 0,0);	//102
		vertex[80] = TexelVertex(-0.5,-0.5,0.5, 1,0);	//112	
		
		vertex[81] = TexelVertex(-0.5,-0.5,0.5, 0,1);	//112
		vertex[82] = TexelVertex(-0.5,-0.5,-0.5, 0,0);	//111
		vertex[83] = TexelVertex(-0.5,-1.5,-0.5, 1,0);	//101

		//top of 101
		vertex[85] = TexelVertex(-0.5,-0.5,-0.5, 0,1);	//111
		vertex[84] = TexelVertex(0.5,-0.5,-0.5, 0,0);	//211
		vertex[86] = TexelVertex(0.5,-0.5,0.5, 1,0);	//212	
		
		vertex[88] = TexelVertex(0.5,-0.5,0.5, 0,1);	//212
		vertex[87] = TexelVertex(-0.5,-0.5,0.5, 0,0);	//112
		vertex[89] = TexelVertex(-0.5,-0.5,-0.5, 1,0);	//111
		_vertices->Unlock();
	}
	else if(_pieceId == 3)
	{
		D3DXCreateTextureFromFile(device, "bluepiece.bmp", &_pieceTexture);
		device->CreateVertexBuffer(
			96 * sizeof(TexelVertex), // size in bytes
			D3DUSAGE_WRITEONLY, // flags
			TexelVertex::FVF,        // vertex format
			D3DPOOL_MANAGED,    // managed memory pool
			&_vertices,          // return create vertex buffer
			0);     
		_vertices->Lock(0, 0, (void**)&vertex, 0);
		_noOfTriangles = 32;
		
		// The front of 000, 100, 200
		vertex[0] = TexelVertex(-1.5,-1.5,-1.5,0,1);	//000
		vertex[1] = TexelVertex(-1.5,-0.5,-1.5,0,0);	//010
		vertex[2] = TexelVertex(-0.5,-0.5,-1.5,1,0);	//110
		
		vertex[3] = TexelVertex(-0.5,-0.5,-1.5,1,0);	//110
		vertex[4] = TexelVertex(-0.5,-1.5,-1.5,1,1);	//100
		vertex[5] = TexelVertex(-1.5,-1.5,-1.5,0,1);	//000

		//The left side of 000, 001
		vertex[6] = TexelVertex(-1.5,-1.5,-1.5, 0,1);	//000
		vertex[7] = TexelVertex(-1.5,-1.5,0.5, 0,0);	//002
		vertex[8] = TexelVertex(-1.5,-0.5,0.5, 1,0);	//012

		vertex[9] = TexelVertex(-1.5,-0.5,0.5,0,1);		//012
		vertex[10] = TexelVertex(-1.5,-0.5,-1.5,0,0 );	//010
		vertex[11] = TexelVertex(-1.5,-1.5,-1.5,1,0);	//000
		//Back of 002
		vertex[12] = TexelVertex(-1.5,-1.5,0.5,0,1);	//002
		vertex[13] = TexelVertex(-0.5,-1.5,0.5, 0,0);	//102
		vertex[14] = TexelVertex(-0.5,-0.5,0.5, 1,0);	//112
		
		vertex[15] = TexelVertex(-0.5,-0.5,0.5,0,1);	//112
		vertex[16] = TexelVertex(-1.5,-0.5,0.5,0,0);	//012
		vertex[17] = TexelVertex(-1.5,-1.5,0.5,1,0);	//002
		
		//top of 000 001
		vertex[18] = TexelVertex(-1.5,-0.5,-1.5,0,1); //010
		vertex[19] = TexelVertex(-1.5,-0.5,0.5, 0,0);  //012
		vertex[20] = TexelVertex(-0.5,-0.5,0.5, 1,0); //112
		
		vertex[21] = TexelVertex(-0.5,-0.5,0.5,1,0);	//112
		vertex[22] = TexelVertex(-0.5,-0.5,-1.5,1,1);	//110
		vertex[23] = TexelVertex(-1.5,-0.5,-1.5,0,1);	//010
		//right of 000
		vertex[24] = TexelVertex(-0.5,-1.5,-0.5, 0,0);	//101
		vertex[25] = TexelVertex(-0.5,-1.5,-1.5,0,1);	//100
		vertex[26] = TexelVertex(-0.5,-0.5,-0.5, 1,0);	//111
		
		vertex[27] = TexelVertex(-0.5,-0.5,-1.5,0,0);	//110
		vertex[28] = TexelVertex(-0.5,-0.5,-0.5,0,1);	//111
		vertex[29] = TexelVertex(-0.5,-1.5,-1.5,1,0);	//100

		//front of 101 201
		
		vertex[30] = TexelVertex(-0.5,-1.5,-0.5, 0,1);	//101
		vertex[31] = TexelVertex(-0.5,-0.5,-0.5, 0,0);	//111
		vertex[32] = TexelVertex(1.5,-0.5,-0.5,  1,0);	//311
		
		vertex[33] = TexelVertex(1.5,-0.5,-0.5,1,0);	//311
		vertex[34] = TexelVertex(1.5,-1.5,-0.5,1,1);	//301
		vertex[35] = TexelVertex(-0.5,-1.5,-0.5,0,1);	//101

		//top of 101 201
		vertex[36] = TexelVertex(-0.5,-0.5,-0.5, 0,1); //111
		vertex[37] = TexelVertex(-0.5,-0.5,0.5, 0,0);  //112
		vertex[38] = TexelVertex(1.5,-0.5,0.5, 1,0);  //312

		vertex[39] = TexelVertex(1.5,-0.5,0.5,1,0);		//312
		vertex[40] = TexelVertex(1.5,-0.5,-0.5,1,1);	//311
		vertex[41] = TexelVertex(-0.5,-0.5,-0.5,0,1);	//111
		//right of 201
		vertex[42] = TexelVertex(1.5,-1.5,0.5, 0,0);	//302
		vertex[43] = TexelVertex(1.5,-1.5,-0.5,0,1);	//301
		vertex[44] = TexelVertex(1.5,-0.5,0.5, 1,0);	//312
		
		vertex[45] = TexelVertex(1.5,-0.5,-0.5,0,0);	//311
		vertex[46] = TexelVertex(1.5,-0.5,0.5,0,1);		//312
		vertex[47] = TexelVertex(1.5,-1.5,-0.5,1,0);	//301

		//back of 102
		vertex[48] = TexelVertex(-0.5,-1.5,1.5,0,1);	//103
		vertex[49] = TexelVertex(0.5,-1.5,1.5, 0,0);	//203
		vertex[50] = TexelVertex(0.5,-0.5,1.5, 1,0);	//213
		
		vertex[51] = TexelVertex(0.5,-0.5,1.5,0,1);		//213
		vertex[52] = TexelVertex(-0.5,-0.5,1.5,0,0);	//113
		vertex[53] = TexelVertex(-0.5,-1.5,1.5,1,0);	//103

		//Right of 102
		vertex[54] = TexelVertex(0.5,-1.5,0.5,0,1);		//202
		vertex[55] = TexelVertex(0.5,-0.5,0.5,0,0);		//212
		vertex[56] = TexelVertex(0.5,-0.5,1.5, 1,0);	//213
		
		vertex[57] = TexelVertex(0.5,-0.5,1.5,0,1);		//213
		vertex[58] = TexelVertex(0.5,-1.5,1.5,0,0);		//203
		vertex[59] = TexelVertex(0.5,-1.5,0.5,1,0);		//202
		
		//back of 201
		vertex[60] = TexelVertex(0.5,-1.5,0.5, 1,0);	//202
		vertex[61] = TexelVertex(1.5,-1.5,0.5,0,0);		//302
		vertex[62] = TexelVertex(1.5,-0.5,0.5, 0,1);	//312
		
		vertex[63] = TexelVertex(1.5,-0.5,0.5,0,1);		//312
		vertex[64] = TexelVertex(0.5,-0.5,0.5,1,1);		//212
		vertex[65] = TexelVertex(0.5,-1.5,0.5,1,0);		//202

		//top of 102
		vertex[66] = TexelVertex(-0.5,-0.5,0.5,0,1);	//112
		vertex[67] = TexelVertex(-0.5,-0.5,1.5, 0,0);	//113
		vertex[68] = TexelVertex(0.5,-0.5,1.5, 1,0);	//213
		
		vertex[69] = TexelVertex(0.5,-0.5,1.5,0,1);		//213
		vertex[70] = TexelVertex(0.5,-0.5,0.5,0,0);	//212
		vertex[71] = TexelVertex(-0.5,-0.5,0.5,1,0);	//112
		//left of 102
 		vertex[72] = TexelVertex(-0.5,-1.5,0.5, 0,1);	//102
		vertex[73] = TexelVertex(-0.5,-1.5,1.5, 0,0);	//103
		vertex[74] = TexelVertex(-0.5,-0.5,1.5, 1,0);	//113	
		
		vertex[75] = TexelVertex(-0.5,-0.5,1.5, 0,1);	//113
		vertex[76] = TexelVertex(-0.5,-0.5,0.5, 0,0);	//112
		vertex[77] = TexelVertex(-0.5,-1.5,0.5, 1,0);	//102

		//bottom of 101 201
		vertex[79] = TexelVertex(-0.5,-1.5,-0.5, 0,1); //101
		vertex[78] = TexelVertex(-0.5,-1.5,0.5, 0,0);  //102
		vertex[80] = TexelVertex(1.5,-1.5,0.5, 1,0);  //302

		vertex[82] = TexelVertex(1.5,-1.5,0.5,1,0);		//302
		vertex[81] = TexelVertex(1.5,-1.5,-0.5,1,1);	//301
		vertex[83] = TexelVertex(-0.5,-1.5,-0.5,0,1);	//101

		//bottom of 000 001
		vertex[85] = TexelVertex(-1.5,-1.5,-1.5,0,1);	//000
		vertex[84] = TexelVertex(-1.5,-1.5,0.5, 0,0);	//002
		vertex[86] = TexelVertex(-0.5,-1.5,0.5, 1,0);	//102
		
		vertex[88] = TexelVertex(-0.5,-1.5,0.5,1,0);	//102
		vertex[87] = TexelVertex(-0.5,-1.5,-1.5,1,1);	//100
		vertex[89] = TexelVertex(-1.5,-1.5,-1.5,0,1);	//000

		//bottom of 102
		vertex[91] = TexelVertex(-0.5,-1.5,0.5,0,1);	//102
		vertex[90] = TexelVertex(-0.5,-1.5,1.5, 0,0);	//103
		vertex[92] = TexelVertex(0.5,-1.5,1.5, 1,0);	//203
		
		vertex[94] = TexelVertex(0.5,-1.5,1.5,0,1);		//203
		vertex[93] = TexelVertex(0.5,-1.5,0.5,0,0);		//202
		vertex[95] = TexelVertex(-0.5,-1.5,0.5,1,0);	//102
		_vertices->Unlock();
	}
	else if(_pieceId == 4)
	{
		D3DXCreateTextureFromFile(device, "yellowpiece.bmp", &_pieceTexture);
		_noOfTriangles = 34;
		device->CreateVertexBuffer(
			102 * sizeof(TexelVertex), // size in bytes
			D3DUSAGE_WRITEONLY, // flags
			TexelVertex::FVF,        // vertex format
			D3DPOOL_MANAGED,    // managed memory pool
			&_vertices,          // return create vertex buffer
			0);     
		_vertices->Lock(0, 0, (void**)&vertex, 0);
		
		// The front of 000
		vertex[0] = TexelVertex(-1.5,-1.5,-1.5,0,1);	//000
		vertex[1] = TexelVertex(-1.5,-0.5,-1.5,0,0);	//010
		vertex[2] = TexelVertex(-0.5,-0.5,-1.5,1,0);	//110
		
		vertex[3] = TexelVertex(-0.5,-0.5,-1.5,1,0);	//110
		vertex[4] = TexelVertex(-0.5,-1.5,-1.5,1,1);	//100
		vertex[5] = TexelVertex(-1.5,-1.5,-1.5,0,1);	//000

		//The left side of 000, 001
		vertex[6] = TexelVertex(-1.5,-1.5,-1.5, 0,1);	//000
		vertex[7] = TexelVertex(-1.5,-1.5,0.5, 0,0);	//002
		vertex[8] = TexelVertex(-1.5,-0.5,0.5, 1,0);	//012

		vertex[9] = TexelVertex(-1.5,-0.5,0.5,0,1);		//012
		vertex[10] = TexelVertex(-1.5,-0.5,-1.5,0,0 );	//010
		vertex[11] = TexelVertex(-1.5,-1.5,-1.5,1,0);	//000
		//Back of 002
		vertex[12] = TexelVertex(-1.5,-1.5,0.5,0,1);	//002
		vertex[13] = TexelVertex(-0.5,-1.5,0.5, 0,0);	//102
		vertex[14] = TexelVertex(-0.5,-0.5,0.5, 1,0);	//112
		
		vertex[15] = TexelVertex(-0.5,-0.5,0.5,0,1);	//112
		vertex[16] = TexelVertex(-1.5,-0.5,0.5,0,0);	//012
		vertex[17] = TexelVertex(-1.5,-1.5,0.5,1,0);	//002
		
		//top of 000 001
		vertex[18] = TexelVertex(-1.5,-0.5,-1.5,0,1); //010
		vertex[19] = TexelVertex(-1.5,-0.5,0.5, 0,0);  //012
		vertex[20] = TexelVertex(-0.5,-0.5,0.5, 1,0); //112
		
		vertex[21] = TexelVertex(-0.5,-0.5,0.5,1,0);	//112
		vertex[22] = TexelVertex(-0.5,-0.5,-1.5,1,1);	//110
		vertex[23] = TexelVertex(-1.5,-0.5,-1.5,0,1);	//010
		//right of 000
		vertex[24] = TexelVertex(-0.5,-1.5,-0.5, 0,0);	//101
		vertex[25] = TexelVertex(-0.5,-1.5,-1.5,0,1);	//100
		vertex[26] = TexelVertex(-0.5,-0.5,-0.5, 1,0);	//111
		
		vertex[27] = TexelVertex(-0.5,-0.5,-1.5,0,0);	//110
		vertex[28] = TexelVertex(-0.5,-0.5,-0.5,0,1);	//111
		vertex[29] = TexelVertex(-0.5,-1.5,-1.5,1,0);	//100

		//front of 101
		
		vertex[30] = TexelVertex(-0.5,-1.5,-0.5, 0,1);	//101
		vertex[31] = TexelVertex(-0.5,-0.5,-0.5, 0,0);	//111
		vertex[32] = TexelVertex(0.5,-0.5,-0.5,  1,0);	//211
		
		vertex[33] = TexelVertex(0.5,-0.5,-0.5,1,0);	//211
		vertex[34] = TexelVertex(0.5,-1.5,-0.5,1,1);	//201
		vertex[35] = TexelVertex(-0.5,-1.5,-0.5,0,1);	//101

		//top of 101 102
		vertex[36] = TexelVertex(-0.5,-0.5,-0.5, 0,1); //111
		vertex[37] = TexelVertex(-0.5,-0.5,1.5, 0,0);  //113
		vertex[38] = TexelVertex(0.5,-0.5,1.5, 1,0);   //213

		vertex[39] = TexelVertex(0.5,-0.5,1.5,1,0);		//213
		vertex[40] = TexelVertex(0.5,-0.5,-0.5,1,1);	//211
		vertex[41] = TexelVertex(-0.5,-0.5,-0.5,0,1);	//111
		
		//right of 202
		vertex[42] = TexelVertex(1.5,-1.5,1.5, 0,0);	//303
		vertex[43] = TexelVertex(1.5,-1.5,0.5,0,1);	//302
		vertex[44] = TexelVertex(1.5,-0.5,1.5, 1,0);	//313
		
		vertex[45] = TexelVertex(1.5,-0.5,0.5,0,0);	//312
		vertex[46] = TexelVertex(1.5,-0.5,1.5,0,1);		//313
		vertex[47] = TexelVertex(1.5,-1.5,0.5,1,0);	//302

		//back of 102 202
		vertex[48] = TexelVertex(-0.5,-1.5,1.5,0,1);	//103
		vertex[49] = TexelVertex(1.5,-1.5,1.5, 0,0);	//303
		vertex[50] = TexelVertex(1.5,-0.5,1.5, 1,0);	//313
		
		vertex[51] = TexelVertex(1.5,-0.5,1.5,0,1);		//313
		vertex[52] = TexelVertex(-0.5,-0.5,1.5,0,0);	//113
		vertex[53] = TexelVertex(-0.5,-1.5,1.5,1,0);	//103

		//Left of 102
		vertex[54] = TexelVertex(-0.5,-0.5,0.5,0,0);		//112
		vertex[55] = TexelVertex(-0.5,-1.5,0.5,0,1);		//102
		vertex[56] = TexelVertex(-0.5,-0.5,1.5, 1,0);		//113
		
		vertex[57] = TexelVertex(-0.5,-1.5,1.5,0,0);		//103
		vertex[58] = TexelVertex(-0.5,-0.5,1.5,0,1);		//113
		vertex[59] = TexelVertex(-0.5,-1.5,0.5,1,0);		//102
		
		//front of 201
		vertex[60] = TexelVertex(1.5,-1.5,0.5,0,0);		//302
		vertex[61] = TexelVertex(0.5,-1.5,0.5, 1,0);	//202
		vertex[62] = TexelVertex(1.5,-0.5,0.5, 0,1);	//312
		
		vertex[63] = TexelVertex(0.5,-0.5,0.5,1,1);		//212
		vertex[64] = TexelVertex(1.5,-0.5,0.5,0,1);		//312
		vertex[65] = TexelVertex(0.5,-1.5,0.5,1,0);		//202
		
		//left of 102
		vertex[66] = TexelVertex(-0.5,-1.5,0.5, 0,1);	//102
		vertex[67] = TexelVertex(-0.5,-1.5,1.5, 0,0);	//103
		vertex[68] = TexelVertex(-0.5,-0.5,1.5, 1,0);	//113	
		
		vertex[69] = TexelVertex(-0.5,-0.5,1.5, 0,1);	//113
		vertex[70] = TexelVertex(-0.5,-0.5,0.5, 0,0);	//112
		vertex[71] = TexelVertex(-0.5,-1.5,0.5, 1,0);	//102
		//right of 101
 		vertex[72] = TexelVertex(0.5,-1.5,-0.5, 0,1);	//201
		vertex[73] = TexelVertex(0.5,-0.5,-0.5, 0,0);	//211
		vertex[74] = TexelVertex(0.5,-0.5,0.5, 1,0);	//212	
		
		vertex[75] = TexelVertex(0.5,-0.5,0.5, 0,1);	//212
		vertex[76] = TexelVertex(0.5,-1.5,0.5, 0,0);	//202
		vertex[77] = TexelVertex(0.5,-1.5,-0.5, 1,0);	//201

		//top of 202
		vertex[78] = TexelVertex(0.5,-0.5,0.5,0,1);		//212
		vertex[79] = TexelVertex(0.5,-0.5,1.5, 0,0);	//213
		vertex[80] = TexelVertex(1.5,-0.5,1.5, 1,0);	//313
		
		vertex[81] = TexelVertex(1.5,-0.5,1.5,0,1);		//313
		vertex[82] = TexelVertex(1.5,-0.5,0.5,0,0);		//312
		vertex[83] = TexelVertex(0.5,-0.5,0.5,1,0);		//212
		//bottom of 101 102
		vertex[84] = TexelVertex(-0.5,-1.5,-0.5, 0,1); //101
		vertex[85] = TexelVertex(0.5,-1.5,-0.5, 0,0);  //201
		vertex[86] = TexelVertex(0.5,-1.5,1.5, 1,0);  //203

		vertex[87] = TexelVertex(0.5,-1.5,1.5,1,0);		//203
		vertex[88] = TexelVertex(-0.5,-1.5,1.5,1,1);	//103
		vertex[89] = TexelVertex(-0.5,-1.5,-0.5,0,1);	//101

		//bottom of 000 001
		vertex[91] = TexelVertex(-1.5,-1.5,-1.5,0,1);	//000
		vertex[90] = TexelVertex(-1.5,-1.5,0.5, 0,0);	//002
		vertex[92] = TexelVertex(-0.5,-1.5,0.5, 1,0);	//102
		
		vertex[94] = TexelVertex(-0.5,-1.5,0.5,1,0);	//102
		vertex[93] = TexelVertex(-0.5,-1.5,-1.5,1,1);	//100
		vertex[95] = TexelVertex(-1.5,-1.5,-1.5,0,1);	//000

		//bottom of 202
		vertex[97] = TexelVertex(0.5,-1.5,0.5,0,1);	//202
		vertex[96] = TexelVertex(0.5,-1.5,1.5, 0,0);	//203
		vertex[98] = TexelVertex(1.5,-1.5,1.5, 1,0);	//303
		
		vertex[100] = TexelVertex(1.5,-1.5,1.5,0,1);		//303
		vertex[99] = TexelVertex(1.5,-1.5,0.5,0,0);		//302
		vertex[101] = TexelVertex(0.5,-1.5,0.5,1,0);	//202

		_vertices->Unlock();	
	}
	else if(_pieceId == 5)
	{
		_noOfTriangles = 24;
		D3DXCreateTextureFromFile(device, "yellowpiece.bmp", &_pieceTexture);
				device->CreateVertexBuffer(
			72 * sizeof(TexelVertex), // size in bytes
			D3DUSAGE_WRITEONLY, // flags
			TexelVertex::FVF,        // vertex format
			D3DPOOL_MANAGED,    // managed memory pool
			&_vertices,          // return create vertex buffer
			0);     
		_vertices->Lock(0, 0, (void**)&vertex, 0);
		
		// The front of 000, 100, 200
		vertex[0] = TexelVertex(1.5,-0.5,-1.5, 0,1);
		vertex[1] = TexelVertex(1.5,-1.5,-1.5,0,0);
		vertex[2] = TexelVertex(-1.5,-1.5,-1.5, 1,0);
		
		vertex[3] = TexelVertex(-1.5,-1.5,-1.5, 0,1);
		vertex[4] = TexelVertex(-1.5,-0.5,-1.5,0,0);
		vertex[5] = TexelVertex(1.5,-0.5,-1.5, 1,0);

		//top of 000, 100 and 200
		vertex[6] = TexelVertex(1.5,-0.5,-0.5,0,1);
		vertex[7] = TexelVertex(1.5,-0.5,-1.5, 0,0);
		vertex[8] = TexelVertex(-1.5,-0.5,-1.5, 1,0);
		
		vertex[9] = TexelVertex(-1.5,-0.5,-1.5,0,1);
		vertex[10] = TexelVertex(-1.5,-0.5,-0.5,0,0);
		vertex[11] = TexelVertex(1.5,-0.5,-0.5,1,0);
		
		//bottom of 000,100 and 200
		vertex[12] = TexelVertex(1.5,-1.5,-1.5, 1,0);
		vertex[13] = TexelVertex(1.5,-1.5,-0.5,1,1);
		vertex[14] = TexelVertex(-1.5,-1.5,-1.5, 0,0);
		
		vertex[15] = TexelVertex(-1.5,-1.5,-0.5,0,1);
		vertex[16] = TexelVertex(-1.5,-1.5,-1.5,0,0);
		vertex[17] = TexelVertex(1.5,-1.5,-0.5,1,1);
		
		//The right side of 200
		vertex[18] = TexelVertex(1.5,-0.5,-0.5, 0,1);
		vertex[19] = TexelVertex(1.5,-1.5,-0.5, 0,0);
		vertex[20] = TexelVertex(1.5,-1.5,-1.5, 1,0);

		vertex[21] = TexelVertex(1.5,-1.5,-1.5,0,1);
		vertex[22] = TexelVertex(1.5,-0.5,-1.5,0,0 );
		vertex[23] = TexelVertex(1.5,-0.5,-0.5,1,0);
		
		//back of 101 201
		vertex[25] = TexelVertex(-0.5,-1.5,-0.5, 0,1);	//101
		vertex[24] = TexelVertex(-0.5,-0.5,-0.5, 0,0);	//111
		vertex[26] = TexelVertex(1.5,-0.5,-0.5,  1,0);	//311
		
		vertex[28] = TexelVertex(1.5,-0.5,-0.5,1,0);	//311
		vertex[27] = TexelVertex(1.5,-1.5,-0.5,1,1);	//301
		vertex[29] = TexelVertex(-0.5,-1.5,-0.5,0,1);	//101

		//The left side of 000, 001
		vertex[30] = TexelVertex(-1.5,-1.5,-1.5, 0,1);	//000
		vertex[31] = TexelVertex(-1.5,-1.5,0.5, 0,0);	//002
		vertex[32] = TexelVertex(-1.5,-0.5,0.5, 1,0);	//012

		vertex[33] = TexelVertex(-1.5,-0.5,0.5,0,1);		//012
		vertex[34] = TexelVertex(-1.5,-0.5,-1.5,0,0 );	//010
		vertex[35] = TexelVertex(-1.5,-1.5,-1.5,1,0);	//000

		//left of 011
		vertex[36] = TexelVertex(-1.5,-0.5,-0.5, 0,1); //011
		vertex[37] = TexelVertex(-1.5,-0.5,0.5, 0,0);  //012
		vertex[38] = TexelVertex(-1.5,0.5,0.5, 1,0);   //022

		vertex[39] = TexelVertex(-1.5,0.5,0.5,1,0);		//022
		vertex[40] = TexelVertex(-1.5,0.5,-0.5,1,1);	//021
		vertex[41] = TexelVertex(-1.5,-0.5,-0.5,0,1);	//011
		
		//front of 011
		vertex[42] = TexelVertex(-1.5,-0.5,-0.5, 0,1);	//011
		vertex[43] = TexelVertex(-1.5,0.5,-0.5,0,0);	//021
		vertex[44] = TexelVertex(-0.5,0.5,-0.5, 1,0);	//121
		
		vertex[45] = TexelVertex(-0.5,0.5,-0.5,1,0);	//121
		vertex[46] = TexelVertex(-0.5,-0.5,-0.5,1,1);	//111
		vertex[47] = TexelVertex(-1.5,-0.5,-0.5,0,1);	//011

		// The right side of 001, 011
		vertex[49] = TexelVertex(-0.5,-1.5,-0.5, 0,1);
		vertex[48] = TexelVertex(-0.5,-1.5,0.5, 0,0);
		vertex[50] = TexelVertex(-0.5,0.5,0.5, 1,0);
		
		vertex[52] = TexelVertex(-0.5,0.5,0.5, 1,0);
		vertex[51] = TexelVertex(-0.5,0.5,-0.5, 1,1);
		vertex[53] = TexelVertex(-0.5,-1.5,-0.5, 0,1);
		//top of 021
		vertex[54] = TexelVertex(-1.5,0.5,-0.5, 0,1); //021
		vertex[55] = TexelVertex(-1.5,0.5,0.5, 0,0);//022
		vertex[56] = TexelVertex(-0.5,0.5,0.5, 1,0);//122

		vertex[57] = TexelVertex(-0.5,0.5,0.5,1,0);//122
		vertex[58] = TexelVertex(-0.5,0.5,-0.5,1,1);//121
		vertex[59] = TexelVertex(-1.5,0.5,-0.5,0,1);//021
		//back of 001 011
		vertex[60] = TexelVertex(-1.5,-1.5,0.5,0,1);   //002
		vertex[61] = TexelVertex(-0.5,-1.5,0.5,0,0);	//102
		vertex[62] = TexelVertex(-0.5,0.5,0.5, 1,0);	//122
		
		vertex[63] = TexelVertex(-0.5,0.5,0.5,0,1);	//122
		vertex[64] = TexelVertex(-1.5,0.5,0.5,0,0);	//022
		vertex[65] = TexelVertex(-1.5,-1.5,0.5,1,0);	//002
		
		//bottom of 001
		vertex[67] = TexelVertex(-1.5,-1.5,-0.5,0,1);	//001
		vertex[66] = TexelVertex(-1.5,-1.5,0.5, 0,0);	//002
		vertex[68] = TexelVertex(-0.5,-1.5,0.5, 1,0);	//102
		
		vertex[70] = TexelVertex(-0.5,-1.5,0.5,1,0);	//102
		vertex[69] = TexelVertex(-0.5,-1.5,-0.5,1,1);	//101
		vertex[71] = TexelVertex(-1.5,-1.5,-0.5,0,1);	//001
		_vertices->Unlock();
	}
	return true;
}

void GraPiece::draw(IDirect3DDevice9* device)
{	
	D3DXMATRIX trans;
	D3DXMATRIX rotX, rotY, rotZ;
	D3DXMatrixTranslation(&trans, _pos.x, _pos.y, _pos.z);
	D3DXMatrixRotationX(& rotX, _rX);
	D3DXMatrixRotationY(& rotY, _rY);
	D3DXMatrixRotationZ(& rotZ, _rZ);
	device->SetStreamSource(0, _vertices, 0, sizeof(TexelVertex));	
	device->SetFVF(TexelVertex::FVF);
	device->SetTexture(0,_pieceTexture);
	device->SetTransform(D3DTS_WORLD, &(rotX * rotY * rotZ* trans));
	device->SetRenderState(D3DRS_LIGHTING, FALSE);
	device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, _noOfTriangles);
} 
