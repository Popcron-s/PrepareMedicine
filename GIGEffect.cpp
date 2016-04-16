#include "GameInGame.h"

_Effect::list* _Effect::m_list = 0x00;
Object _Effect::main = 0x00;

void effect_update(){
	_Effect::list* t_list = _Effect::m_list;
	while(t_list != 0x00){
		if(t_list->_node->update()){
			_Effect::list* d_list = t_list;
			t_list = t_list->_next;
			_Effect::Destroy(d_list->_node);
		}
		else{
			t_list = t_list->_next;
		}
	}
}

_Effect::_Effect(Camera sub){
	m_Image = CreateObject(0x00);
	_VERTEX vtx[4] = {
		{{ 0.0f, 0.0f,0.0f},{},{1.0f,1.0f,1.0f,1.0f},{0.00f,0.0f}},
		{{40.0f, 0.0f,0.0f},{},{1.0f,1.0f,1.0f,1.0f},{0.25f,0.0f}},
		{{ 0.0f,40.0f,0.0f},{},{1.0f,1.0f,1.0f,1.0f},{0.00f,0.5f}},
		{{40.0f,40.0f,0.0f},{},{1.0f,1.0f,1.0f,1.0f},{0.25f,0.5f}}
	};
	SetVertex(m_Image,vtx,4);
	_TEXT tex[1] = {};
	SetText(&(tex[0]), "Graphics\\Effect.png");
	SetTexture(m_Image,tex,1);
	RegisterObjectForCamera(sub,m_Image);

	m_Frame = 0;
	m_RefTime = GetTickCount();
}

_Effect::~_Effect(){
	ReleaseObject(m_Image);
}

void _Effect::Create(Camera sub, _vector3 pos){
	list* t_list = new list;
	t_list->_node = new _Effect(sub);
	t_list->_node->SetPosition(pos);
	t_list->_next = m_list;
	if(m_list != 0x00){
		m_list->_prev = t_list;
	}
	t_list->_prev = 0x00;
	m_list = t_list;

	if(main == 0x00){
		main = CreateObject(effect_update);
		RegisterUpdate(main);
	}
}

void _Effect::Destroy(_Effect* obj){
	_Effect::list* t_list = _Effect::m_list;
	while(t_list != 0x00){
		if(t_list->_node == obj){
			if(m_list == t_list){
				m_list = t_list->_next;
			}
			if(t_list->_prev != 0x00){t_list->_prev->_next = t_list->_next;}
			if(t_list->_next != 0x00){t_list->_next->_prev = t_list->_prev;}
			delete t_list->_node;
			delete t_list;
			if(m_list == 0x00){
				RemoveUpdate(main);
				ReleaseObject(main);
				main = 0x00;
			}
			return;
		}
		t_list = t_list->_next;
	}
}

bool _Effect::update(){
	if((INT)(GetTickCount() - m_RefTime) > 50){
		++m_Frame;
		if(m_Frame >= 8){return true;}
		_VERTEX vtx[4] = {
			{{ 0.0f, 0.0f,0.0f},{},{1.0f,1.0f,1.0f,1.0f},{0.00f+(0.25f*(m_Frame%4)),0.0f+(0.5f*(m_Frame/4))}},
			{{40.0f, 0.0f,0.0f},{},{1.0f,1.0f,1.0f,1.0f},{0.25f+(0.25f*(m_Frame%4)),0.0f+(0.5f*(m_Frame/4))}},
			{{ 0.0f,40.0f,0.0f},{},{1.0f,1.0f,1.0f,1.0f},{0.00f+(0.25f*(m_Frame%4)),0.5f+(0.5f*(m_Frame/4))}},
			{{40.0f,40.0f,0.0f},{},{1.0f,1.0f,1.0f,1.0f},{0.25f+(0.25f*(m_Frame%4)),0.5f+(0.5f*(m_Frame/4))}}
		};
		SetVertex(m_Image,vtx,4);
		m_RefTime = GetTickCount();
	}
	return false;
}

void _Effect::SetPosition(_vector3 pos){
	::SetPosition(m_Image,pos.x-5.0f, pos.y+5.0f, pos.z);
	SetWorldMatrix(m_Image);
}