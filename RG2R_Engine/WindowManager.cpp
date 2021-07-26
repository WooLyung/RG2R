#include "stdafx.h"
#include "WindowManager.h"
#include "Engine.h"
#include "Resource.h"
#include "Settings.h"

WindowManager::WindowManager()
	:isFullscreen_(WINDOW_START_FULLSCREEN), // 설정된 값으로 설정
	isResizable_(WINDOW_RESIZABLE), // 설정된 값으로 설정
	msg_{ 0, }, // 메세지를 [ 0, ~ ] 로 설정
	savedRect_{ 0,0,(LONG)WINDOW_DEFAULT_WIDTH, (LONG)WINDOW_DEFAULT_HEIGHT }, // 사각형 설정?
	cStrBuffer_{ 0, } // 글자 관련
{
	WNDCLASSEXA wc = { 0, }; // 윈도우 클래스, 초기값 모두 0으로
	HINSTANCE hInstance = GetModuleHandleA(nullptr); // 윈도우 객체 받아옴
	wc.hIcon = LoadIconA(hInstance, MAKEINTRESOURCEA(IDC_RG2RENGINE)); // 아이콘 설정
	wc.hIconSm = LoadIconA(hInstance, MAKEINTRESOURCEA(IDI_SMALL)); // 작은 아이콘 설정
	wc.cbSize = sizeof(WNDCLASSEXA); // 구조체 크기
	wc.hInstance = hInstance; // 윈도우 객체 설정
	wc.lpszClassName = GAME_TITLE;
	wc.style = CS_CLASSDC; // 출력 형태
	wc.lpfnWndProc = &WindowManager::WndProc; // 프로시저 함수, 메세지 처리용

	// 윈도우 클래스를 운영체제에 등록
	RegisterClassExA(&wc);

	int wx, wy;
	RECT rcWindow = { 0, };
	DWORD style, exstyle;

	if (isFullscreen_)
	{
		wx = wy = 0L;
		rcWindow.right = GetSystemMetrics(SM_CXSCREEN);
		rcWindow.bottom = GetSystemMetrics(SM_CYSCREEN);
		style = WS_SYSMENU | WS_POPUP; // 스타일 설정 (전체화면용)
		exstyle = NULL;
	}
	else
	{
		// GetSystemMetrics(SM_CXSCREEN) : 현재 화면의 해상도를 받아옴

		wx = (GetSystemMetrics(SM_CXSCREEN) - WINDOW_DEFAULT_WIDTH) / 2;
		wy = (GetSystemMetrics(SM_CYSCREEN) - WINDOW_DEFAULT_HEIGHT) / 2;
		rcWindow.right = WINDOW_DEFAULT_WIDTH;
		rcWindow.bottom = WINDOW_DEFAULT_HEIGHT;
		style = (WS_MINIMIZEBOX * WINDOW_EXIST_MINIMIZEBOX) | (WS_MAXIMIZEBOX * WINDOW_EXIST_MAXIMIZEBOX) | (WS_SYSMENU * WINDOW_EXIST_CLOSEBOX) | WS_CAPTION | (WINDOW_RESIZABLE * WS_THICKFRAME); // 스타일 설정 (창모드용)
		exstyle = NULL;
	}

	AdjustWindowRectEx(&rcWindow, style, false, exstyle); // 작업영역 크기에 맞춰 크기를 설정

	// 윈도우를 생성
	hwnd_ = CreateWindowExA(
		exstyle, // 확장된 스타일
		GAME_TITLE, // 등록된 윈도우 클래스 이름
		GAME_TITLE, // 윈도우 캡션 이름
		style, // 윈도우 스타일
		wx, // 윈도우 좌측 상단의 x좌표
		wy, // 윈도우 좌측 상단의 y좌표
		rcWindow.right - rcWindow.left, // 윈도우 폭
		rcWindow.bottom - rcWindow.top, // 윈도우 높이
		NULL, // 부모 윈도우의 핸들
		NULL, // 메뉴 또는 자식 윈도우 식별자
		wc.hInstance, // 윈도우를 생성한 인스턴스 핸들
		NULL); // CREATESTRUCT 구조체를 통해 전달되는 값

	// SavedRect가 초기값이 fullscreen일때도 설정되게 수정함
	AdjustWindowRectEx(&savedRect_, WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU | WS_CAPTION, false, NULL);

	// 윈도우 출력
	ShowWindow(hwnd_, SW_SHOWNORMAL);
}


WindowManager::~WindowManager()
{
}

void WindowManager::SetTitle(const std::string& title) // 타이틀 설정
{
	SetWindowTextA(hwnd_, title.c_str());
}

void WindowManager::SetPos(const Point2L& pos) // 윈도우 위치 설정
{
	SetWindowPos(hwnd_, NULL, pos.x, pos.y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
}

void WindowManager::SetSize(const Size2U& size) // 윈도우 크기 설정
{
	//client 기준으로 설정하도록 수정함
	RECT tmp = { 0, 0, (LONG)size.width, (LONG)size.height };
	savedRect_ = tmp;
	SetWindowPos(hwnd_, HWND_NOTOPMOST, savedRect_.left, savedRect_.top, savedRect_.right - savedRect_.left, savedRect_.bottom - savedRect_.top, SWP_FRAMECHANGED | SWP_SHOWWINDOW);
}

void WindowManager::SetFullscreen(bool flag) // 풀스크린 설정
{
	//변경하려는 상태가 현재상태와 같으면 아무일도 하지않음
	if (flag == isFullscreen_) return;

	isFullscreen_ = flag;
	if (flag)
	{
		GetWindowRect(hwnd_, &savedRect_);
		SetWindowLongA(hwnd_, GWL_STYLE, WS_SYSMENU | WS_POPUP);
		SetWindowPos(hwnd_, HWND_TOPMOST, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), SWP_FRAMECHANGED | SWP_SHOWWINDOW);
	}
	else
	{
		SetWindowLongA(hwnd_, GWL_STYLE, WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU | WS_CAPTION | (isResizable_ ? WS_THICKFRAME : 0));
		SetWindowPos(hwnd_, HWND_NOTOPMOST, savedRect_.left, savedRect_.top, savedRect_.right - savedRect_.left, savedRect_.bottom - savedRect_.top, SWP_FRAMECHANGED | SWP_SHOWWINDOW);
	}
}

void WindowManager::SetResizable(bool flag)
{
	isResizable_ = flag;
	SetWindowLongA(hwnd_, GWL_STYLE, flag ?
		GetWindowLongA(hwnd_, GWL_STYLE) | WS_THICKFRAME :
		GetWindowLongA(hwnd_, GWL_STYLE) & ~WS_THICKFRAME);
}

void WindowManager::SetMaximizable(bool flag)
{
	SetWindowLongA(hwnd_, GWL_STYLE, flag ?
		GetWindowLongA(hwnd_, GWL_STYLE) | WS_MAXIMIZEBOX :
		GetWindowLongA(hwnd_, GWL_STYLE) & ~WS_MAXIMIZEBOX);
}

void WindowManager::ToggleFullscreen()
{
	SetFullscreen(!isFullscreen_);
}

HWND WindowManager::GetHwnd()
{
	return hwnd_;
}

std::string WindowManager::GetTitle()
{
	cStrBuffer_[GetWindowTextA(hwnd_, cStrBuffer_, C_STR_BUFFER_SIZE)] = '\0';
	return cStrBuffer_;
}

Point2L WindowManager::GetPos()
{
	RECT rc;
	GetWindowRect(hwnd_, &rc);
	return Point2L(rc.left, rc.top);
}

Size2U WindowManager::GetSize()
{
	RECT rc;
	GetClientRect(hwnd_, &rc);
	return Size2U((UINT32)rc.right, (UINT32)rc.bottom);
}

void WindowManager::Close()
{
	SendMessage(hwnd_, WM_CLOSE, 0, 0);
}

void WindowManager::Minimize()
{
	ShowWindow(hwnd_, SW_SHOWMINIMIZED);
}

void WindowManager::Maximize()
{
	ShowWindow(hwnd_, SW_SHOWMAXIMIZED);
}

void WindowManager::Focus()
{
	SetFocus(hwnd_);
}

void WindowManager::Foreground()
{
	SetForegroundWindow(hwnd_);
}

void WindowManager::Activate()
{
	SetActiveWindow(hwnd_);
}

bool WindowManager::IsFullscreen()
{
	return isFullscreen_;
}

bool WindowManager::MsgLoop()
{
	if (PeekMessageA(&msg_, NULL, 0U, 0U, PM_REMOVE))
	{
		DispatchMessageA(&msg_);
		return false;
	}
	return true;
}

LRESULT WindowManager::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProcA(hwnd, msg, wParam, lParam);
}

bool WindowManager::IsRunning()
{
	return !(msg_.message == WM_QUIT);
}

bool WindowManager::IsResizable()
{
	return GetWindowLongA(hwnd_, GWL_STYLE) & WS_THICKFRAME ? true : false;
}

bool WindowManager::IsMaximizable()
{
	return GetWindowLongA(hwnd_, GWL_STYLE) & WS_MAXIMIZEBOX ? true : false;
}

bool WindowManager::IsMinimized()
{
	return IsIconic(hwnd_);
}

bool WindowManager::IsMaximized()
{
	return IsZoomed(hwnd_);
}

bool WindowManager::IsFocused()
{
	return GetFocus() == hwnd_;
}

bool WindowManager::IsActive()
{
	return GetActiveWindow() == hwnd_;
}
