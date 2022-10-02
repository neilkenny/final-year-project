#include "world.h"
#include <d3dx9.h>
#include <stdio.h>
#include <vector>
#include "direct3dbase.h"
#include<iostream>
#include "camera.h"

using namespace std;
const int NOOFPIECES = 13;

World::World()
{
	_camera = NULL;
	_currentPiece = NULL;
	for(int i=0; i<8; i++)
	{
        line[i] = NULL;
	}
}

World::World(Main * main)
{
	_main = main;
	_camera = NULL;
	_currentPiece = NULL;
	for(int i=0; i<8; i++)
	{
		line[i] = NULL;
	}
}

World::~World()
{
	
}

void World::load()
{
	_box = new Box();
}

bool World::setup(IDirect3DDevice9 * device) 
{
	bool retVal = true;
	_device = device;
	load();
	//setup the pieces
	for(int i=0; i<NOOFPIECES; i++)
	{
		_piece[i] = new Piece(i);
		_piece[i]->setup(device);
	}
	//setup the lines
	for(int i=0; i<8; i++)
	{
		line[i] = new Line3D();
		line[i]->setup(device);
	}
	//set the endpoints of the lines
	line[0]->setEndPoints(-1.5,-1.5,-1.5,2.5,-1.5,-1.5,new D3DCOLOR(0,0,0));
	line[1]->setEndPoints(-1.5,-1.5,-1.5,-1.5,-1.5,2.5,new D3DCOLOR(0,0,0));
	line[2]->setEndPoints(-1.5,-1.5,-1.5,-1.5,2.5,-1.5,new D3DCOLOR(0,0,0));
	line[3]->setEndPoints(-1.5,-1.5,2.5,2.5,-1.5,2.5,new D3DCOLOR(0,0,0));
	line[4]->setEndPoints(-1.5,-1.5,2.5,-1.5,2.5,2.5,new D3DCOLOR(0,0,0));
	line[5]->setEndPoints(2.5,-1.5,2.5,2.5,2.5,2.5,new D3DCOLOR(0,0,0));
	line[6]->setEndPoints(2.5,-1.5,2.5,2.5,-1.5,-1.5,new D3DCOLOR(0,0,0));
	line[7]->setEndPoints(2.5,-1.5,-1.5,2.5,2.5,-1.5,new D3DCOLOR(0,0,0));

	return true;
}

void World::update(float timeDelta) 
{
	if( ::GetAsyncKeyState('1'))	//Chosose piece0
	{	
		if(_currentPiece!=_piece[0])
		{
			_box->setPiece(_piece[0]);
			_currentPiece= _box->getPiece();
            _piece[0]->setVisible(true);
		}
	}
	if( ::GetAsyncKeyState('2') & 0x8000f )//Chosose piece1
	{	
		if(_currentPiece!=_piece[1])
		{
			_box->setPiece(_piece[1]);
			_currentPiece = _box->getPiece();
			_piece[1]->setVisible(true);
		}
	}
	if( ::GetAsyncKeyState('3') & 0x8000f )//Chosose piece2
	{	
		if(_currentPiece!=_piece[2])
		{
			_box->setPiece(_piece[2]);
			_currentPiece= _box->getPiece();
            _piece[2]->setVisible(true);
		}
	}
	if( ::GetAsyncKeyState('4') & 0x8000f )//Chosose piece3
	{	
		if(_currentPiece!=_piece[3])
		{
			_box->setPiece(_piece[3]);
			_currentPiece= _box->getPiece();
            _piece[3]->setVisible(true);
		}
	}
	if( ::GetAsyncKeyState('5') & 0x8000f )//Chosose piece4
	{	
		if(_currentPiece!=_piece[4])
		{
			_box->setPiece(_piece[4]);
			_currentPiece= _box->getPiece();
            _piece[4]->setVisible(true);
		}
	}
	if( ::GetAsyncKeyState('6') & 0x8000f ) //Chosose piece5
	{	
		if(_currentPiece!=_piece[5])
		{
			_box->setPiece(_piece[5]);
			_currentPiece= _box->getPiece();
            _piece[5]->setVisible(true);
		}
	}
	if( ::GetAsyncKeyState('W') & 0x8000f ) //Move camera forward
	{	
		_camera->walk(5*timeDelta);
	}
	if( ::GetAsyncKeyState('S') & 0x8000f ) //Move camera backward
	{	
		_camera->walk(-5*timeDelta);
	}
	if( ::GetAsyncKeyState('A') & 0x8000f ) //Move camera left
	{
		_camera->strafe(-5*timeDelta);
	}
	if( ::GetAsyncKeyState('D') & 0x8000f ) //Move camera right
	{
		_camera->strafe(5*timeDelta);
	}
	if( ::GetAsyncKeyState('R') & 0x8000f ) //Move camera up
	{
		_camera->fly(5*timeDelta);
	}
	if( ::GetAsyncKeyState('F') & 0x8000f ) //Move camera down
	{
		_camera->fly(-5*timeDelta);
	}

}

void World::draw(IDirect3DDevice9* device) 
{
	//draw the box
	for(int i=0; i<8; i++)
	{
		line[i]->draw(device);
	}			
	//draw the visible pieces
	for(int i=0; i<NOOFPIECES; i++)
	{
		if(_piece[i]->getVisible() == true)
		{
			_piece[i]->draw(device);
		}
	}
}

void World::cleanup(IDirect3DDevice9 * device) 
{
	device->Release();
}


void World::setCamera(Camera * cam)
{
	_camera = cam;
}

Camera * World::getCamera()
{
	return _camera;
}

Box * World::getBox()
{
	return _box;
}

Piece * World::getCurrentPiece()
{
	return _currentPiece;
}
