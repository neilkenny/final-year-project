#ifndef __DrawableEntityH__
#define __DrawableEntityH__


class DrawableEntity
{
public: 	virtual bool setup(IDirect3DDevice9* device) {_device = device; return true;}
	virtual void draw(IDirect3DDevice9* Device) {};
	virtual void update(float timeDelta) {};
	virtual void cleanup(IDirect3DDevice9 * device) {};

protected:
	IDirect3DDevice9* _device;
};

#endif