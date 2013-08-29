#ifndef UNICODE
#define UNICODE
#endif

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#define APP_NAME L"Learn to Program Windows"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
	// Register the window class. Unique thru our application
	const wchar_t CLASS_NAME[]  = L"kutsuu3D";

	// Null structure members
	WNDCLASSEX wc = {};

	// Assign windows procedure callback, instance and set class name for our window
	wc.cbSize        = sizeof(WNDCLASSEX);
	wc.lpfnWndProc   = WindowProc;
	wc.hInstance     = hInstance;
	wc.lpszClassName = CLASS_NAME;

	// Try to register our window class
	BOOL regClass;
	regClass = RegisterClassEx(&wc);
	if (!regClass) {
		// Maybe calling GetLastError to get details on the error
		return 0;
	}

	// Create the window.
	HWND hWnd = CreateWindowEx(
		0,                              // Optional window styles.
		CLASS_NAME,                     // Window class
		APP_NAME,    // Window text
		WS_OVERLAPPEDWINDOW,            // Window style
		// Size and position
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL,       // Parent window    
		NULL,       // Menu
		hInstance,  // Instance handle
		NULL        // Additional application data
	);

	// Terminate if window coudn't be created
	if (hWnd == NULL) {
		return 0;
	}

	// Otherwise visualize the created window
	ShowWindow(hWnd, nCmdShow);

	// Run the message loop and listen for user and system messages
	MSG msg = {};
	BOOL bRet;
	// Because GetMessage returns non zero value if message is not WM_QUIT, zero if it is WM_QUIT and -1 if an error occur.
	while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0) {
		// @Note so far we do not care of error handling
		if (bRet != -1) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	// OS does not care what we return to it
	return 0;
}

// Handles messages passed to our window by the OS (either user or os messages)
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
		case WM_DESTROY: { // Windows must be destroyed, program is terminated
			PostQuitMessage(0);
		}
		return 0;

		case WM_CLOSE: {
			int msgBoxId;
			if ((msgBoxId = MessageBox(hWnd, L"Quit?", APP_NAME, MB_OKCANCEL)) == IDOK) {
				DestroyWindow(hWnd);
			}
		}
		return 0;

		case WM_PAINT: { // OS will draw paint the window
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);

			FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));
			
			EndPaint(hWnd, &ps);
		}
		return 0;
	}

	// fallback to default windows procedure for all non catched cases
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}