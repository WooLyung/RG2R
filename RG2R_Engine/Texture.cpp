#include "stdafx.h"
#include "Texture.h"
#include "Engine.h"

Texture::Texture(const std::string& path)
	:bitmap_(nullptr)
{
	IWICBitmapDecoder* decoder = nullptr;
	HR(
		RG2R_TextureM->wicFactory_->CreateDecoderFromFilename(
			Widen(path).c_str(),
			nullptr,
			GENERIC_READ,
			WICDecodeMetadataCacheOnDemand,
			&decoder
		)
	);
	IWICBitmapFrameDecode* frame = nullptr;
	HR(
		decoder->GetFrame(0, &frame)
	);

	IWICFormatConverter* convertedSrcBmp = nullptr;
	HR(
		RG2R_TextureM->wicFactory_->CreateFormatConverter(
			&convertedSrcBmp
		)
	);

	HR(
		convertedSrcBmp->Initialize(
			frame,
			GUID_WICPixelFormat32bppPRGBA,
			WICBitmapDitherTypeNone,
			nullptr,
			0.f,
			WICBitmapPaletteTypeCustom
		)
	);

	HR(
		RG2R_GraphicM->GetDeviceContext()->CreateBitmapFromWicBitmap(
			convertedSrcBmp,
			&bitmap_
		)
	);

	decoder->Release();
	convertedSrcBmp->Release();
	frame->Release();
}

Texture::~Texture()
{
	bitmap_->Release();
}

Size2F Texture::GetSize()
{
	return Size2F(bitmap_->GetSize().width, bitmap_->GetSize().height);
}

void Texture::Render(const Rect& visibleRect)
{
	ID2D1Layer *pLayer = NULL;
	ID2D1PathGeometry *m_pPathGeometry;
	HR(
		RG2R_GraphicM->GetFactory()->CreatePathGeometry(&m_pPathGeometry)
	);

	ID2D1GeometrySink *pSink = NULL;
	m_pPathGeometry->Open(&pSink);
	pSink->SetFillMode(D2D1_FILL_MODE_WINDING);
	pSink->BeginFigure(D2D1::Point2F(30, 30), D2D1_FIGURE_BEGIN_FILLED);
	pSink->AddLine(D2D1::Point2F(5000, 30));
	pSink->AddLine(D2D1::Point2F(5000, 5000));
	pSink->AddLine(D2D1::Point2F(30, 5000));
	pSink->EndFigure(D2D1_FIGURE_END_CLOSED);
	pSink->Close();

	auto parameters = D2D1::LayerParameters(D2D1::InfiniteRect(), m_pPathGeometry);
	parameters.maskTransform = D2D1::Matrix3x2F::Identity();

	RG2R_GraphicM->GetDeviceContext()->PushLayer(
		parameters,
		pLayer
	);

	RG2R_GraphicM->GetDeviceContext()->DrawBitmap(
		bitmap_,
		nullptr,
		1.f,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		&visibleRect
	);

	RG2R_GraphicM->GetDeviceContext()->PopLayer();

	SafeDelete(pLayer);
	pSink->Release();
	m_pPathGeometry->Release();
}