#pragma once
#include"Math.h"
#include"KeyCode.h"
//TODO: rawinput���� ����
#define KEY_MAXCOUNT  256

#define DIK_MOUSELBUTTON 0 // ��Ŭ��
#define DIK_MOUSERBUTTON 1 // ��Ŭ��
#define DIK_MOUSEMBUTTON 2 // ��Ŭ��
#define DIK_MOUSEXBUTTON 3 // Ȯ���ưŬ��

class InputManager
{
private:
	LPDIRECTINPUT8A directInput_; // Direct Input ��ü
	LPDIRECTINPUTDEVICE8A keyboard_; // Direct Input Device (Ű����)
	LPDIRECTINPUTDEVICE8A mouse_; // Direct Input Device (���콺)

	BYTE keyStateL_[KEY_MAXCOUNT]; // keyState (1������ ��)
	BYTE keyStateR_[KEY_MAXCOUNT]; // keyState (���� ������)
	DIMOUSESTATE mouseState_; // mouseState
	BYTE rgbButtonsL_[4];
public:
	InputManager();
	~InputManager();

	void Update(void); // ������Ʈ, App�� �������� ������Ʈ��Ŵ

	KeyState GetKeyState(KeyCode key); // Ű���� ����
	KeyState GetMouseState(MouseCode key); // ���콺 ����

	Point2F GetMousePos() const; // ���콺 ��ġ
	Point2F GetMouseWorldPos() const; // ���콺 ��ġ
	
	long GetMouseDeltaX(void) const; // ���콺 �������� ����
	long GetMouseDeltaY(void) const; // ���콺 �������� ����

	// ������( < 0) ����(-120, -240, -360 ...), �ø���( > 0) ���(120, 240, 360 ...)
	int GetMouseWheel(void) const; // ��

	Vec2F FromScreenToUI(Vec2F);
	Vec2F FromUIToScreen(Vec2F);
	Vec2F FromScreenToWorld(Vec2F);
	Vec2F FromUIToWorld(Vec2F);
	Vec2F FromWorldToUI(Vec2F);
	Vec2F FromWorldToScreen(Vec2F);
};