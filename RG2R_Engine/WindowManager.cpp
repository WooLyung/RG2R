#include "stdafx.h"
#include "WindowManager.h"
#include "Engine.h"
#include "Resource.h"
#include "Settings.h"

WindowManager::WindowManager()
	:isFullscreen_(WINDOW_START_FULLSCREEN), // ������ ������ ����
	isResizable_(WINDOW_RESIZABLE), // ������ ������ ����
	msg_{ 0, }, // �޼����� [ 0, ~ ] �� ����
	savedRect_{ 0,0,(LONG)WINDOW_DEFAULT_WIDTH, (LONG)WINDOW_DEFAULT_HEIGHT }, // �簢�� ����?
	cStrBuffer_{ 0, } // ���� ����
{
	WNDCLASSEXA wc = { 0, }; // ������ Ŭ����, �ʱⰪ ��� 0����
	HINSTANCE hInstance = GetModuleHandleA(nullptr); // ������ ��ü �޾ƿ�
	wc.hIcon = LoadIconA(hInstance, MAKEINTRESOURCEA(IDC_RG2RENGINE)); // ������ ����
	wc.hIconSm = LoadIconA(hInstance, MAKEINTRESOURCEA(IDI_SMALL)); // ���� ������ ����
	wc.cbSize = sizeof(WNDCLASSEXA); // ����ü ũ��
	wc.hInstance = hInstance; // ������ ��ü ����
	wc.lpszClassName = GAME_TITLE;
	wc.style = CS_CLASSDC; // ��� ����
	wc.lpfnWndProc = &WindowManager::WndProc; // ���ν��� �Լ�, �޼��� ó����

	// ������ Ŭ������ �ü���� ���
	RegisterClassExA(&wc);

	int wx, wy;
	RECT rcWindow = { 0, };
	DWORD style, exstyle;

	if (isFullscreen_)
	{
		wx = wy = 0L;
		rcWindow.right = GetSystemMetrics(SM_CXSCREEN);
		rcWindow.bottom = GetSystemMetrics(SM_CYSCREEN);
		style = WS_SYSMENU | WS_POPUP; // ��Ÿ�� ���� (��üȭ���)
		exstyle = NULL;
	}
	else
	{
		// GetSystemMetrics(SM_CXSCREEN) : ���� ȭ���� �ػ󵵸� �޾ƿ�

		wx = (GetSystemMetrics(SM_CXSCREEN) - WINDOW_DEFAULT_WIDTH) / 2;
		wy = (GetSystemMetrics(SM_CYSCREEN) - WINDOW_DEFAULT_HEIGHT) / 2;
		rcWindow.right = WINDOW_DEFAULT_WIDTH;
		rcWindow.bottom = WINDOW_DEFAULT_HEIGHT;
		style = (WS_MINIMIZEBOX * WINDOW_EXIST_MINIMIZEBOX) | (WS_MAXIMIZEBOX * WINDOW_EXIST_MAXIMIZEBOX) | (WS_SYSMENU * WINDOW_EXIST_CLOSEBOX) | WS_CAPTION | (WINDOW_RESIZABLE * WS_THICKFRAME); // ��Ÿ�� ���� (â����)
		exstyle = NULL;
	}

	AdjustWindowRectEx(&rcWindow, style, false, exstyle); // �۾����� ũ�⿡ ���� ũ�⸦ ����

	// �����츦 ����
	hwnd_ = CreateWindowExA(
		exstyle, // Ȯ��� ��Ÿ��
		GAME_TITLE, // ��ϵ� ������ Ŭ���� �̸�
		GAME_TITLE, // ������ ĸ�� �̸�
		style, // ������ ��Ÿ��
		wx, // ������ ���� ����� x��ǥ
		wy, // ������ ���� ����� y��ǥ
		rcWindow.right - rcWindow.left, // ������ ��
		rcWindow.bottom - rcWindow.top, // ������ ����
		NULL, // �θ� �������� �ڵ�
		NULL, // �޴� �Ǵ� �ڽ� ������ �ĺ���
		wc.hInstance, // �����츦 ������ �ν��Ͻ� �ڵ�
		NULL); // CREATESTRUCT ����ü�� ���� ���޵Ǵ� ��

	// SavedRect�� �ʱⰪ�� fullscreen�϶��� �����ǰ� ������
	AdjustWindowRectEx(&savedRect_, WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU | WS_CAPTION, false, NULL);

	// ������ ���
	ShowWindow(hwnd_, SW_SHOWNORMAL);
}


WindowManager::~WindowManager()
{
}

void WindowManager::SetTitle(const std::string& title) // Ÿ��Ʋ ����
{
	SetWindowTextA(hwnd_, title.c_str());
}

void WindowManager::SetPos(const Point2L& pos) // ������ ��ġ ����
{
	SetWindowPos(hwnd_, NULL, pos.x, pos.y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
}

void WindowManager::SetSize(const Size2U& size) // ������ ũ�� ����
{
	//client �������� �����ϵ��� ������
	RECT tmp = { 0, 0, (LONG)size.width, (LONG)size.height };
	savedRect_ = tmp;
	SetWindowPos(hwnd_, HWND_NOTOPMOST, savedRect_.left, savedRect_.top, savedRect_.right - savedRect_.left, savedRect_.bottom - savedRect_.top, SWP_FRAMECHANGED | SWP_SHOWWINDOW);
}

void WindowManager::SetFullscreen(bool flag) // Ǯ��ũ�� ����
{
	//�����Ϸ��� ���°� ������¿� ������ �ƹ��ϵ� ��������
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
