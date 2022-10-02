#ifndef _GraPiece_
#define _GraPiece_
#include "GameEntity.h"


class GraPiece: public GameEntity
{
public:
	GraPiece();
	GraPiece(int pieceId);
	//GraPiece(IDirect3DDevice9 * device);
	bool setup(IDirect3DDevice9* Device); // override from GameEntity
	void draw(IDirect3DDevice9* Device); // override from GameEntity
	void update(float timeDelta); // override from GameEntity
	bool getVisible();
	void setVisible(bool value);
	int getPieceId();
	int getNoOfTriangles();
	float getElapsedTime();
	void resetPiece();
	void setElapsedTime(float time);
	void setRotationX(float value);
	void setRotationY(float value);
	void setRotationZ(float value);
	int getRotCorrectionX(){return _rotCorrectionX;};
	int getRotCorrectionY(){return _rotCorrectionY;};
	int getRotCorrectionZ(){return _rotCorrectionZ;};
//	void setRotationOffsetX(int value){_rotationOffsetX = value;};
//	void setRotationOffsetY(int value){_rotationOffsetY = value;};
//	void setRotationOffsetZ(int value){_rotationOffsetZ = value;};
//	int getRotationOffsetX(){return _rotationOffsetX;};
//	int getRotationOffsetY(){return _rotationOffsetY;};
//	int getRotationOffsetZ(){return _rotationOffsetZ;};
	void setRotCorrectionX(int value){_rotCorrectionX = value;};
	void setRotCorrectionY(int value){_rotCorrectionY = value;};
	void setRotCorrectionZ(int value){_rotCorrectionZ = value;};
	float getRotationX();
	float getRotationY();
	float getRotationZ();			 

protected:
	bool _visible;
	int _pieceId;
	int _noOfTriangles;
	float _elapsedTime;
	//int _rotationOffsetX;
	//int _rotationOffsetY;
	//int _rotationOffsetZ;
	int _rotCorrectionX;
	int _rotCorrectionY;
	int _rotCorrectionZ;
	IDirect3DVertexBuffer9* _vertices; 
	IDirect3DTexture9 * _pieceTexture;
	float _rX;
	float _rY;
	float _rZ;
};







#endif