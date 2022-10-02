#include "MoveableEntity.h"
#include "world.h"
#include "camera.h"
#include <d3dx9.h>

MoveableEntity::MoveableEntity() 
{
	_right = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	_up    = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	_speed = 5;
}

void MoveableEntity::floorPos()
{
	_pos.x = floor(_pos.x); _pos.y = floor(_pos.y); _pos.z = floor(_pos.z);
}

void MoveableEntity::walk(float units)
{
	D3DXVECTOR3 newPos;

	newPos = _pos + D3DXVECTOR3(_look.x, 0.0f, _look.z) * units;
	_pos = newPos;
	
}

/*void MoveableEntity::circle(float units)
{
	D3DXVECTOR3 newPos;
}*/

void MoveableEntity::strafe(float units)
{
	D3DXVECTOR3 newPos;
	newPos = _pos + D3DXVECTOR3(_right.x, 0.0f, _right.z) * units;
	_pos = newPos;

}

void MoveableEntity::fly(float units)
{
	_pos.y += units;
}

void MoveableEntity::pitch(float angle)
{
	D3DXMATRIX T;
	D3DXMatrixRotationAxis(&T, &_right,	angle);

	// rotate _up and _look around _right vector
	D3DXVec3TransformCoord(&_up,&_up, &T);
	D3DXVec3TransformCoord(&_look,&_look, &T);
}

void MoveableEntity::yaw(float angle)
{
	D3DXMATRIX T;

	D3DXMatrixRotationY(&T, angle);

	// rotate _right and _look around _up or y-axis
	D3DXVec3TransformCoord(&_right,&_right, &T);
	D3DXVec3TransformCoord(&_look,&_look, &T);
}

void MoveableEntity::roll(float angle)
{
	D3DXMATRIX T;
	D3DXMatrixRotationAxis(&T, &_look,	angle);

		// rotate _up and _right around _look vector
	D3DXVec3TransformCoord(&_right,&_right, &T);
	D3DXVec3TransformCoord(&_up,&_up, &T);
}

int MoveableEntity::getXPosition()
{
	return _pos.x;
}

int MoveableEntity::getYPosition()
{
	return _pos.y;
}
int MoveableEntity::getZPosition()
{
	return _pos.z;
}
D3DXVECTOR3 MoveableEntity::getPosition()
{
	return _pos;
}

D3DXVECTOR3 MoveableEntity::getLook()
{
	return _look;
}


void MoveableEntity::setPosition(D3DXVECTOR3* pos)
{	
	_pos = *pos;
}

void MoveableEntity::setLook(D3DXVECTOR3* look)
{	
	_look = * look;
	// Keep camera's axes orthogonal to eachother
	D3DXVec3Normalize(&_look, &_look);

	D3DXVec3Cross(&_right, &_up, &_look);
	D3DXVec3Normalize(&_right, &_right);


	D3DXVec3Cross(&_up, &_look, &_right);
	D3DXVec3Normalize(&_up, &_up);

}

void MoveableEntity::setWorld(World * world)
{
	_world = world;
}
