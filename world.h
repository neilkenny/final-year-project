#ifndef __worldH__
#define __worldH__

#include <d3dx9.h>
#include <vector>
#include "drawableentity.h"
#include"Piece.h"
#include "box.h"
#include "line3d.h"
#include "Main.h"
class Camera;
class Main;
class World:public DrawableEntity
{	
protected:	
	IDirect3DDevice9 * _device;
	Camera * _camera;
	Piece * _piece[13];
	Piece * _currentPiece;
	Box * _box;
	Line3D * line[8];
	Main * _main;
	void load();
public:
	World();
	World(Main * main);
	~World();
	void setMain(Main * main){_main = main;};
	bool setup(IDirect3DDevice9 * device); // override from the superclass
	void update(float timeDelta); // override from the superclass
	void draw(IDirect3DDevice9 * device); // override from the superclass
	void cleanup(IDirect3DDevice9 * device);
	void setCamera(Camera * camera);
	void setBox(Box * box);
	Piece * getPiece(int i){return _piece[i];};
	Camera * getCamera();
	void setCurrentPiece(Piece * piece){_currentPiece = piece;};
	Piece * getCurrentPiece();
	Box * getBox();


};
#endif // __worldH__

