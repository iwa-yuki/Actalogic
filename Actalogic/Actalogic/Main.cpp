#include "pch.h"
#include "ActalogicApp.h"

// �G���g���[�|�C���g
int WINAPI _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR lpCmdLine,
	int nCmdShow)
{
	ActalogicApp theApp;

	if (SUCCEEDED(theApp.Initialize(hInstance, nCmdShow)))
	{
		theApp.Run();
	}

	return 0;
}
