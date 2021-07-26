#pragma once
#include "Math.h"

class WindowManager
{
private:
	HWND hwnd_;
	MSG msg_;
	RECT savedRect_;
	char cStrBuffer_[C_STR_BUFFER_SIZE];
	bool isFullscreen_;
	bool isResizable_;

public:
	WindowManager();
	~WindowManager();

	void SetTitle(const std::string& title);
	void SetPos(const Point2L& pos);
	void SetSize(const Size2U& size);
	void SetFullscreen(bool flag);
	void SetResizable(bool flag);
	void SetMaximizable(bool flag);
	void ToggleFullscreen();

	HWND GetHwnd();
	std::string GetTitle();
	Point2L GetPos();
	Size2U GetSize();
	void Minimize();
	void Maximize();
	void Focus();
	void Foreground();
	void Activate();
	void Close();

	bool IsRunning();
	bool IsResizable();
	bool IsMaximizable();
	bool IsMinimized();
	bool IsMaximized();
	bool IsFocused();
	bool IsActive();
	bool IsFullscreen();
	bool MsgLoop();

	static LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};