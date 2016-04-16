#include "Game.h"

_GAME* _GAME::m_pSingleton = 0x00;

_GAME* _GAME::GetSingleton(){
	if(m_pSingleton == 0x00){
		m_pSingleton = new _GAME;
	}
	return m_pSingleton;
}

void _GAME::Destroy(){
	if(m_pSingleton != 0x00){
		delete m_pSingleton;
		m_pSingleton = 0x00;
	}
}

void game_update(){_GAME::GetSingleton()->update();}

_GAME::_GAME(){
	main = CreateObject(&game_update);
	RegisterUpdate(main);

	main_cam = CreateCamera();

	_vector2 size = {800,600};
	SetCameraSize(main_cam, size);
	SetEye(main_cam, {400.0f,300.0f,-1.0f});
	SetLookat(main_cam, {400.0f, 300.0f, 0.0f});
	SetViewMatrix(main_cam);
	SetPerspective(main_cam, size, 1.0f, 100.0f);
	SetPerspectiveProjMatrix(main_cam);
}
_GAME::~_GAME(){
	RemoveObjectForCamera(main_cam,main);
	ReleaseObject(main);
	ReleaseCameraUsePointer(main_cam);
}

void _GAME::Init(){
	title = CreateObject(0x00);
	_VERTEX vertex[] = {
		{{ 000.0f, 000.0f,0.0f,1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.0f,0.0f}},
		{{ 800.0f, 000.0f,0.0f,1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{1.0f,0.0f}},
		{{ 000.0f, 600.0f,0.0f,1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.0f,1.0f}},
		{{ 800.0f, 600.0f,0.0f,1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{1.0f,1.0f}}
	};
	_TEXT texture[1] = {};
	SetText(&(texture[0]),"Graphics\\title.png");
	SetVertex(title, vertex, 4);
	SetTexture(title, texture, 1);
	RegisterObjectForCamera(main_cam, title);

	mouse_x = 0; mouse_y = 0; LButton = 0;

	state = TITLE;
}

void _GAME::update(){
	POINT point ={0,0};
	GetCursorPos(&point);
	ScreenToClient(GetHWND(),&point);
	mouse_x = point.x; mouse_y = mouse_y = point.y;
	if(GetAsyncKeyState(VK_LBUTTON) & 8001){
		if(LButton & 0x80){LButton = 0x00;}
		else{LButton = 0x01;}
		LButton |= 0x80;
	}
	else{
		if(LButton & 0x80){LButton = 0x01;}
		else{LButton = 0x00;}
	}

	switch(state){
	case TITLE:
		if(LButton == 0x81){
			if(380 <= mouse_x && mouse_x <= 620 && 290 <= mouse_y && mouse_y <=340){//250*50
				game = new _GIMain;
				game->Init(main_cam, &state, &mouse_x, &mouse_y, &LButton);
				state = MAIN;
			}
			else if(410 <= mouse_x && mouse_x <= 660 && 350 <= mouse_y && mouse_y <=400){//250*50
				game = new _GIMain;
				game->Init(main_cam, &state, &mouse_x, &mouse_y, &LButton);
				game->Load();
				state = MAIN;
			}
			else if(450 <= mouse_x && mouse_x <= 700 && 410 <= mouse_y && mouse_y <=460){//250*50
				//state = OPTION;
			}
			else if(490 <= mouse_x && mouse_x <= 740 && 470 <= mouse_y && mouse_y <=520){//250*50
				PostQuitMessage(0);
			}
		}
		break;
	case MAIN: case SHOP: case PLAY:
		game->update();
		if(state == TITLE){
			delete game;
			game = 0x00;
		}
		break;
	}
}