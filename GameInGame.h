#pragma once

#include "Library Header\\GameSystem.h"
#include "Library Header\\Variable.h"

#include <stdlib.h>
#include "Library Header\\Win32.h"

enum GameState{
	TITLE,
	OPTION,
	MAIN,
	SHOP,
	PLAY,
	SAVE,
	LOAD
};

enum DIR{
	DIR_UP,DIR_DOWN,DIR_LEFT,DIR_RIGHT
};

enum TYPE{
	TYPE_PURPLE, TYPE_BLUE, TYPE_YELLOW, TYPE_RED, TYPE_GREEN
};

class _Tile{
private:
	Object m_Image;
	_VERTEX vtx[4];
	_Tile** m_near[4];

	TYPE m_Type;
	bool m_on;

public:
	_Tile();
	~_Tile();

	void SetLight(bool);
	bool IsLight();

	void SetType(TYPE);
	TYPE GetType();

	void SetNearTile(_Tile** top, _Tile** bottom, _Tile** left, _Tile** right);
	_Tile* GetTile(DIR);
	_Tile** GetTilePointer(DIR);

	void RegisterImage(Camera cam);
	void SetImagePosition(FLOAT x, FLOAT y);
	_vector3 GetImagePosition() const;
};

class _Effect{
private:
	static Object main;
	Object m_Image;

	INT m_Frame;
	UINT m_RefTime;

	~_Effect();
public:
	_Effect(Camera sub);

	static void Create(Camera, _vector3);
	static void Destroy(_Effect*);

	bool update();
	void SetPosition(_vector3);

	struct list{
		_Effect* _node;
		list* _next;
		list* _prev;
	}static *m_list;
};

class _GIGame{
private:
	Camera sub_cam;
	Object m_BG;
	Object m_Window[3];
	Object m_Icon[2];

	Object m_ScoreCount[8];
	Object m_TimeCount[3];

	_Tile** m_Tile;
	UINT m_Tile_x, m_Tile_y;
	UINT m_Col;
	INT m_Time;
	INT m_Score;

	INT* m_TotalGold;

	UINT* m_Mouse_x, *m_Mouse_y;
	unsigned char* m_LButton;
	GameState* m_state;

	INT m_RefTime;
	bool m_Over;

private:
	void SetTile(INT type_num, INT tile_x, INT tile_y);

public:
	_GIGame();
	~_GIGame();

	void Init(Camera sub, UINT* m_x, UINT* m_y, unsigned char* m_l, GameState* state, INT* total, INT type_num, INT tile_x, INT tile_y, INT time);
	void update();

	void PlayingGame();
	void LightOnLinkTile(_Tile* tile, UINT* count, TYPE type);
	void BreakLinkTile(_Tile** tile, TYPE type, UINT* count);
	void SortBlock();
	void ScoreUp(UINT count);

	bool IsOver();
	void GameOver(bool Clear);
};
