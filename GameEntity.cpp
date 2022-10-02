#include <vector>
#include "GameEntity.h"
#include "world.h"

int GameEntity::_nextID = 0; 

GameEntity::GameEntity() 
{	
    _pos   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	
	_look  = D3DXVECTOR3(0.0f, 0.0f, 1.0f);	
	_fov = D3DX_PI / 2; // 90 Degrees
	_world = NULL;	
	_id = _nextID;
	_nextID ++;
	
}

GameEntity::~GameEntity()
{
}

bool GameEntity::setup(IDirect3DDevice9* device) 
{
	return true;//ret;
}

void GameEntity::update(float timeDelta)
{
	//setCentrePoint(& (_pos + _meshWrapper->getCenter()));
	//THE CENTER POINT OF THE PIECE COULD BE CHANGED HERE IF IT IS NEEDED
}

void GameEntity::draw(IDirect3DDevice9* device)
{	
	D3DXMATRIX antPos;
	D3DXMatrixTranslation(&antPos, _pos.x, _pos.y, _pos.z);

	D3DXMATRIX antLook;			
	D3DXMatrixRotationY(&antLook, getOrientation());	
	D3DXMATRIX rotationX;	
	D3DXMatrixRotationX(&rotationX, D3DX_PI/2);	
	D3DXMATRIX antScale;		
	D3DXMatrixScaling(&antScale, 1,1,1);

	D3DXMATRIX antMatrix;
	antMatrix = antLook * antPos;

	device->SetTransform(D3DTS_WORLD, &antMatrix);
}

float GameEntity::getOrientation() 
{
	float orientation;
	D3DXVECTOR3 up = D3DXVECTOR3(0, 0, 1);

	orientation = acos((D3DXVec3Dot(& up, & _look)));
	if (_look.x < 0)
	{
		orientation = (2 * D3DX_PI) - orientation;
	}
	return orientation;
}

void GameEntity::setOrientation(float orientation) 
{

	if (orientation > (D3DX_PI * 2))
	{
		orientation = orientation - (D3DX_PI * 2);
	}

	D3DXVECTOR3 look;

	look.x = sin(orientation);
	look.y = 0;
	look.z = cos(orientation);	

	D3DXVec3Normalize(& look, & look);
	setLook(&look);
}


void GameEntity::cleanup(IDirect3DDevice9 * device)
{
}
