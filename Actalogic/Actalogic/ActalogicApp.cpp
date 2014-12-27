#include "pch.h"
#include "ActalogicApp.h"

TCHAR ActalogicApp::m_szWindowClass[] = _T("Actalogic");
TCHAR ActalogicApp::m_szTitle[] = _T("Actalogic");

ActalogicApp::ActalogicApp():
m_hWnd(NULL),
m_hInstance(NULL),
m_d2d1Manager(),
m_entityFPS()
{
}


ActalogicApp::~ActalogicApp()
{
}

HRESULT ActalogicApp::Initialize(HINSTANCE hInstance, int nCmdShow)
{
	HRESULT hresult;

	hresult = m_d2d1Manager.CreateDeviceIndependentResources();
	if (FAILED(hresult)) {return hresult;}

	//TODO:ここにEntityのデバイス非依存の初期化処理を追加
	hresult = m_entityFPS.OnCreateDeviceIndependentResources();
	if (FAILED(hresult)) { return hresult; }

	m_hInstance = hInstance;
	m_hWnd = InitializeWindow(hInstance, nCmdShow, 640.0F, 480.0F);

	return m_hWnd==NULL ? E_FAIL : S_OK;
}

HWND ActalogicApp::InitializeWindow(HINSTANCE hInstance, int nCmdShow, FLOAT width, FLOAT height)
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

	FLOAT dpiX, dpiY;
	m_d2d1Manager.GetDesktopDpi(&dpiX, &dpiY);
	UINT desktopWidth = static_cast<UINT>(ceil(width * dpiX / 96.f));
	UINT desktopHeight = static_cast<UINT>(ceil(height * dpiY / 96.f));

	HWND hWnd = CreateWindow(
		m_szWindowClass,
		m_szTitle,
		WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT,
		desktopWidth, desktopHeight,
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

	SetClientSize(hWnd, desktopWidth, desktopHeight);

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
	for (;;)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) {
			if (!GetMessage(&msg, NULL, 0, 0))
			{
				return msg.wParam;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			if (m_isActive)
			{
				OnTick();
			}
			else
			{
				Sleep(1);
			}
		}
	}
}


///////////////////////////////////////////////////////////////////////////////

void ActalogicApp::OnTick()
{
	OnPreRender();
	OnRender();
	OnPostRender();
}

void ActalogicApp::OnPreRender()
{
	//TODO:ここに描画前の処理を追加
	m_entityFPS.OnPreRender();
}

void ActalogicApp::OnRender()
{
	HRESULT hresult = S_OK;

	hresult = m_d2d1Manager.CreateDeviceResources(m_hWnd);
	if (SUCCEEDED(hresult))
	{
		m_d2d1Manager.BeginDraw();

		//TODO:ここに描画処理を追加
		m_entityFPS.OnRender();

		hresult = m_d2d1Manager.EndDraw();
	}
	if (hresult == D2DERR_RECREATE_TARGET)
	{
		hresult = S_OK;
		m_d2d1Manager.DiscardDeviceResources();

		//TODO:ここにリソースの解放処理を追加
		m_entityFPS.OnDiscardDeviceResources();
	}
}

void ActalogicApp::OnPostRender()
{
	//TODO:ここに描画前の処理を追加
	m_entityFPS.OnPostRender();
}

void ActalogicApp::OnResize(WORD width, WORD height, BOOL isActive)
{
	m_isActive = isActive;
}

///////////////////////////////////////////////////////////////////////////////

LRESULT CALLBACK ActalogicApp::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_CREATE)
	{
		LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;
		ActalogicApp *pApp = (ActalogicApp *)pcs->lpCreateParams;

		SetWindowLongPtrW(hWnd, GWLP_USERDATA, PtrToUlong(pApp));
	}
	else
	{
		ActalogicApp *pApp = reinterpret_cast<ActalogicApp *>(static_cast<LONG_PTR>(
			::GetWindowLongPtrW(hWnd, GWLP_USERDATA)));

		switch (message)
		{
		case WM_DISPLAYCHANGE:
			InvalidateRect(hWnd, NULL, FALSE);
		case WM_PAINT:
			pApp->OnRender();
			ValidateRect(hWnd, NULL);
			break;
		case WM_SIZE:
		{
			BOOL isActive = wParam == SIZE_MINIMIZED ? FALSE : TRUE;
			WORD width = lParam & 0xFFFF;
			WORD height = (lParam >> 16) & 0xFFFF;
			pApp->OnResize(width, height, isActive);
			break;
		}
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
			break;
		}
	}

	return S_OK;
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