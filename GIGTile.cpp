#include "GameInGame.h"

_Tile::_Tile(){
	m_Image = CreateObject(0x00);
	vtx[0] = {{ 0.0f,  0.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.00f, 0.00f}};
	vtx[1] = {{30.0f,  0.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.33f, 0.00f}};
	vtx[2] = {{ 0.0f, 30.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.00f, 1.00f}};
	vtx[3] = {{30.0f, 30.0f, 0.0f, 1.0f},{},{1.0f, 1.0f, 1.0f, 1.0f},{0.33f, 1.00f}};
	SetVertex(m_Image, vtx, 4);
	_TEXT texture[1] = {};
	SetText(&(texture[0]), "Graphics\\Block.png");
	SetTexture(m_Image, texture, 1);
	m_near[0] = 0x00;
	m_near[1] = 0x00;
	m_near[2] = 0x00;
	m_near[3] = 0x00;

	m_Type = TYPE_PURPLE;
	m_on = false;
}

_Tile::~_Tile(){
	ReleaseObject(m_Image);
}


void _Tile::SetLight(bool b){
	m_on = b;
	if(b){
		vtx[0].diffuse = {0.5f,0.5f,0.5f,1.0f};
		vtx[1].diffuse = {0.5f,0.5f,0.5f,1.0f};
		vtx[2].diffuse = {0.5f,0.5f,0.5f,1.0f};
		vtx[3].diffuse = {0.5f,0.5f,0.5f,1.0f};
	}
	else{
		vtx[0].diffuse = {1.0f,1.0f,1.0f,1.0f};
		vtx[1].diffuse = {1.0f,1.0f,1.0f,1.0f};
		vtx[2].diffuse = {1.0f,1.0f,1.0f,1.0f};
		vtx[3].diffuse = {1.0f,1.0f,1.0f,1.0f};
	}
	SetVertex(m_Image, vtx, 4);
}
bool _Tile::IsLight(){return m_on;}

void _Tile::SetType(TYPE type){
	m_Type = type;
	switch(type){
	case TYPE_PURPLE:
		vtx[0].tex.x = 0.00f;
		vtx[1].tex.x = 0.33f;
		vtx[2].tex.x = 0.00f;
		vtx[3].tex.x = 0.33f;
		break;
	case TYPE_BLUE:
		vtx[0].tex.x = 0.33f;
		vtx[1].tex.x = 0.66f;
		vtx[2].tex.x = 0.33f;
		vtx[3].tex.x = 0.66f;
		break;
	case TYPE_YELLOW:
		vtx[0].tex.x = 0.66f;
		vtx[1].tex.x = 1.00f;
		vtx[2].tex.x = 0.66f;
		vtx[3].tex.x = 1.00f;
		break;
	}
	SetVertex(m_Image, vtx, 4);
}
TYPE _Tile::GetType(){return m_Type;}

void _Tile::SetNearTile(_Tile** top, _Tile** bottom, _Tile** left, _Tile** right){
	m_near[DIR_UP] = top;
	m_near[DIR_DOWN] = bottom;
	m_near[DIR_LEFT] = left;
	m_near[DIR_RIGHT] = right;
}
_Tile* _Tile::GetTile(DIR dir){
	if(m_near[dir] == 0x00){return 0x00;}
	return *(m_near[dir]);
}
_Tile** _Tile::GetTilePointer(DIR dir){
	return m_near[dir];
}

void _Tile::RegisterImage(Camera cam){
	RegisterObjectForCamera(cam,m_Image);
}
void _Tile::SetImagePosition(FLOAT x, FLOAT y){
	SetPosition(m_Image,x,-y,0.0f);
	SetWorldMatrix(m_Image);
}

_vector3 _Tile::GetImagePosition() const{
	return GetPosition(m_Image);
}