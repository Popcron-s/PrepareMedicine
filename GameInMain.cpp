#include "GameInMain.h"

_GIMain::_GIMain(){

}
_GIMain::~_GIMain(){
	ReleaseObject(main);
	ReleaseObject(main_menu);
	ReleaseObject(Item[0]);
	ReleaseObject(Item[1]);
	ReleaseObject(Item[2]);
	for(INT i = 0 ; i<9 ; ++i){
		ReleaseObject(Number[i]);
	}
	ReleaseObject(ShopWindow);
	//ReleaseCameraUsePointer(sub_cam);
}

void _GIMain::Init(Camera sub, GameState* state, UINT* mouse_x, UINT* mouse_y, unsigned char* LButton){
	m_Gold = 0;
	m_Item[0] = 0;
	m_Item[1] = 0;
	m_Item[2] = 0;

	m_state = state;
	m_Mouse_x = mouse_x;
	m_Mouse_y = mouse_y;
	m_LButton = LButton;

	sub_cam = sub;
	/*
	sub_cam = CreateCamera();

	_vector2 size = {800,600};
	SetCameraSize(sub_cam, size);
	SetEye(sub_cam, {400.0f,300.0f,-1.0f});
	SetLookat(sub_cam, {400.0f, 300.0f, 0.0f});
	SetViewMatrix(sub_cam);
	SetPerspective(sub_cam, size, 1.0f, 100.0f);
	SetPerspectiveProjMatrix(sub_cam);
	*/
	_VERTEX global_vtx[4] = {
		{{  0.0f,   0.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.0f, 0.0f}},
		{{800.0f,   0.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{1.0f, 0.0f}},
		{{  0.0f, 600.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.0f, 1.0f}},
		{{800.0f, 600.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{1.0f, 1.0f}}
	};

	main = CreateObject(0x00);
	SetVertex(main, global_vtx, 4);
	_TEXT tex1[1] = {};
	SetText(&(tex1[0]), "Graphics\\main.png");
	SetTexture(main, tex1, 1);
	RegisterObjectForCamera(sub_cam,main);

	main_menu = CreateObject(0x00);
	SetVertex(main_menu, global_vtx, 4);
	_TEXT tex7[1] = {};
	SetText(&(tex7[0]), "Graphics\\main_menu.png");
	SetTexture(main_menu, tex7, 1);
	RegisterObjectForCamera(sub_cam,main_menu);

	Item[0] = CreateObject(0x00);
	SetVertex(Item[0], global_vtx, 4);
	_TEXT tex2[1] = {};
	SetText(&(tex2[0]), "Graphics\\item_1.png");
	SetTexture(Item[0], tex2, 1);
	//RegisterObjectForCamera(sub_cam,Item[0]);

	Item[1] = CreateObject(0x00);
	SetVertex(Item[1], global_vtx, 4);
	_TEXT tex3[1] = {};
	SetText(&(tex3[0]), "Graphics\\item_2.png");
	SetTexture(Item[1], tex3, 1);
	//RegisterObjectForCamera(sub_cam,Item[1]);

	Item[2] = CreateObject(0x00);
	SetVertex(Item[2], global_vtx, 4);
	_TEXT tex4[1] = {};
	SetText(&(tex4[0]), "Graphics\\item_3.png");
	SetTexture(Item[2], tex4, 1);
	//RegisterObjectForCamera(sub_cam,Item[2]);

	_TEXT tex5[1] = {};
	SetText(&(tex5[0]), "Graphics\\Number.png");
	for(INT i = 0 ; i<9 ; ++i){
		Number[i] = CreateObject(0x00);
		_VERTEX num_vtx[4] = {//430 74
			{{412.0f - (i*18.0f),  64.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.0f, 0.0f}},
			{{430.0f - (i*18.0f),  64.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.1f, 0.0f}},
			{{412.0f - (i*18.0f),  88.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.0f, 1.0f}},
			{{430.0f - (i*18.0f),  88.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.1f, 1.0f}}
		};
		SetVertex(Number[i], num_vtx, 4);
		SetTexture(Number[i], tex5, 1);
		RegisterObjectForCamera(sub_cam,Number[i]);
	}

	ShopWindow = CreateObject(0x00);
	_VERTEX sw_vtx[4] = {
		{{100.0f,  50.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.0f, 0.0f}},
		{{700.0f,  50.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{1.0f, 0.0f}},
		{{100.0f, 550.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.0f, 1.0f}},
		{{700.0f, 550.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{1.0f, 1.0f}}
	};

	SetVertex(ShopWindow, sw_vtx, 4);
	_TEXT tex6[1] = {};
	SetText(&(tex6[0]), "Graphics\\store.png");
	SetTexture(ShopWindow, tex6, 1);
	//RegisterObjectForCamera(sub_cam,ShopWindow);
	m_Game = 0x00;
}
void _GIMain::update(){
	switch(*m_state){
	case MAIN:
		if(*m_LButton == 0x81){
			if(60 <= *m_Mouse_x && *m_Mouse_x <= 260 && 150 <= *m_Mouse_y && *m_Mouse_y <= 200){
				m_Game = new _GIGame;
				UINT x = 0,y = 0,type = 0,time = 0;
				x = 9 + (3*m_Item[0]) + (3*m_Item[2]);
				y = 6 + (2*m_Item[1]) + (2*m_Item[2]);
				type = 3;
				time = 100 + (10*m_Item[0]) + (10*m_Item[1]);
				m_Game->Init(sub_cam, m_Mouse_x, m_Mouse_y, m_LButton, m_state, &m_Gold, type, x, y, time);
				*m_state = PLAY;
			}
			else if(60 <= *m_Mouse_x && *m_Mouse_x <= 260 && 210 <= *m_Mouse_y && *m_Mouse_y <= 260){
				RegisterObjectForCamera(sub_cam,ShopWindow);
				*m_state = SHOP;
			}
			else if(60 <= *m_Mouse_x && *m_Mouse_x <= 260 && 270 <= *m_Mouse_y && *m_Mouse_y <= 320){
				if(Save()){::MessageBoxA(NULL,"SAVE GAME","SAVE",MB_OK);}
				else{::MessageBoxA(NULL,"Failed Save","SAVE",MB_OK);}
			}
			else if(60 <= *m_Mouse_x && *m_Mouse_x <= 260 && 330 <= *m_Mouse_y && *m_Mouse_y <= 380){
				if(Load()){::MessageBoxA(NULL,"LOAD GAME","LOAD",MB_OK);}
				else{::MessageBoxA(NULL,"Failed load","LOAD",MB_OK);}
			}
			else if(60 <= *m_Mouse_x && *m_Mouse_x <= 260 && 390 <= *m_Mouse_y && *m_Mouse_y <= 430){
				//option
			}
			else if(60 <= *m_Mouse_x && *m_Mouse_x <= 260 && 440 <= *m_Mouse_y && *m_Mouse_y <= 490){
				*m_state = TITLE;
			}
		}
		break;
	case SHOP:
		Shop();
		if(*m_state == MAIN){
			RemoveObjectForCamera(sub_cam,ShopWindow);
		}
		break;
	case PLAY:
		m_Game->update();
		if(*m_state == MAIN){
			delete m_Game;
		}
		break;
	}
	UINT t_gold = m_Gold;
	for(INT i = 0 ; i<9 ; ++i){
		UINT t = t_gold%10;
		_VERTEX num_vtx[4] = {//430 74
			{{412.0f - (i*18.0f),  64.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.0f + (t*0.1f), 0.0f}},
			{{430.0f - (i*18.0f),  64.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.1f + (t*0.1f), 0.0f}},
			{{412.0f - (i*18.0f),  88.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.0f + (t*0.1f), 1.0f}},
			{{430.0f - (i*18.0f),  88.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.1f + (t*0.1f), 1.0f}}
		};
		SetVertex(Number[i], num_vtx, 4);
		t_gold /= 10;
	}
}

void _GIMain::ShopInit(){

}

void _GIMain::Shop(){
	if(*m_LButton == 0x81){
		if(152 <= *m_Mouse_x && *m_Mouse_x <= 277 && 440 <= *m_Mouse_y && *m_Mouse_y <= 476){
			if(m_Item[0] == 0 && m_Gold >= 20000){
				m_Item[0] = 1;
				m_Gold -= 20000;
				::MessageBoxA(NULL,"실험정신 세트를 구입하였습니다.","구입 성공",MB_OK);
				RegisterObjectForCamera(sub_cam,Item[0]);
				RemoveObjectForCamera(sub_cam,main_menu);
				RemoveObjectForCamera(sub_cam,ShopWindow);
				RegisterObjectForCamera(sub_cam,main_menu);
				RegisterObjectForCamera(sub_cam,ShopWindow);
			}
			else if(m_Item[0] != 0){
				::MessageBoxA(NULL,"실험정신 세트는 이미 구매하신 상품입니다.","구입 실패",MB_OK);
			}
			else{
				::MessageBoxA(NULL,"돈이 부족합니다.","구입 실패",MB_OK);
			}
		}
		else if(340 <= *m_Mouse_x && *m_Mouse_x <= 460 && 440 <= *m_Mouse_y && *m_Mouse_y <= 476){
			if(m_Item[1] == 0 && m_Gold >= 20000){
				m_Item[1] += 1;
				m_Gold -= 20000;
				::MessageBoxA(NULL,"해피아워 세트를 구입하였습니다.","구입 성공",MB_OK);
				RegisterObjectForCamera(sub_cam,Item[1]);
				RemoveObjectForCamera(sub_cam,main_menu);
				RemoveObjectForCamera(sub_cam,ShopWindow);
				RegisterObjectForCamera(sub_cam,main_menu);
				RegisterObjectForCamera(sub_cam,ShopWindow);
			}
			else if(m_Item[1] != 0){
				::MessageBoxA(NULL,"해피아워 세트는 이미 구매하신 상품입니다.","구입 실패",MB_OK);
			}
			else{
				::MessageBoxA(NULL,"돈이 부족합니다.","구입 실패",MB_OK);
			}
		}
		else if(526 <= *m_Mouse_x && *m_Mouse_x <= 646 && 440 <= *m_Mouse_y && *m_Mouse_y <= 476){
			if(m_Item[2] == 0 && m_Gold >= 80000){
				m_Item[2] += 1;
				m_Gold -= 80000;
				::MessageBoxA(NULL,"노벨화학상 세트를 구입하였습니다.","구입 성공",MB_OK);
				RegisterObjectForCamera(sub_cam,Item[2]);
				RemoveObjectForCamera(sub_cam,main_menu);
				RemoveObjectForCamera(sub_cam,ShopWindow);
				RegisterObjectForCamera(sub_cam,main_menu);
				RegisterObjectForCamera(sub_cam,ShopWindow);
			}
			else if(m_Item[2] != 0){
				::MessageBoxA(NULL,"노벨화학상 세트는 이미 구매하신 상품입니다.","구입 실패",MB_OK);
			}
			else{
				::MessageBoxA(NULL,"돈이 부족합니다.","구입 실패",MB_OK);
			}
		}
		else if(372 <= *m_Mouse_x && *m_Mouse_x <= 426 && 512 <= *m_Mouse_y && *m_Mouse_y <= 542){
			*m_state = MAIN;
		}
	}
}

bool _GIMain::Save(){
	FILE* file;
	fopen_s(&file, "SaveFile.sav", "wb");
	if(file == NULL){return false;}
	fwrite(&m_Gold, sizeof(INT), 1, file);
	fwrite(m_Item, sizeof(unsigned char), 3, file);
	fclose(file);
	return true;
}

bool _GIMain::Load(){
	FILE* file;
	fopen_s(&file, "SaveFile.sav", "rb");
	if(file == NULL){return false;}
	if(m_Item[0] != 0){RemoveObjectForCamera(sub_cam,Item[0]);}
	if(m_Item[1] != 0){RemoveObjectForCamera(sub_cam,Item[1]);}
	if(m_Item[2] != 0){RemoveObjectForCamera(sub_cam,Item[2]);}
	RemoveObjectForCamera(sub_cam,main_menu);
	fread(&m_Gold, sizeof(INT), 1, file);
	fread(m_Item, sizeof(unsigned char), 3, file);
	fclose(file);
	if(m_Item[0] != 0){RegisterObjectForCamera(sub_cam,Item[0]);}
	if(m_Item[1] != 0){RegisterObjectForCamera(sub_cam,Item[1]);}
	if(m_Item[2] != 0){RegisterObjectForCamera(sub_cam,Item[2]);}
	RegisterObjectForCamera(sub_cam,main_menu);
	return true;
}