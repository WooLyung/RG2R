#include "stdafx.h"
#include "EffectInfo.h"
#include "Math.h"
#include "Engine.h"

#pragma region EffectInfo
EffectInfo::EffectInfo()
{
}

EffectInfo::~EffectInfo()
{
}
#pragma endregion

#pragma region ColorMatrixEffectInfo
ColorMatrixEffectInfo::ColorMatrixEffectInfo(const Color& color)
{
	colorMatrix_ = D2D1::Matrix5x4F(
		color.r, 0, 0, 0,
		0, color.g, 0, 0,
		0, 0, color.b, 0,
		0, 0, 0, color.a,
		0, 0, 0, 0
	);
}

ColorMatrixEffectInfo::~ColorMatrixEffectInfo()
{
}

ID2D1Image* ColorMatrixEffectInfo::GetOutputImage(ID2D1Image* input)
{
	auto e = RG2R_GraphicM->GetEffect(ET_ColorMatrix);
	e->SetInput(0, input);
	e->SetValue(D2D1_COLORMATRIX_PROP_COLOR_MATRIX, colorMatrix_);
	ID2D1Image* output;
	e->GetOutput(&output);
	return output;
}
void ColorMatrixEffectInfo::SetColor(const Color & color)
{
	colorMatrix_ = D2D1::Matrix5x4F(
		color.r, 0, 0, 0,
		0, color.g, 0, 0,
		0, 0, color.b, 0,
		0, 0, 0, color.a,
		0, 0, 0, 0
	);
}
Color ColorMatrixEffectInfo::GetColor()
{
	return Color(colorMatrix_._11, colorMatrix_._22, colorMatrix_._33, colorMatrix_._44);
}
#pragma endregion

#pragma region DiscreteTransferEffectInfo
DiscreteTransferEffectInfo::DiscreteTransferEffectInfo()
	:redTable{ 0,0,0.5,1,1 }, greenTable{ 0,0,0.5,1,1 }, blueTable{ 0,0,0.5,1,1 }, alphaTable{ 0,0,0.5,1,1 }
{
}

DiscreteTransferEffectInfo::DiscreteTransferEffectInfo(float r1, float r2, float r3, float r4, float r5, float g1, float g2, float g3, float g4, float g5, float b1, float b2, float b3, float b4, float b5, float a1, float a2, float a3, float a4, float a5)
	: redTable{ r1,r2,r3,r4,r5 }, greenTable{ g1,g2,g3,g4,g5 }, blueTable{ b1,b2,b3,b4,b5 }, alphaTable{ a1,a2,a3,a4,a5 }
{
}

DiscreteTransferEffectInfo::~DiscreteTransferEffectInfo()
{

}

ID2D1Image * DiscreteTransferEffectInfo::GetOutputImage(ID2D1Image * input)
{
	auto e = RG2R_GraphicM->GetEffect(ET_DiscreteTransfer);
	e->SetInput(0, input);

	e->SetValue(D2D1_DISCRETETRANSFER_PROP_RED_TABLE, redTable);
	e->SetValue(D2D1_DISCRETETRANSFER_PROP_GREEN_TABLE, greenTable);
	e->SetValue(D2D1_DISCRETETRANSFER_PROP_BLUE_TABLE, blueTable);
	e->SetValue(D2D1_DISCRETETRANSFER_PROP_ALPHA_TABLE, alphaTable);

	ID2D1Image* output;
	e->GetOutput(&output);
	return output;
}
#pragma endregion

#pragma region GammaTransferEffectInfo
GammaTransferEffectInfo::GammaTransferEffectInfo()
	:redAmplitude(1.f), redExponent(1.f), redOffset(0.f),
	greenAmplitude(1.f), greenExponent(1.f), greenOffset(0.f),
	blueAmplitude(1.f), blueExponent(1.f), blueOffset(0.f),
	alphaAmplitude(1.f), alphaExponent(1.f), alphaOffset(0.f)
{
}

GammaTransferEffectInfo::GammaTransferEffectInfo(float redAmplitude, float redExponent, float redOffset, float greenAmplitude, float greenExponent, float greenOffset, float blueAmplitude, float blueExponent, float blueOffset, float alphaAmplitude, float alphaExponent, float alphaOffset)
	:redAmplitude(redAmplitude), redExponent(redExponent), redOffset(redOffset),
	greenAmplitude(greenAmplitude), greenExponent(greenExponent), greenOffset(greenOffset),
	blueAmplitude(blueAmplitude), blueExponent(blueExponent), blueOffset(blueOffset),
	alphaAmplitude(alphaAmplitude), alphaExponent(alphaExponent), alphaOffset(alphaOffset)
{
}

GammaTransferEffectInfo::~GammaTransferEffectInfo()
{
}

ID2D1Image * GammaTransferEffectInfo::GetOutputImage(ID2D1Image * input)
{
	auto e = RG2R_GraphicM->GetEffect(ET_GammaTransfer);
	e->SetInput(0, input);
	e->SetValue(D2D1_GAMMATRANSFER_PROP_RED_AMPLITUDE, redAmplitude);
	e->SetValue(D2D1_GAMMATRANSFER_PROP_RED_EXPONENT, redExponent);
	e->SetValue(D2D1_GAMMATRANSFER_PROP_RED_OFFSET, redOffset);
	e->SetValue(D2D1_GAMMATRANSFER_PROP_GREEN_AMPLITUDE, greenAmplitude);
	e->SetValue(D2D1_GAMMATRANSFER_PROP_GREEN_EXPONENT, greenExponent);
	e->SetValue(D2D1_GAMMATRANSFER_PROP_GREEN_OFFSET, greenOffset);
	e->SetValue(D2D1_GAMMATRANSFER_PROP_BLUE_AMPLITUDE, blueAmplitude);
	e->SetValue(D2D1_GAMMATRANSFER_PROP_BLUE_EXPONENT, blueExponent);
	e->SetValue(D2D1_GAMMATRANSFER_PROP_BLUE_OFFSET, blueOffset);
	e->SetValue(D2D1_GAMMATRANSFER_PROP_ALPHA_AMPLITUDE, alphaAmplitude);
	e->SetValue(D2D1_GAMMATRANSFER_PROP_ALPHA_EXPONENT, alphaExponent);
	e->SetValue(D2D1_GAMMATRANSFER_PROP_ALPHA_OFFSET, alphaOffset);
	ID2D1Image* output;
	e->GetOutput(&output);
	return output;
}
#pragma endregion

#pragma region HueRotationEffectInfo
HueRotationEffectInfo::HueRotationEffectInfo(Degree angle)
	:angle(angle)
{
}

HueRotationEffectInfo::~HueRotationEffectInfo()
{
}

ID2D1Image * HueRotationEffectInfo::GetOutputImage(ID2D1Image * input)
{
	auto e = RG2R_GraphicM->GetEffect(ET_HueRotation);
	e->SetInput(0, input);
	e->SetValue(D2D1_HUEROTATION_PROP_ANGLE, angle);
	ID2D1Image* output;
	e->GetOutput(&output);
	return output;
}
#pragma endregion

#pragma region LinearTransferEffectInfo
LinearTransferEffectInfo::LinearTransferEffectInfo()
	:redYIntercept(0.f), redSlope(1.f),
	greenYIntercept(0.f), greenSlope(1.f),
	blueYIntercept(0.f), blueSlope(1.f),
	alphaYIntercept(0.f), alphaSlope(1.f)
{
}

LinearTransferEffectInfo::LinearTransferEffectInfo(float redYIntercept, float redSlope, float greenYIntercept, float greenSlope, float blueYIntercept, float blueSlope, float alphaYIntercept, float alphaSlope)
	:redYIntercept(redYIntercept), redSlope(redSlope),
	greenYIntercept(greenYIntercept), greenSlope(greenSlope),
	blueYIntercept(blueYIntercept), blueSlope(blueSlope),
	alphaYIntercept(alphaYIntercept), alphaSlope(alphaSlope)
{
}

LinearTransferEffectInfo::~LinearTransferEffectInfo()
{
}

ID2D1Image * LinearTransferEffectInfo::GetOutputImage(ID2D1Image * input)
{
	auto e = RG2R_GraphicM->GetEffect(ET_LinearTransfer);
	e->SetInput(0, input);
	e->SetValue(D2D1_LINEARTRANSFER_PROP_RED_Y_INTERCEPT, redYIntercept);
	e->SetValue(D2D1_LINEARTRANSFER_PROP_RED_SLOPE, redSlope);
	e->SetValue(D2D1_LINEARTRANSFER_PROP_GREEN_Y_INTERCEPT, greenYIntercept);
	e->SetValue(D2D1_LINEARTRANSFER_PROP_GREEN_SLOPE, greenSlope);
	e->SetValue(D2D1_LINEARTRANSFER_PROP_BLUE_Y_INTERCEPT, blueYIntercept);
	e->SetValue(D2D1_LINEARTRANSFER_PROP_BLUE_SLOPE, blueSlope);
	e->SetValue(D2D1_LINEARTRANSFER_PROP_ALPHA_Y_INTERCEPT, alphaYIntercept);
	e->SetValue(D2D1_LINEARTRANSFER_PROP_ALPHA_SLOPE, alphaSlope);
	ID2D1Image* output;
	e->GetOutput(&output);
	return output;
}
#pragma endregion

#pragma region SaturationEffectInfo
SaturationEffectInfo::SaturationEffectInfo(float saturation)
	:saturation(saturation)
{
}

SaturationEffectInfo::~SaturationEffectInfo()
{
}

ID2D1Image * SaturationEffectInfo::GetOutputImage(ID2D1Image * input)
{
	auto e = RG2R_GraphicM->GetEffect(ET_Saturation);
	e->SetInput(0, input);
	e->SetValue(D2D1_SATURATION_PROP_SATURATION, saturation);
	ID2D1Image* output;
	e->GetOutput(&output);
	return output;
}
#pragma endregion

#pragma region TableTransferEffectInfo

TableTransferEffectInfo::TableTransferEffectInfo()
	:redTable{ 0,0.25,0.5,0.75,1 }, greenTable{ 0,0.25,0.5,0.75,1 }, blueTable{ 0,0.25,0.5,0.75,1 }, alphaTable{ 0,0.25,0.5,0.75,1 }
{
}

TableTransferEffectInfo::TableTransferEffectInfo(float r1, float r2, float r3, float r4, float r5, float g1, float g2, float g3, float g4, float g5, float b1, float b2, float b3, float b4, float b5, float a1, float a2, float a3, float a4, float a5)
	: redTable{ r1,r2,r3,r4,r5 }, greenTable{ g1,g2,g3,g4,g5 }, blueTable{ b1,b2,b3,b4,b5 }, alphaTable{ a1,a2,a3,a4,a5 }
{
}

TableTransferEffectInfo::~TableTransferEffectInfo()
{
}

ID2D1Image* TableTransferEffectInfo::GetOutputImage(ID2D1Image* input)
{
	auto e = RG2R_GraphicM->GetEffect(ET_TableTransfer);
	e->SetInput(0, input);

	e->SetValue(D2D1_TABLETRANSFER_PROP_RED_TABLE, redTable);
	e->SetValue(D2D1_TABLETRANSFER_PROP_GREEN_TABLE, greenTable);
	e->SetValue(D2D1_TABLETRANSFER_PROP_BLUE_TABLE, blueTable);
	e->SetValue(D2D1_TABLETRANSFER_PROP_ALPHA_TABLE, alphaTable);

	ID2D1Image* output;
	e->GetOutput(&output);
	return output;
}

#pragma endregion

#pragma region MorphologyEffectInfo
MorphologyEffectInfo::MorphologyEffectInfo(UINT mpwidth, UINT mpheight, D2D1_MORPHOLOGY_MODE mode)
	:height(mpheight), width(mpwidth), mode(mode)
{
}

MorphologyEffectInfo::~MorphologyEffectInfo()
{
}

ID2D1Image * MorphologyEffectInfo::GetOutputImage(ID2D1Image * input)
{
	auto e = RG2R_GraphicM->GetEffect(ET_Morphology);
	e->SetInput(0, input);

	e->SetValue(D2D1_MORPHOLOGY_PROP_MODE, mode);
	e->SetValue(D2D1_MORPHOLOGY_PROP_WIDTH, width);
	e->SetValue(D2D1_MORPHOLOGY_PROP_HEIGHT, height);

	ID2D1Image* output;
	e->GetOutput(&output);
	return output;
}

TDRotationEffectInfo::TDRotationEffectInfo(D2D1_VECTOR_3F vec)
{
	this->vec = vec;
}

TDRotationEffectInfo::~TDRotationEffectInfo()
{

}

ID2D1Image* TDRotationEffectInfo::GetOutputImage(ID2D1Image* input)
{
	auto e = RG2R_GraphicM->GetEffect(ET_3DPerspectiveTransform);
	e->SetInput(0, input);
	e->SetValue(D2D1_3DPERSPECTIVETRANSFORM_PROP_ROTATION, vec);

	ID2D1Image* output;
	e->GetOutput(&output);
	return output;
}

BrightnessEffectInfo::BrightnessEffectInfo(float whiteStart, float whiteEnd, float blackStart, float blackEnd)
	: whiteStart(whiteStart), blackStart(blackStart), whiteEnd(whiteEnd), blackEnd(blackEnd)
{

}

BrightnessEffectInfo::~BrightnessEffectInfo()
{

}

ID2D1Image* BrightnessEffectInfo::GetOutputImage(ID2D1Image* input)
{
	auto e = RG2R_GraphicM->GetEffect(ET_Brightness);
	e->SetInput(0, input);
	e->SetValue(D2D1_BRIGHTNESS_PROP_BLACK_POINT, D2D1::Vector2F(blackStart, blackEnd));
	e->SetValue(D2D1_BRIGHTNESS_PROP_WHITE_POINT, D2D1::Vector2F(whiteStart, whiteEnd));

	ID2D1Image* output;
	e->GetOutput(&output);
	return output;
}

GaussianBlurEffectInfo::GaussianBlurEffectInfo(float level)
	: level(level) {}

GaussianBlurEffectInfo::~GaussianBlurEffectInfo()
{

}

ID2D1Image* GaussianBlurEffectInfo::GetOutputImage(ID2D1Image* input)
{
	auto e = RG2R_GraphicM->GetEffect(ET_GaussianBlur);
	e->SetInput(0, input);
	e->SetValue(D2D1_GAUSSIANBLUR_PROP_STANDARD_DEVIATION, level);

	ID2D1Image* output;
	e->GetOutput(&output);
	return output;
}

#pragma endregion