#include "System.h"

namespace gdl {
	System::System(HINSTANCE hInstance, const wchar_t appName[]) {
		m_sAppName = appName;
		m_hInstance = hInstance;
	}

	System::~System() {

	}

	bool System::Initialize(int nCmdShow, const wchar_t className[]) {
		// Register the window class. Unique thru our application
		// Null structure members
		WNDCLASSEX wc = {};

		// Assign windows procedure callback, instance and set class name for our window
		wc.cbSize        = sizeof(WNDCLASSEX);
		wc.lpfnWndProc   = WindowProc;
		wc.hInstance     = m_hInstance;
		wc.lpszClassName = className;

		// Try to register our window class
		BOOL regClass;
		regClass = RegisterClassEx(&wc);
		if (!regClass) {
			// Maybe calling GetLastError to get details on the error
			return false;
		}

		// Create the window.
		HWND hWnd = CreateWindowEx(
			0,                              // Optional window styles.
			className,                     // Window class
			m_sAppName,   				// Window text
			WS_OVERLAPPEDWINDOW,            // Window style
			// Size and position
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
			NULL,       // Parent window    
			NULL,       // Menu
			m_hInstance,  // Instance handle
			this        // Additional application data
		);

		// Terminate if window coudn't be created
		if (hWnd == NULL) {
			return false;
		}

		// Otherwise visualize the created window
		ShowWindow(hWnd, nCmdShow);
		SetForegroundWindow(hWnd);
		SetFocus(hWnd);

		return true;
	}

	void System::Run() {
		// Run the message loop and listen for user and system messages
		// Because GetMessage() is blocking and we are going to initialize DirectX soon, we need something faster, PeekMessage() to the rescue
		MSG msg = {};
		BOOL bIsRunning = FALSE;
		while (!bIsRunning) {
			while (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE)) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);

				// If about quit time...
				if (msg.message == WM_QUIT) {
					bIsRunning = TRUE;
					break;
				}
			}
		}
	}

	void System::Shutdown() {

	}

	// Handles messages passed to our window by the OS (either user or os messages)
	LRESULT CALLBACK System::MessageProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		switch (uMsg) {
			case WM_DESTROY: { // Windows must be destroyed, program is terminated
				PostQuitMessage(0);
			}
			return 0;

			case WM_CLOSE: {
				int msgBoxId;
				if ((msgBoxId = MessageBox(hWnd, L"Quit?", L"...", MB_OKCANCEL)) == IDOK) {
					DestroyWindow(hWnd);
				}
			}
			return 0;

			case WM_PAINT: { // OS will draw paint the window
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(hWnd, &ps);

				FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));
			
				TextOut(hdc, 10, 10, L"Hallo!", 6);

				EndPaint(hWnd, &ps);
			}
			return 0;
		}

		// fallback to default windows procedure for all non catched cases
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	// Handle windows creation and pass any other events to MessageProc
	LRESULT CALLBACK System::WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		System *pSys = NULL;
		if (uMsg == WM_CREATE) {
			CREATESTRUCT *pStruct = (CREATESTRUCT *)lParam;
			pSys = (System *)pStruct->lpCreateParams;
			SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pSys);
			pSys->m_hWnd = hWnd;
		} else {
			pSys = (System *)GetWindowLongPtr(hWnd, GWLP_USERDATA);
		}

		if (pSys) {
			return pSys->MessageProc(hWnd, uMsg, wParam, lParam);
		} else {
			return DefWindowProc(hWnd, uMsg, wParam, lParam); 
		}
	}
}