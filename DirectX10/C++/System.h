#include <windows.h>

namespace gdl {
	class System {
	public:
		System(HINSTANCE, const wchar_t []);
		~System();
		bool Initialize(int nCmdShow, const wchar_t []);
		void Run();
		void Shutdown();

		static LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

	private:
		HWND m_hWnd;
		HINSTANCE m_hInstance;
		const wchar_t *m_sAppName;
		bool m_bClassRegistered;
	};
}