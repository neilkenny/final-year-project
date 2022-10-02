#ifndef __Main__
#define __Main__

#include "Direct3dbase.h"
#include "world.h"
#include"Camera.h"
#include "Genetic.h"
#include "depthFirst.h"
#include "SimulatedAnnealing.h"
#include <windowsx.h>
#include <stdio.h>
#include <d3dx9.h>
class DepthFirst;
class World;
class Main:public Direct3DBase
{

public:
		Main();
		~Main();

		LRESULT CALLBACK handleEvent(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

		bool setup(IDirect3DDevice9 * device);
		void update(float timeDelta);
		void draw(IDirect3DDevice9 * device);
		void cleanup(IDirect3DDevice9 * device);
		
	private:
		World * _world;
		Camera * _camera;
		DepthFirst * _depthFirst;
		Genetic * _genetic;
		SimulatedAnnealing * _SimulatedAnnealing;
};

#endif