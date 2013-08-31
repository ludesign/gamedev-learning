#ifndef UNICODE
#define UNICODE
#endif

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "System.h"

#define APP_NAME L"Learn to Program Windows"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {

	gdl::System *sys = new gdl::System(hInstance, L"App Title");
	if (sys->Initialize(nCmdShow, L"kutsuu")) {
		sys->Run();
	}
	sys->Shutdown();

	// OS does not care what we return to it but let's follow the convention and return the exit code given by WM_QUIT
	// return static_cast<int>(msg.wParam);
	return 0;
}

