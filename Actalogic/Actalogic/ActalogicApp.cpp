#include "pch.h"
#include "ActalogicApp.h"

TCHAR ActalogicApp::m_szWindowClass[] = _T("Actalogic");
TCHAR ActalogicApp::m_szTitle[] = _T("Actalogic");

ActalogicApp::ActalogicApp():
m_hWnd(NULL),
m_hInstance(NULL)
{
}


ActalogicApp::~ActalogicApp()
{
}

HRESULT ActalogicApp::Initialize(HINSTANCE hInstance, int nCmdShow)
{
	HRESULT hresult;

	hresult = m_d2d1Manager.Initialize();
	if (FAILED(hresult))
	{
		return hresult;
	}

	m_hInstance = hInstance;
	m_hWnd = InitializeWindow(hInstance, nCmdShow, 640, 480);

	return m_hWnd==NULL ? E_FAIL : S_OK;
}

HWND ActalogicApp::InitializeWindow(HINSTANCE hInstance, int nCmdShow, LONG width, LONG height)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = ActalogicApp::WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = m_szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			m_szTitle,
			NULL);

		return NULL;
	}

	HWND hWnd = CreateWindow(
		m_szWindowClass,
		m_szTitle,
		WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT,
		width, height,
		NULL,
		NULL,
		hInstance,
		this
		);

	if (!hWnd)
	{
		MessageBox(NULL,
			_T("Call to CreateWindow failed!"),
			m_szTitle,
			NULL);

		return NULL;
	}

	SetClientSize(hWnd, width, height);

	if (nCmdShow == SW_MAXIMIZE)
	{
		ShowWindow(hWnd, SW_RESTORE);
	}
	else
	{
		ShowWindow(hWnd, nCmdShow);
	}

	UpdateWindow(hWnd);

	return hWnd;
}

int ActalogicApp::Run()
{
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

///////////////////////////////////////////////////////////////////////////////

LRESULT CALLBACK ActalogicApp::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}

VOID ActalogicApp::SetClientSize(HWND hWnd, LONG sx, LONG sy)
{
	RECT rc1;
	RECT rc2;

	GetWindowRect(hWnd, &rc1);
	GetClientRect(hWnd, &rc2);
	sx += ((rc1.right - rc1.left) - (rc2.right - rc2.left));
	sy += ((rc1.bottom - rc1.top) - (rc2.bottom - rc2.top));
	SetWindowPos(hWnd, NULL, 0, 0, sx, sy, (SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOMOVE));
}