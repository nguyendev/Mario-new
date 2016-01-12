#include <windows.h>
#include "game.h"
#include "trace.h"
#include "Brick.h"

CGame::CGame(HINSTANCE hInstance, LPWSTR Name, int Mode, int IsFullScreen, int FrameRate)
{
	_d3d = NULL;
	_d3ddv = NULL;
	_BackBuffer = NULL;

	_Mode = Mode;
	_SetScreenDimension(Mode);
	_Name = Name;
	_IsFullScreen = IsFullScreen;
	_FrameRate = FrameRate;

	_hInstance = hInstance;
}

void CGame::_SetScreenDimension(int Mode)
{
	switch (Mode)
	{
	case GAME_SCREEN_RESOLUTION_640_480_24:
		_ScreenWidth = 640; 
		_ScreenHeight = 480;
		_Depth = 24;
		_BackBufferFormat = D3DFMT_X8R8G8B8;
		break;

	case GAME_SCREEN_RESOLUTION_800_600_24:
		_ScreenWidth = 800; 
		_ScreenHeight = 600;
		_Depth = 24;
		_BackBufferFormat = D3DFMT_X8R8G8B8;
		break;

	case GAME_SCREEN_RESOLUTION_1024_768_24:
		_ScreenWidth = 1024; 
		_ScreenHeight = 768;
		_Depth = 24;
		_BackBufferFormat = D3DFMT_X8R8G8B8;
		break;

	default: 
		break;
	}
}

void CGame::_InitWindow()
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = _hInstance;

	wc.lpfnWndProc = (WNDPROC)CGame::_WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "Game Mario";
	wc.hIconSm = NULL;
	
	RegisterClassEx(&wc);

	DWORD style; 
	if (_IsFullScreen)
		style = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP;
	else 
		style = WS_OVERLAPPEDWINDOW;

	_hWnd = 
		CreateWindow(
		"Game Mario",
		"Game Mario",
			style, 
			CW_USEDEFAULT,
			CW_USEDEFAULT, 
			_ScreenWidth,
			_ScreenHeight,
			NULL,
			NULL,
			_hInstance,
			NULL);
	
	if (!_hWnd) 
	{ 
		trace(L"[ERROR] Failed to created window!");
		DWORD ErrCode = GetLastError();
	}

	ShowWindow(_hWnd,SW_SHOWNORMAL);
	UpdateWindow(_hWnd);
}

void CGame::_InitDirectX()
{
	_d3d = Direct3DCreate9(D3D_SDK_VERSION);
	D3DPRESENT_PARAMETERS d3dpp; 

	ZeroMemory( &d3dpp, sizeof(d3dpp) );

	d3dpp.Windowed = _IsFullScreen?FALSE:TRUE;

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;

	d3dpp.BackBufferFormat = _BackBufferFormat; 
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferHeight = _ScreenHeight;
	d3dpp.BackBufferWidth = _ScreenWidth;

	_d3d->CreateDevice(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			_hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&_d3ddv);

	if (_d3ddv==NULL) 
	{
		
	}
	
	_d3ddv->GetBackBuffer(0,0,D3DBACKBUFFER_TYPE_MONO,&_BackBuffer);
}

void CGame::Init()
{
	_InitWindow();
	_InitDirectX();
	
	LoadResources(_d3ddv);
	_timeManager = new TimeManager();
}


// Main game message loop
void CGame::Run()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	trace(L">>> Main game loop has been started");
	_timeManager->LimitFPS(60);
	//Sleep(1000);
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			
			TPF = _timeManager->TPF;
			ProcessInput(_d3ddv, TPF);
			UpdateWorld(TPF);
			_RenderFrame();
		}
		
		
	}

	trace(L"Main game loop has ended");
}

void CGame::_RenderFrame()
{
	if (_d3ddv->BeginScene()) 
	{
		// Clear back buffer with BLACK
		_d3ddv->ColorFill(_BackBuffer,NULL,D3DCOLOR_XRGB(0xAA,0xAA,0xAA));
		RenderFrame(_d3ddv, TPF);
		_d3ddv->EndScene();
	}
	_d3ddv->Present(NULL,NULL,NULL,NULL);
}

void CGame::RenderFrame(LPDIRECT3DDEVICE9 d3ddv, float TPF)
{
	d3ddv->ColorFill(_BackBuffer,NULL,D3DCOLOR_XRGB(0,0,0));
}

void CGame::UpdateWorld(float TPF) { }

void CGame::LoadResources(LPDIRECT3DDEVICE9 d3ddv){}

void CGame::ProcessInput(LPDIRECT3DDEVICE9 d3ddv, float TPF) { }

CGame::~CGame()
{
	if (_d3ddv!=NULL) _d3ddv->Release();
	if (_d3d!=NULL) _d3d->Release();
}
LRESULT CALLBACK CGame::_WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) 
	{
		case WM_DESTROY: 
			PostQuitMessage(0);
			break;
		default: 
			return DefWindowProc(hWnd, message, wParam,lParam);
	}

	return 0;
}


