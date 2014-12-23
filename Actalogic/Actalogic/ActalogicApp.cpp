#include "pch.h"
#include "ActalogicApp.h"

TCHAR ActalogicApp::m_szWindowClass[] = _T("Actalogic");
TCHAR ActalogicApp::m_szTitle[] = _T("Actalogic");

ActalogicApp::ActalogicApp()
{
	m_hInstance = NULL;
	m_hWnd = NULL;
}


ActalogicApp::~ActalogicApp()
{
}

HRESULT ActalogicApp::Initialize(HINSTANCE hInstance, int nCmdShow)
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

		return 1;
	}

	m_hInstance = hInstance;

	m_hWnd = CreateWindow(
		m_szWindowClass,
		m_szTitle,
		WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT,
		640, 480,
		NULL,
		NULL,
		hInstance,
		this
		);

	if (!m_hWnd)
	{
		MessageBox(NULL,
			_T("Call to CreateWindow failed!"),
			m_szTitle,
			NULL);

		return 1;
	}

	SetClientSize(m_hWnd, 640, 480);

	if (nCmdShow == SW_MAXIMIZE)
	{
		ShowWindow(m_hWnd, SW_RESTORE);
	}
	else
	{
		ShowWindow(m_hWnd, nCmdShow);
	}

	UpdateWindow(m_hWnd);

	return 0;
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