#pragma once
#include "EffectType.h"
#include "Renderer.h"

class GraphicManager
{
private:
	friend class TextRenderer;

	ID2D1Factory1* factory_;
	IDWriteFactory* dwFactory_;
	ID2D1Device* d2dDevice_;
	ID2D1DeviceContext* deviceContext_;
	IDXGISwapChain1* swapChain_;
	ID2D1Bitmap1* targetBitmap_;

	ID2D1SolidColorBrush* outlineBrush_;
	ID2D1SolidColorBrush* fillBrush_;

	std::map<EffectType, ID2D1Effect*> effects_;
	std::vector<Renderer*> renderBuffer;
	std::vector<Renderer*> viewRenderBuffer;

public:
	GraphicManager();
	~GraphicManager();

	void Render();
	void SetTargetBitmap(ID2D1Bitmap1* bitmap);
	void PushRenderBuffer(Renderer*);
	void PushViewRenderBuffer(Renderer*);

	ID2D1DeviceContext* GetDeviceContext() const { return deviceContext_; }
	ID2D1Effect* GetEffect(EffectType type) const { return effects_.at(type); }
	ID2D1Factory1* GetFactory() const { return factory_; }
	IDXGISwapChain1* GetSwapChain() { return swapChain_; }
	ID2D1Bitmap1* GetTartgetBitmap() { return targetBitmap_; }
	IDWriteFactory* GetDwFactory() { return dwFactory_; }
	std::vector<Renderer*>* GetViewRenderBuffer() { return &viewRenderBuffer; }
};