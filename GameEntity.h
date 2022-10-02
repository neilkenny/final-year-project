#ifndef __GameEntityH__
#define __GameEntityH__

#include <d3dx9.h>
#include <vector>

#include "drawableentity.h"
//#include "boundableentity.h"
#include "moveableentity.h"

class World;



class GameEntity:public DrawableEntity, public MoveableEntity
{
public:
		GameEntity();
		~GameEntity();

		bool setup(IDirect3DDevice9* Device);		
		void GameEntity::update(float timeDelta);		
		void GameEntity::draw(IDirect3DDevice9* Device);
		void GameEntity::cleanup(IDirect3DDevice9* Device);
		
		float getOrientation();
		void setOrientation(float orientation );		

		int getID() { return _id;}
		static int _nextID;
		int _id;
protected:
	IDirect3DDevice9 * _device;
	IDirect3DVertexBuffer9* vertices; 
	IDirect3DTexture9 * pieceTexture;
	float _fov;
};

#endif // __gameEntityH__