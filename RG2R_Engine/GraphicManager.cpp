#include "stdafx.h"
#include "GraphicManager.h"
#include "Engine.h"
#include "WindowManager.h"
#include "Settings.h"

GraphicManager::GraphicManager()
	:deviceContext_(nullptr)
{
	ID3D11Device* device;
	ID3D11DeviceContext* context;
	IDXGIDevice1* dxgiDevice;
	IDXGIAdapter* dxgiAdapter;
	IDXGIFactory2* dxgiFactory;
	ID3D11Texture2D* backBuffer;
	IDXGISurface* dxgiBackBuffer;
	UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1
	};
	D3D_FEATURE_LEVEL featureLevel;
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc = { 0 };
	D2D1_BITMAP_PROPERTIES1 bitmapProperties;

	D2D1_FACTORY_OPTIONS opt;
	opt.debugLevel = D2D1_DEBUG_LEVEL_NONE;
	HR(
		D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, opt, &factory_)
	);
	HR(
		DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_ISOLATED,
			__uuidof(*dwFactory_),
			(IUnknown**)&dwFactory_
		)
	);

	HR(
		D3D11CreateDevice(
			nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			0,
			creationFlags,
			featureLevels,
			ARRAYSIZE(featureLevels),
			D3D11_SDK_VERSION,
			&device,
			&featureLevel,
			&context
		)
	);

	HR(
		device->QueryInterface(__uuidof(IDXGIDevice), (void **)&dxgiDevice)
	);
	HR(
		factory_->CreateDevice(dxgiDevice, &d2dDevice_)
	);

	HR(
		d2dDevice_->CreateDeviceContext(
			D2D1_DEVICE_CONTEXT_OPTIONS_NONE,
			&deviceContext_
		)
	);

	swapChainDesc.Width = GetSystemMetrics(SM_CXSCREEN);
	swapChainDesc.Height = GetSystemMetrics(SM_CYSCREEN);
	swapChainDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	swapChainDesc.Stereo = false;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = 2;
	swapChainDesc.Scaling = DXGI_SCALING_NONE;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapChainDesc.Flags = 0;

	HR(
		dxgiDevice->GetAdapter(&dxgiAdapter)
	);

	HR(
		dxgiAdapter->GetParent(IID_PPV_ARGS(&dxgiFactory))
	);


	HR(
		dxgiFactory->CreateSwapChainForHwnd(
			device,
			RG2R_WindowM->GetHwnd(),
			&swapChainDesc,
			nullptr,
			nullptr,
			&swapChain_
		)
	);

	HR(
		dxgiDevice->SetMaximumFrameLatency(1)
	);

	HR(
		swapChain_->GetBuffer(0, IID_PPV_ARGS(&backBuffer))
	);

	bitmapProperties =
		D2D1::BitmapProperties1(
			D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
			D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_IGNORE),
			96.f,
			96.f
		);

	HR(
		swapChain_->GetBuffer(0, IID_PPV_ARGS(&dxgiBackBuffer))
	);

	HR(
		deviceContext_->CreateBitmapFromDxgiSurface(
			dxgiBackBuffer,
			&bitmapProperties,
			&targetBitmap_
		)
	);

	deviceContext_->SetTarget(targetBitmap_);

	HR(
		deviceContext_->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::Enum::Green),
			&outlineBrush_
		)
	);
	HR(
		deviceContext_->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::Enum::White),
			&fillBrush_
		)
	);

	deviceContext_->SetDpi(96, 96);
	deviceContext_->CreateEffect(CLSID_D2D1ColorMatrix, &effects_[ET_ColorMatrix]);
	deviceContext_->CreateEffect(CLSID_D2D1DiscreteTransfer, &effects_[ET_DiscreteTransfer]);
	deviceContext_->CreateEffect(CLSID_D2D1GammaTransfer, &effects_[ET_GammaTransfer]);
	deviceContext_->CreateEffect(CLSID_D2D1HueRotation, &effects_[ET_HueRotation]);
	deviceContext_->CreateEffect(CLSID_D2D1LinearTransfer, &effects_[ET_LinearTransfer]);
	deviceContext_->CreateEffect(CLSID_D2D1Saturation, &effects_[ET_Saturation]);
	deviceContext_->CreateEffect(CLSID_D2D1TableTransfer, &effects_[ET_TableTransfer]);
	deviceContext_->CreateEffect(CLSID_D2D1DirectionalBlur, &effects_[ET_DirectionalBlur]);
	deviceContext_->CreateEffect(CLSID_D2D1GaussianBlur, &effects_[ET_GaussianBlur]);
	deviceContext_->CreateEffect(CLSID_D2D1Morphology, &effects_[ET_Morphology]);
	deviceContext_->CreateEffect(CLSID_D2D1Brightness, &effects_[ET_Brightness]);
	deviceContext_->CreateEffect(CLSID_D2D13DTransform, &effects_[ET_3DTransform]);
	deviceContext_->CreateEffect(CLSID_D2D13DPerspectiveTransform, &effects_[ET_3DPerspectiveTransform]);
	deviceContext_->CreateEffect(CLSID_D2D1Tile, &effects_[ET_Tile]);

	device->Release();
	context->Release();
	dxgiDevice->Release();
	dxgiAdapter->Release();
	dxgiFactory->Release();
	backBuffer->Release();
	dxgiBackBuffer->Release();
}

GraphicManager::~GraphicManager()
{
	factory_->Release();
	dwFactory_->Release();
	d2dDevice_->Release();
	deviceContext_->Release();
	swapChain_->Release();
	targetBitmap_->Release();
	outlineBrush_->Release();
	fillBrush_->Release();
	for (auto i : effects_)
		i.second->Release();
}

void GraphicManager::Render()
{
	renderBuffer.clear();
	RG2R_SceneM->Render();

	deviceContext_->SetTarget(targetBitmap_);
	deviceContext_->BeginDraw();
	deviceContext_->Clear(D2D1::ColorF(BACKGROUND_COLOR));

	sort(renderBuffer.begin(), renderBuffer.end(), [](Renderer* renderer1, Renderer* renderer2) -> bool {
		return renderer1->GetZ_index() < renderer2->GetZ_index();
		});
	for_each(renderBuffer.begin(), renderBuffer.end(), [](Renderer* renderer) -> void {
		renderer->Draw();
		});

	deviceContext_->EndDraw();

	swapChain_->Present(1, 0);
}

void GraphicManager::PushRenderBuffer(Renderer* renderer)
{
	renderBuffer.push_back(renderer);
}

void GraphicManager::PushViewRenderBuffer(Renderer* renderer)
{
	viewRenderBuffer.push_back(renderer);
}

void GraphicManager::SetTargetBitmap(ID2D1Bitmap1* bitmap)
{
	deviceContext_->SetTarget(bitmap);
}