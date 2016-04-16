#include "Library Header\\Win32.h"
#include "Library Header\\GameSystem.h"

#include "Game.h"

#include <time.h>

#include <gl\\GL.h>
#pragma comment(lib, "OpenGL32.lib")

HDC g_hDC;
HGLRC g_hRC;

void GLInit() {
	PIXELFORMATDESCRIPTOR pfd =                             // 픽셀 포맷 설정 구조체
	{
		sizeof(PIXELFORMATDESCRIPTOR),                          // 사이즈
		1,                                                      // 버전 숫자
		PFD_DRAW_TO_WINDOW |                                    // 윈도우를 지원
		PFD_SUPPORT_OPENGL |                                    // GL을 지원
		PFD_DOUBLEBUFFER,                                       // 더블 버퍼링 사용
		PFD_TYPE_RGBA,                                          // RGBA 포맷 사용
		32,                                                     // 색상 비트 수
		0, 0, 0, 0, 0, 0,                                       // 컬러 비트 무시
		0,                                                      // 알파블렌딩 버퍼 사용하지 않음
		0,                                                      // Shift Bit 무시
		0,                                                      // Accumulation Buffer 사용하지 않음
		0, 0, 0, 0,                                             // Accumulation Bits 무시
		16,                                                     // 16Bit Z-Buffer 사용 
		0,                                                      // Stencil Buffer 사용하지 않음
		0,                                                      // Auxiliary Buffer 사용하지 않음
		PFD_MAIN_PLANE,                                         // 메인 드로잉 레이어
		0,                                                      // 무시
		0, 0, 0                                                 // Layer Masks 무시
	};

	g_hDC = GetDC(GetHWND());                                  // DC 획득
	unsigned int PixelFormat = ChoosePixelFormat(g_hDC, &pfd);        // pfd와 DC를 통해 픽셀포맷 설정
	SetPixelFormat(g_hDC, PixelFormat, &pfd);                 // PixelFormat값을 통해 픽셀포맷 설정
	
	g_hRC = wglCreateContext(g_hDC);                        // RC 획득
	wglMakeCurrent(g_hDC, g_hRC);                            // GL측에서 RC 지정
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