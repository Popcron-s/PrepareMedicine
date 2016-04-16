#pragma once

#include "GameInGame.h"

#include <iostream>

class _GIMain{
private:
	Camera sub_cam;
	Object main;
	Object main_menu;
	Object Item[3];
	Object Number[9];
	Object ShopWindow;

	INT m_Gold;
	unsigned char m_Item[3];

	UINT* m_Mouse_x, *m_Mouse_y;
	unsigned char* m_LButton;

	GameState* m_state;
	_GIGame* m_Game;

public:
	_GIMain();
	~_GIMain();

	void Init(Camera, GameState* state, UINT* mouse_x, UINT* mouse_y, unsigned char* LButton);
	void update();

	void ShopInit();
	void Shop();

	bool Save();
	bool Load();
};