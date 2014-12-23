#include "pch.h"
#include "ActalogicApp.h"

// エントリーポイント
int WINAPI _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR lpCmdLine,
	int nCmdShow)
{
	if (SUCCEEDED(CoInitialize(NULL)))
	{
		{
			ActalogicApp theApp;

			if (SUCCEEDED(theApp.Initialize(hInstance, nCmdShow)))
			{
				theApp.Run();
			}
		}
		CoUninitialize();
	}

	return 0;
}
