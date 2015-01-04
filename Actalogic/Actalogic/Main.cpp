#include "pch.h"
#include "ActalogicApp.h"

// エントリーポイント
int WINAPI _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR lpCmdLine,
	int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	if (SUCCEEDED(CoInitialize(NULL)))
	{
		{
			ActalogicApp theApp;

			if (SUCCEEDED(theApp.Initialize(hInstance, nCmdShow)))
			{
				theApp.Run();
			}

			theApp.Dispose();
		}
		CoUninitialize();
	}

	return 0;
}
