#include<string>
#include <iostream>
#include"Main.h"
#include<time.h>
const int NOOFPIECES = 13;
using namespace std;
Main::Main()
{	
	setBounds(800, 600);
	setWindowed(true);
	setConsole(true);
	setFiltering(true);
	_camera = new Camera();
	_world = new World();
	_camera->setWorld(_world);
	_world->setCamera(_camera);
	_world->setMain(this);
}


int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE prevInstance, PSTR cmdLine,int showCmd)
{
	Main * instance = new Main();
	instance->main(hinstance);
}

LRESULT CALLBACK Main::handleEvent(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	
	int deltaX, deltaY, midX, midY, xPos, yPos;
	switch( msg )
	{
		case WM_SETCURSOR:
			// Turn off window cursor 
			SetCursor(NULL);			
			_device->ShowCursor(TRUE);
			return TRUE; // prevent Windows from setting cursor to window class cursor
			break;
		case WM_DESTROY:
			::PostQuitMessage(0);
			break;		
		case WM_KEYDOWN:
			if(wParam == VK_ESCAPE)
			{
				::DestroyWindow(hwnd);
			}

			if( wParam == VK_UP)
			{	
				if(_world->getCurrentPiece()!=NULL && _world->getBox()->getPiece() != NULL)
				{
					_world->getBox()->movePieceMoreZ();
				}
			}
			if( wParam == VK_DOWN)
			{	if(_world->getCurrentPiece()!=NULL && _world->getBox()->getPiece() != NULL)
				{
					_world->getBox()->movePieceLessZ();
				}
			}
			if( wParam == VK_LEFT)
			{	
				if(_world->getCurrentPiece()!=NULL && _world->getBox()->getPiece() != NULL)
				{
					_world->getBox()->movePieceLessX();
				}
			}
			if( wParam == VK_RIGHT)
			{	
				if(_world->getCurrentPiece()!=NULL && _world->getBox()->getPiece() != NULL)
				{
					_world->getBox()->movePieceMoreX();
				}
			}
			if( wParam == VK_SPACE)
			{	
				if(_world->getCurrentPiece()!=NULL && _world->getBox()->getPiece() != NULL)
				{
					_world->getBox()->dropPiece();
                }
			}
			if( ::GetAsyncKeyState('X') & 0x8000f )
			{
				if(_world->getCurrentPiece()!=NULL && _world->getBox()->getPiece() != NULL)
				{
					_world->getBox()->rotatePieceX();
				}
			}
			if( ::GetAsyncKeyState('Y') & 0x8000f )
			{
				if(_world->getCurrentPiece()!=NULL && _world->getBox()->getPiece() != NULL)
				{
					_world->getBox()->rotatePieceY();
				}
			}
			/*if( ::GetAsyncKeyState(VK_SHIFT) & 0x8000f && ::GetAsyncKeyState('1'))
			{

				_world->getBox()->removePiece(_world->getPiece(0));
				if (_world->getBox()->getPiece() == _world->getPiece(0))
				{
					_world->setCurrentPiece(NULL);
				}

			}*/
			if( ::GetAsyncKeyState('Z') & 0x8000f )
			{
				if(_world->getCurrentPiece()!=NULL && _world->getBox()->getPiece() != NULL)
				{
					_world->getBox()->rotatePieceZ();
				}
			}
			if( ::GetAsyncKeyState('L') & 0x8000f )
			{
				_depthFirst = new DepthFirst(_world->getBox());
				for(int i=0; i<13; i++)
				{
					cout << "Setting piece " << i << "\n";
					_depthFirst->setPiece(i, _world->getPiece(i));
				}
				_depthFirst->solve();
			}
			if( ::GetAsyncKeyState('K') & 0x8000f )
			{
				_genetic = new Genetic(_world->getBox());
				for(int i=0; i<13; i++)
				{
					cout << "Setting piece " << i << "\n";
					_genetic->setPiece(_world->getPiece(i),i);
				}
				_genetic->solve();

			}
			if( ::GetAsyncKeyState('J') & 0x8000f )
			{
				_SimulatedAnnealing = new SimulatedAnnealing(_world->getBox());
				for(int i=0; i<13; i++)
				{
					cout << "Setting piece " << i << "\n";
					_SimulatedAnnealing->setPiece(_world->getPiece(i),i);
				}
				_SimulatedAnnealing->solve();

			}
			break;
		case WM_MOUSEMOVE:
			midX = _width / 2;
			midY = _height / 2;
			POINT p;
			GetCursorPos(&p);
			xPos = p.x;
			yPos = p.y;

			if ((xPos == midX) && (yPos == midY)) 
			{			
				break;
			}		
			deltaX = xPos - midX;
			deltaY = yPos - midY;
			_camera->yaw(((float)deltaX) / 100.0f);
			_camera->pitch(((float)deltaY) / 100.0f);				
			SetCursorPos(midX, midY);
			break;
		case WM_LBUTTONDOWN:
			
			break;
	}
	return ::DefWindowProc(hwnd, msg, wParam, lParam);
}

bool Main::setup(IDirect3DDevice9 * device)
{
	cout << "Main::Setup\n";
	bool success;
	// Call the superclass setup
	success = Direct3DBase::setup(device);

	if (success) 
	{
		success = _world->setup(device);			
	}
	_camera->setDevice(device);
	
	return success;
}


void Main::update(float timeDelta)
{
	_world->update(timeDelta);
}

void Main::draw(IDirect3DDevice9 * device)
{
	_world->draw(device);
	D3DXMATRIX V;
	_camera->getViewMatrix(& V);
	device->SetTransform(D3DTS_VIEW, &V);
}

void Main::cleanup(IDirect3DDevice9 * device)
{
	Direct3DBase::cleanup(device);
	_world->cleanup(device);
}

Main::~Main()
{
	delete _world;
	delete _camera;
	if(_depthFirst != NULL)
	{
		delete _depthFirst;
	}
}




