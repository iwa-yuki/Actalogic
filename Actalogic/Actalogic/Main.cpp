#include "pch.h"
#include "ActalogicApp.h"

// �G���g���[�|�C���g
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

			theApp.Dispose();
		}
		CoUninitialize();
	}

	return 0;
}
