#pragma once

#include "Library Header\Win32.h"
#include "Library Header\\GameSystem.h"
#include "GameInMain.h"

class _GAME{
private:
	static _GAME* m_pSingleton;

	_GAME();
	~_GAME();
public:
	static _GAME* GetSingleton();
	static void Destroy();

private:
	Object main;
	Camera main_cam;

	UINT mouse_x, mouse_y;
	unsigned char LButton;
	INT temp;
	GameState state;
	_GIMain* game;

public:
	void Init();
	void update();

private:
	Object title;
};