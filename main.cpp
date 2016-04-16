#include "Library Header\\Win32.h"
#include "Library Header\\GameSystem.h"

#include "Game.h"

#include <time.h>

#include <gl\\GL.h>
#pragma comment(lib, "OpenGL32.lib")

HDC g_hDC;
HGLRC g_hRC;

void GLInit() {
	PIXELFORMATDESCRIPTOR pfd =                             // �ȼ� ���� ���� ����ü
	{
		sizeof(PIXELFORMATDESCRIPTOR),                          // ������
		1,                                                      // ���� ����
		PFD_DRAW_TO_WINDOW |                                    // �����츦 ����
		PFD_SUPPORT_OPENGL |                                    // GL�� ����
		PFD_DOUBLEBUFFER,                                       // ���� ���۸� ���
		PFD_TYPE_RGBA,                                          // RGBA ���� ���
		32,                                                     // ���� ��Ʈ ��
		0, 0, 0, 0, 0, 0,                                       // �÷� ��Ʈ ����
		0,                                                      // ���ĺ��� ���� ������� ����
		0,                                                      // Shift Bit ����
		0,                                                      // Accumulation Buffer ������� ����
		0, 0, 0, 0,                                             // Accumulation Bits ����
		16,                                                     // 16Bit Z-Buffer ��� 
		0,                                                      // Stencil Buffer ������� ����
		0,                                                      // Auxiliary Buffer ������� ����
		PFD_MAIN_PLANE,                                         // ���� ����� ���̾�
		0,                                                      // ����
		0, 0, 0                                                 // Layer Masks ����
	};

	g_hDC = GetDC(GetHWND());                                  // DC ȹ��
	unsigned int PixelFormat = ChoosePixelFormat(g_hDC, &pfd);        // pfd�� DC�� ���� �ȼ����� ����
	SetPixelFormat(g_hDC, PixelFormat, &pfd);                 // PixelFormat���� ���� �ȼ����� ����
	
	g_hRC = wglCreateContext(g_hDC);                        // RC ȹ��
	wglMakeCurrent(g_hDC, g_hRC);                            // GL������ RC ����
}

void Loop() {
	update();
	SwapBuffers(g_hDC);
}

int WINAPI WinMain(HINSTANCE hThisInst, HINSTANCE hPrevInst, LPSTR lpszArgs, int nWinMode) {
	srand(time(NULL));
	SetBackBuffer(800, 600);
	WindowCreate(hThisInst, L"Prepare Medicine", &nWinMode, 800, 600);

	HWND hwnd = GetHWND();
	_GAME::GetSingleton()->Init();

	GLInit();
	MainLoop(Loop);
	Run();

	_GAME::Destroy();
}