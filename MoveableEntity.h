#ifndef __MoveableEntityH__
#define __MoveableEntityH__

#include <d3dx9.h>


class World;
class Camera;

class MoveableEntity
{
	public:
		MoveableEntity();
		void strafe(float units); 
		void fly(float units);    
		void walk(float units);   		

		void pitch(float angle); // rotate on right vector
		void yaw(float angle);   // rotate on up vector
		void roll(float angle);  // rotate on look vector

		void setSpeed(float speed) {_speed = speed;}
		float getSpeed() {return _speed;}		

		D3DXVECTOR3 getPosition(); 
		void setPosition(D3DXVECTOR3* pos);
		
		int getXPosition();
		int getYPosition();
		int getZPosition();

		void setLook(D3DXVECTOR3* look);
		D3DXVECTOR3 getLook();

		void setWorld(World * world);
		World * getWorld() { return _world;}
		void floorPos();
	protected:
		D3DXVECTOR3 _right;
		D3DXVECTOR3 _up;		
		D3DXVECTOR3 _look;
		D3DXVECTOR3 _pos;
		float _speed;
		World * _world;
};
#endif // __MoveableEntityH__
		