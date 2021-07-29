#pragma once

#include "GraphicManager.h"
#include "InputManager.h"
#include "SoundManager.h"
#include "TextureManager.h"
#include "TimeManager.h"
#include "WindowManager.h"
#include "SceneManager.h"

#define RG2R Engine::GetInstance()
#define RG2R_GraphicM Engine::GetInstance()->GetGraphicM()
#define RG2R_InputM Engine::GetInstance()->GetInputM()
#define RG2R_SoundM Engine::GetInstance()->GetSoundM()
#define RG2R_TimeM Engine::GetInstance()->GetTimeM()
#define RG2R_TextureM Engine::GetInstance()->GetTextureM()
#define RG2R_WindowM Engine::GetInstance()->GetWindowM()
#define RG2R_SceneM Engine::GetInstance()->GetSceneM()

class Engine
{
private:
	Engine();

	GraphicManager* graphicM;
	InputManager* inputM;
	SoundManager* soundM;
	TextureManager* textureM;
	TimeManager* timeM;
	WindowManager* windowM;
	SceneManager* sceneM;

public:
	~Engine();

	static Engine* GetInstance();

	void Init(Scene*);
	void MainLoop();
	void Release();

	GraphicManager* GetGraphicM() { return graphicM; }
	InputManager* GetInputM() { return inputM; }
	SoundManager* GetSoundM() { return soundM; }
	TextureManager* GetTextureM() { return textureM; }
	TimeManager* GetTimeM() { return timeM; }
	WindowManager* GetWindowM() { return windowM; }
	SceneManager* GetSceneM() { return sceneM; }
};