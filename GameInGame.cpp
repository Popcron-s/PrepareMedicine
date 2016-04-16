#include "GameInGame.h"

_GIGame::_GIGame(){
	m_Tile = 0x00;
	m_Tile_x = 0;
	m_Tile_y = 0;
	m_Time = 0;
	m_Score = 0;

	m_TotalGold = 0;
	m_Mouse_x = 0;
	m_Mouse_y = 0;

	m_RefTime = 0;
	m_Over = false;
}
_GIGame::~_GIGame(){
	ReleaseObject(m_BG);
	ReleaseObject(m_Window[0]);
	ReleaseObject(m_Window[1]);
	ReleaseObject(m_Window[2]);
	ReleaseObject(m_Icon[0]);
	ReleaseObject(m_Icon[1]);
	ReleaseObject(m_ScoreCount[0]);
	ReleaseObject(m_ScoreCount[1]);
	ReleaseObject(m_ScoreCount[2]);
	ReleaseObject(m_ScoreCount[3]);
	ReleaseObject(m_ScoreCount[4]);
	ReleaseObject(m_ScoreCount[5]);
	ReleaseObject(m_ScoreCount[6]);
	ReleaseObject(m_ScoreCount[7]);
	ReleaseObject(m_TimeCount[0]);
	ReleaseObject(m_TimeCount[1]);
	ReleaseObject(m_TimeCount[2]);
	//ReleaseCameraUsePointer(sub_cam);
	if(m_Tile != 0x00){
		for(UINT i = 0; i<(m_Tile_x*m_Tile_y) ; ++i){
			delete m_Tile[i];
		}
		delete [] m_Tile;
		m_Tile = 0x00;
	}
}

void _GIGame::Init(Camera sub, UINT* m_x, UINT* m_y, unsigned char* m_l, GameState* state, INT* total, 
	INT type_num, INT tile_x, INT tile_y, INT time){
	sub_cam = sub;
	/*sub_cam = CreateCamera();

	_vector2 size = {800,600};
	SetCameraSize(sub_cam, size);
	SetCameraPosition(sub_cam, {-300,0});
	SetEye(sub_cam, {400.0f,300.0f,-1.0f});
	SetLookat(sub_cam, {400.0f, 300.0f, 0.0f});
	SetViewMatrix(sub_cam);
	SetPerspective(sub_cam, size, 1.0f, 100.0f);
	SetPerspectiveProjMatrix(sub_cam);*/

	m_BG = CreateObject(0x00);
	_VERTEX bg_vtx[4] = {
		{{  0.0f,   0.0f, 0.0f, 1.0f},{},{0.0f, 0.0f, 0.0f, 0.8f},{0.0f, 0.0f}},
		{{800.0f,   0.0f, 0.0f, 1.0f},{},{0.0f, 0.0f, 0.0f, 0.8f},{1.0f, 0.0f}},
		{{  0.0f, 600.0f, 0.0f, 1.0f},{},{0.0f, 0.0f, 0.0f, 0.8f},{0.0f, 1.0f}},
		{{800.0f, 600.0f, 0.0f, 1.0f},{},{0.0f, 0.0f, 0.0f, 0.8f},{1.0f, 1.0f}}
	};
	SetVertex(m_BG, bg_vtx, 4);
	RegisterObjectForCamera(sub_cam,m_BG);

	m_Window[0] = CreateObject(0x00);
	_VERTEX win_vtx1[22] = {
		{{ 95.0f,  30.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.000000f, 0.000000f}},
		{{ 95.0f,  35.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.000000f, 0.333333f}},
		{{100.0f,  30.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.333333f, 0.000000f}},
		{{100.0f,  35.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.333333f, 0.333333f}},
		{{470.0f,  30.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.666666f, 0.000000f}},
		{{470.0f,  35.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.666666f, 0.333333f}},
		{{475.0f,  30.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{1.000000f, 0.000000f}},

		{{475.0f,  35.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{1.000000f, 0.333333f}},

		{{475.0f,  95.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{1.000000f, 0.666666f}},
		{{470.0f,  35.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.666666f, 0.333333f}},
		{{470.0f,  95.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.666666f, 0.666666f}},
		{{100.0f,  35.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.333333f, 0.333333f}},
		{{100.0f,  95.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.333333f, 0.666666f}},
		{{ 95.0f,  35.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.000000f, 0.333333f}},

		{{ 95.0f,  95.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.000000f, 0.666666f}},

		{{ 95.0f, 100.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.000000f, 1.000000f}},
		{{100.0f,  95.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.333333f, 0.666666f}},
		{{100.0f, 100.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.333333f, 1.000000f}},
		{{470.0f,  95.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.666666f, 0.666666f}},
		{{470.0f, 100.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.666666f, 1.000000f}},
		{{475.0f,  95.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{1.000000f, 0.666666f}},
		{{475.0f, 100.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{1.000000f, 1.000000f}}
	};
	SetVertex(m_Window[0], win_vtx1, 22);
	_TEXT tex[1] = {};
	SetText(&(tex[0]), "Graphics\\Window.png");
	SetTexture(m_Window[0], tex, 1);
	RegisterObjectForCamera(sub_cam,m_Window[0]);
	//495 500 700 705
	m_Window[1] = CreateObject(0x00);
	_VERTEX win_vtx2[22] = {
		{{495.0f,  30.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.000000f, 0.000000f}},
		{{495.0f,  35.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.000000f, 0.333333f}},
		{{500.0f,  30.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.333333f, 0.000000f}},
		{{500.0f,  35.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.333333f, 0.333333f}},
		{{700.0f,  30.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.666666f, 0.000000f}},
		{{700.0f,  35.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.666666f, 0.333333f}},
		{{705.0f,  30.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{1.000000f, 0.000000f}},

		{{705.0f,  35.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{1.000000f, 0.333333f}},

		{{705.0f,  95.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{1.000000f, 0.666666f}},
		{{700.0f,  35.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.666666f, 0.333333f}},
		{{700.0f,  95.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.666666f, 0.666666f}},
		{{500.0f,  35.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.333333f, 0.333333f}},
		{{500.0f,  95.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.333333f, 0.666666f}},
		{{495.0f,  35.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.000000f, 0.333333f}},

		{{495.0f,  95.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.000000f, 0.666666f}},

		{{495.0f, 100.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.000000f, 1.000000f}},
		{{500.0f,  95.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.333333f, 0.666666f}},
		{{500.0f, 100.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.333333f, 1.000000f}},
		{{700.0f,  95.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.666666f, 0.666666f}},
		{{700.0f, 100.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.666666f, 1.000000f}},
		{{705.0f,  95.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{1.000000f, 0.666666f}},
		{{705.0f, 100.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{1.000000f, 1.000000f}}
	};
	SetVertex(m_Window[1], win_vtx2, 22);
	SetTexture(m_Window[1], tex, 1);
	RegisterObjectForCamera(sub_cam,m_Window[1]);

	m_Window[2] = CreateObject(0x00);
	SetTexture(m_Window[2], tex, 1);

	m_Icon[0] = CreateObject(0x00);
	_VERTEX ic_vtx1[4] = {
		{{105.0f,  40.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.0f, 0.0f}},
		{{155.0f,  40.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.5f, 0.0f}},
		{{105.0f,  90.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.0f, 1.0f}},
		{{155.0f,  90.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.5f, 1.0f}}
	};
	SetVertex(m_Icon[0], ic_vtx1, 4);
	_TEXT tex2[1] = {};
	SetText(&(tex2[0]), "Graphics\\Icon.png");
	SetTexture(m_Icon[0], tex2, 1);
	RegisterObjectForCamera(sub_cam,m_Icon[0]);

	m_Icon[1] = CreateObject(0x00);
	_VERTEX ic_vtx2[4] = {
		{{505.0f,  40.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.5f, 0.0f}},
		{{555.0f,  40.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{1.0f, 0.0f}},
		{{505.0f,  90.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.5f, 1.0f}},
		{{555.0f,  90.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{1.0f, 1.0f}}
	};
	SetVertex(m_Icon[1], ic_vtx2, 4);
	SetTexture(m_Icon[1], tex2, 1);
	RegisterObjectForCamera(sub_cam,m_Icon[1]);
	
	_TEXT tex3[1] = {};
	SetText(&(tex3[0]), "Graphics\\number.png");
	for(UINT i = 0 ; i<8 ; ++i){
		m_ScoreCount[i] = CreateObject(0x00);
		_VERTEX sc_vtx1[4] = {
			{{296.0f - (i*18.0f),  54.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.0f, 0.0f}},
			{{313.0f - (i*18.0f),  54.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.1f, 0.0f}},
			{{296.0f - (i*18.0f),  78.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.0f, 1.0f}},
			{{313.0f - (i*18.0f),  78.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.1f, 1.0f}}
		};
		SetVertex(m_ScoreCount[i], sc_vtx1, 4);
		SetTexture(m_ScoreCount[i], tex3, 1);
		RegisterObjectForCamera(sub_cam,m_ScoreCount[i]);
	}

	for(UINT i = 0 ; i<3 ; ++i){
		m_TimeCount[i] = CreateObject(0x00);
		_VERTEX tc_vtx1[4] = {
			{{610.0f - (i*18.0f),  54.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.0f, 0.0f}},
			{{627.0f - (i*18.0f),  54.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.1f, 0.0f}},
			{{610.0f - (i*18.0f),  78.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.0f, 1.0f}},
			{{627.0f - (i*18.0f),  78.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.1f, 1.0f}}
		};
		SetVertex(m_TimeCount[i], tc_vtx1, 4);
		SetTexture(m_TimeCount[i], tex3, 1);
		RegisterObjectForCamera(sub_cam,m_TimeCount[i]);
	}
	
	m_Mouse_x = m_x; m_Mouse_y = m_y; m_LButton = m_l; m_state = state;
	m_TotalGold = total;
	m_Time = time;
	SetTile(type_num, tile_x, tile_y);
	m_RefTime = GetTickCount();
	m_Over = false;
}

void _GIGame::SetTile(INT type_num, INT tile_x, INT tile_y){
	FLOAT x1 = (800-(tile_x*30))/2, y1 = 80.0f + ((520-(tile_y*30))/2);
	FLOAT x2 = x1 + (tile_x*30), y2 = y1 + (tile_y*30);
	_VERTEX win_vtx3[22] = {
		{{x1-5.0f, y1-5.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.000000f, 0.000000f}},
		{{x1-5.0f, y1     , 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.000000f, 0.333333f}},
		{{x1     , y1-5.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.333333f, 0.000000f}},
		{{x1     , y1     , 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.333333f, 0.333333f}},
		{{x2     , y1-5.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.666666f, 0.000000f}},
		{{x2     , y1     , 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.666666f, 0.333333f}},
		{{x2+5.0f, y1-5.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{1.000000f, 0.000000f}},

		{{x2+5.0f, y1     , 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{1.000000f, 0.333333f}},

		{{x2+5.0f, y2     , 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{1.000000f, 0.666666f}},
		{{x2     , y1     , 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.666666f, 0.333333f}},
		{{x2     , y2     , 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.666666f, 0.666666f}},
		{{x1     , y1     , 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.333333f, 0.333333f}},
		{{x1     , y2     , 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.333333f, 0.666666f}},
		{{x1-5.0f, y1     , 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.000000f, 0.333333f}},

		{{x1-5.0f, y2     , 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.000000f, 0.666666f}},

		{{x1-5.0f, y2+5.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.000000f, 1.000000f}},
		{{x1     , y2     , 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.333333f, 0.666666f}},
		{{x1     , y2+5.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.333333f, 1.000000f}},
		{{x2     , y2     , 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.666666f, 0.666666f}},
		{{x2     , y2+5.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.666666f, 1.000000f}},
		{{x2+5.0f, y2     , 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{1.000000f, 0.666666f}},
		{{x2+5.0f, y2+5.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{1.000000f, 1.000000f}}
	};
	SetVertex(m_Window[2], win_vtx3, 22);
	RegisterObjectForCamera(sub_cam,m_Window[2]);

	if(m_Tile != 0){
		for(UINT i = 0; i<(m_Tile_x*m_Tile_y) ; ++i){
			delete m_Tile[i];
		}
		delete [] m_Tile;
		m_Tile = 0x00;
		m_Tile_x = 0;
		m_Tile_y = 0;
	}
	m_Tile = new _Tile*[tile_x*tile_y];
	m_Tile_x = tile_x;
	m_Tile_y = tile_y;
	m_Col = m_Tile_x;
	for(UINT i = 0; i<(m_Tile_x*m_Tile_y) ; ++i){
		m_Tile[i] = new _Tile;
	}
	for(INT i = 0 ; i<(tile_x*tile_y) ; ++i){
		(*m_Tile[i]).SetLight(false);
		(*m_Tile[i]).SetType((TYPE)(rand()%type_num));
		INT x = i%tile_x;
		INT y = i/tile_x;
		(*m_Tile[i]).SetNearTile(
			((y > 0)?			&(m_Tile[i-tile_x]):0x00),
			((y < (tile_y-1))?	&(m_Tile[i+tile_x]):0x00),
			((x > 0)?			&(m_Tile[i-1]):0x00),
			((x < (tile_x-1))?	&(m_Tile[i+1]):0x00));
		(*m_Tile[i]).SetImagePosition(((800-(tile_x*30))/2) + (x*30),80 + ((520-(tile_y*30))/2) + (y*30));
		(*m_Tile[i]).RegisterImage(sub_cam);
	}
}

void _GIGame::update(){
	if(m_Over){
		char str[256];
		wsprintfA(str, "È¹µæ ÀÚ±Ý : %d\nÇöÀç ÀÚ±Ý : %d", m_Score, *m_TotalGold);
		::MessageBoxA(NULL, str, "°á°ú", MB_OK);
		*m_state = MAIN;
	}
	else{
		PlayingGame();
	}
	UINT t_score = m_Score;
	for(UINT i = 0 ; i<8 ; ++i){
		UINT t_num = t_score%10;
		_VERTEX sc_vtx1[4] = {
			{{296.0f - (i*18.0f),  54.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.0f+(0.1f*t_num), 0.0f}},
			{{313.0f - (i*18.0f),  54.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.1f+(0.1f*t_num), 0.0f}},
			{{296.0f - (i*18.0f),  78.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.0f+(0.1f*t_num), 1.0f}},
			{{313.0f - (i*18.0f),  78.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.1f+(0.1f*t_num), 1.0f}}
		};
		SetVertex(m_ScoreCount[i], sc_vtx1, 4);
		t_score /= 10;
	}
	
	UINT t_time = m_Time;
	for(UINT i = 0 ; i<3 ; ++i){
		UINT t_num = t_time%10;
		_VERTEX tc_vtx1[4] = {
			{{610.0f - (i*18.0f),  54.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.0f+(0.1f*t_num), 0.0f}},
			{{627.0f - (i*18.0f),  54.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.1f+(0.1f*t_num), 0.0f}},
			{{610.0f - (i*18.0f),  78.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.0f+(0.1f*t_num), 1.0f}},
			{{627.0f - (i*18.0f),  78.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.1f+(0.1f*t_num), 1.0f}}
		};
		SetVertex(m_TimeCount[i], tc_vtx1, 4);
		t_time /= 10;
	}
}

void _GIGame::PlayingGame(){
	INT last_t = GetTickCount();
	if((GetTickCount() - m_RefTime) > 1000){
		--m_Time;
		m_RefTime += 1000;
	}
	if(m_Time < 0){
		GameOver(false);
	}
	INT t_x = ((INT)*m_Mouse_x-((800 - (INT)(m_Tile_x*30))/2))/30;
	INT t_y = ((INT)*m_Mouse_y-(80+((520 - (INT)(m_Tile_y*30))/2)))/30; // (ÁÂÇ¥ - ±âÁØÁ¡)%30pixel

	if(*m_LButton & 0x80){
		if( 0 <= t_x && t_x < m_Tile_x && 
			0 <= t_y && t_y < m_Tile_y){
				UINT num = (t_y*m_Tile_x)+t_x;
				if(m_Tile[num] != 0x00){
					if((*m_Tile[num]).IsLight()){
						UINT count = 0;
						BreakLinkTile(&(m_Tile[num]), (m_Tile[num])->GetType(), &count);
						SortBlock();
						ScoreUp(count);
					}
					else{
						for(UINT i = 0 ; i<(m_Tile_x*m_Tile_y) ; ++i){
							if(m_Tile[i] != 0x00){(*m_Tile[i]).SetLight(false);}
						}
						UINT count = 1;
						TYPE type = (*m_Tile[num]).GetType();
						(*m_Tile[num]).SetLight(true);
						LightOnLinkTile(m_Tile[num], &count, type);
						if(count <= 1){
							(*m_Tile[num]).SetLight(false);
					}
				}
			}
		}
		else{
			for(UINT i = 0 ; i<(m_Tile_x*m_Tile_y) ; ++i){
				if(m_Tile[i] != 0x00){(*m_Tile[i]).SetLight(false);}
			}
		}
	}
	if(IsOver()){
		GameOver(true);
	}
}

void _GIGame::LightOnLinkTile(_Tile* tile, UINT* count, TYPE type){
	for(UINT i = 0 ; i<4 ; ++i){
		if(tile->GetTile((DIR)i) != 0x00){
			if(!tile->GetTile((DIR)i)->IsLight() && tile->GetTile((DIR)i)->GetType() == type){
				tile->GetTile((DIR)i)->SetLight(true); 
				++(*count);
				LightOnLinkTile(tile->GetTile((DIR)i), count, type);
			}
		}
	}
}

void _GIGame::BreakLinkTile(_Tile** tile, TYPE type, UINT* count){
	if(tile == 0x00){return;}
	if(*tile == 0x00){return;}
	_Tile** temp[4] = {
		(*tile)->GetTilePointer(DIR_UP),
		(*tile)->GetTilePointer(DIR_DOWN),
		(*tile)->GetTilePointer(DIR_LEFT),
		(*tile)->GetTilePointer(DIR_RIGHT)
	};
	if((*tile) != 0x00){
		if((*tile)->GetType() == type){
			_Effect::Create(sub_cam, (*tile)->GetImagePosition());
			delete (*tile);
			(*tile) = 0x00;
			++(*count);
			BreakLinkTile(temp[0],type, count);
			BreakLinkTile(temp[1],type, count);
			BreakLinkTile(temp[2],type, count);
			BreakLinkTile(temp[3],type, count);
		}
	}
}
void _GIGame::SortBlock(){
	for(INT i = (m_Tile_x*m_Tile_y)-1 ; i>=0 ; --i){
		if(m_Tile[i] != 0x00){
			INT t = i;
			while(m_Tile[t]->GetTile(DIR_DOWN) == 0x00 && (t+m_Tile_x)<(m_Tile_x*m_Tile_y)){
				m_Tile[t+m_Tile_x] = m_Tile[t];
				m_Tile[t] = 0x00;
				t += m_Tile_x;
				INT x = t%m_Tile_x, y = t/m_Tile_x;
				m_Tile[t]->SetNearTile(
					((y > 0)?			&(m_Tile[t-m_Tile_x]):0x00),
					((y < (m_Tile_y-1))?&(m_Tile[t+m_Tile_x]):0x00),
					((x > 0)?			&(m_Tile[t-1]):0x00),
					((x < (m_Tile_x-1))?&(m_Tile[t+1]):0x00));
				if(m_Tile[t] != 0x00){
					m_Tile[t]->SetImagePosition(((800-(m_Tile_x*30))/2) + (x*30),
						80 + ((520-(m_Tile_y*30))/2) + (y*30));
				}
			}
		}
	}
	INT x1 = -1, x2 = -1;
	for(INT x = (m_Tile_x-1) ; x>=0 ; --x){
		for(INT y = 0 ; y<m_Tile_y ; ++y){
			if(m_Tile[(y*m_Tile_x)+x] != 0x00){
				if(x1 != -1){x2 = x;}
				break;
			}
			else if(x1 == -1 && y == (m_Tile_y-1)){
				x1 = x;
			}
		}
		if(x1 != -1 && x2 != -1){
			for(INT y = 0 ; y<m_Tile_y ; ++y){
				m_Tile[(y*m_Tile_x)+x1] = m_Tile[(y*m_Tile_x)+x2];
				m_Tile[(y*m_Tile_x)+x2] = 0x00;
				INT temp = (y*m_Tile_x)+x1;
				if(m_Tile[temp] == 0x00){continue;}
				m_Tile[temp]->SetNearTile(
					((y > 0)?			&(m_Tile[temp-m_Tile_x]):0x00),
					((y < (m_Tile_y-1))?&(m_Tile[temp+m_Tile_x]):0x00),
					((x1 > 0)?			&(m_Tile[temp-1]):0x00),
					((x1 < (m_Tile_x-1))?&(m_Tile[temp+1]):0x00));
			}
			x = x1;
			x1 = -1;
			x2 = -1;
			for(INT y = 0 ; y<m_Tile_y ; ++y){
				if(m_Tile[(y*m_Tile_x)+x] != 0x00){
					m_Tile[(y*m_Tile_x)+x]->SetImagePosition(((800-(m_Tile_x*30))/2) + (x*30),
						80 + ((520-(m_Tile_y*30))/2) + (y*30));
				}
			}
		}
	}
}
void _GIGame::ScoreUp(UINT count){
	UINT unity_score = 10;
	UINT multiply = 1;

	unity_score += (count/3)*10;
	multiply += (count/8);

	UINT result = (count*unity_score)*multiply;
	m_Score += result;
}

bool _GIGame::IsOver(){
	for(UINT i = 0 ; i<(m_Tile_x*m_Tile_y) ; ++i){
		if(m_Tile[i] != 0x00){
			if(m_Tile[i]->GetTile(DIR_UP) != 0x00){
				if(m_Tile[i]->GetTile(DIR_UP)->GetType() == m_Tile[i]->GetType()){
					return false;
				}
			}
			if(m_Tile[i]->GetTile(DIR_DOWN) != 0x00){
				if(m_Tile[i]->GetTile(DIR_DOWN)->GetType() == m_Tile[i]->GetType()){
					return false;
				}
			}
			if(m_Tile[i]->GetTile(DIR_LEFT) != 0x00){
				if(m_Tile[i]->GetTile(DIR_LEFT)->GetType() == m_Tile[i]->GetType()){
					return false;
				}
			}
			if(m_Tile[i]->GetTile(DIR_DOWN) != 0x00){
				if(m_Tile[i]->GetTile(DIR_DOWN)->GetType() == m_Tile[i]->GetType()){
					return false;
				}
			}
		}
	}
	return true;
}
void _GIGame::GameOver(bool Clear){
	UINT count = 0;
	for(UINT i = 0 ; i<(m_Tile_x*m_Tile_y) ; ++i){
		if(m_Tile[i] != 0x00){++count;}
	}
	count = (count>=5)?1:(5-count);
	if(Clear){
		m_Score *= count;
	}
	else{
		m_Score *= 0.33;
	}
	*m_TotalGold += m_Score;
	m_Over = true;
}