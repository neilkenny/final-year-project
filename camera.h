#ifndef __cameraH__
#define __cameraH__

#include <d3dx9.h>
#include "moveableentity.h"
#include "world.h"

class Camera:public MoveableEntity
{
public:
	
	Camera();
	~Camera();
	void getViewMatrix(D3DXMATRIX* ); 
	void setDevice(IDirect3DDevice9 * device);
protected:
	IDirect3DDevice9 * _device;
};
#endif // __cameraH__