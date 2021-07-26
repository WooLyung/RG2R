#pragma once
#include "Effect.h"
#include "stdafx.h"

class EffectInfo
{
public:
	EffectInfo();
	~EffectInfo();
	virtual ID2D1Image* GetOutputImage(ID2D1Image* input) = 0;
};

class ColorMatrixEffectInfo
	: public EffectInfo
{
private:
	D2D1_MATRIX_5X4_F colorMatrix_;

public:
	ColorMatrixEffectInfo(const Color& color = Color(1.f, 1.f, 1.f, 1.f));
	~ColorMatrixEffectInfo();
	ID2D1Image* GetOutputImage(ID2D1Image* input) override;

	void SetColor(const Color& color);
	Color GetColor();
};

class DiscreteTransferEffectInfo
	: public EffectInfo
{
public:
	float redTable[5];
	float greenTable[5];
	float blueTable[5];
	float alphaTable[5];
public:
	DiscreteTransferEffectInfo();
	DiscreteTransferEffectInfo(float r1, float r2, float r3, float r4, float r5,
		float g1, float g2, float g3, float g4, float g5,
		float b1, float b2, float b3, float b4, float b5,
		float a1, float a2, float a3, float a4, float a5);
	~DiscreteTransferEffectInfo();

	ID2D1Image* GetOutputImage(ID2D1Image* input) override;

};

class GammaTransferEffectInfo
	:public EffectInfo
{
public:
	float redAmplitude;
	float redExponent;
	float redOffset;
	float greenAmplitude;
	float greenExponent;
	float greenOffset;
	float blueAmplitude;
	float blueExponent;
	float blueOffset;
	float alphaAmplitude;
	float alphaExponent;
	float alphaOffset;
public:
	GammaTransferEffectInfo();
	GammaTransferEffectInfo(float redAmplitude, float redExponent, float redOffset,
		float greenAmplitude, float greenExponent, float greenOffset,
		float blueAmplitude, float blueExponent, float blueOffset,
		float alphaAmplitude, float alphaExponent, float alphaOffset);
	~GammaTransferEffectInfo();

	ID2D1Image* GetOutputImage(ID2D1Image* input) override;
};

class HueRotationEffectInfo
	:public EffectInfo
{
public:
	Degree angle;
public:
	HueRotationEffectInfo(Degree angle = 0.f);
	~HueRotationEffectInfo();
	ID2D1Image* GetOutputImage(ID2D1Image* input) override;
};

class LinearTransferEffectInfo
	:public EffectInfo
{
public:
	//C' = mC + B( 일차함수 ) where m == slope and B == yIntercept
	float redYIntercept;// y절편
	float redSlope;// 기울기
	float greenYIntercept;
	float greenSlope;
	float blueYIntercept;
	float blueSlope;
	float alphaYIntercept;
	float alphaSlope;
public:
	LinearTransferEffectInfo();
	LinearTransferEffectInfo(float redYIntercept, float redSlope,
		float greenYIntercept, float greenSlope,
		float blueYIntercept, float blueSlope,
		float alphaYIntercept, float alphaSlope);
	~LinearTransferEffectInfo();
	ID2D1Image* GetOutputImage(ID2D1Image* input) override;
};

class SaturationEffectInfo
	:public EffectInfo
{
public:
	// [0, 1] 
	//1 : fully saturated
	//0 : monochrome
	float saturation;
public:
	SaturationEffectInfo(float saturation = 0.5);
	~SaturationEffectInfo();
	ID2D1Image* GetOutputImage(ID2D1Image* input) override;
};

class TableTransferEffectInfo
	:public EffectInfo
{
public:
	float redTable[5];
	float greenTable[5];
	float blueTable[5];
	float alphaTable[5];
public:
	TableTransferEffectInfo();
	TableTransferEffectInfo(
		float r1, float r2, float r3, float r4, float r5,
		float g1, float g2, float g3, float g4, float g5,
		float b1, float b2, float b3, float b4, float b5,
		float a1, float a2, float a3, float a4, float a5);
	~TableTransferEffectInfo();

	ID2D1Image* GetOutputImage(ID2D1Image* input) override;
};

class MorphologyEffectInfo
	:public EffectInfo
{
public:
	UINT width;
	UINT height;
	D2D1_MORPHOLOGY_MODE mode;

public:
	MorphologyEffectInfo(UINT width = 1, UINT height = 1, D2D1_MORPHOLOGY_MODE mode = D2D1_MORPHOLOGY_MODE_ERODE);
	~MorphologyEffectInfo();

	ID2D1Image* GetOutputImage(ID2D1Image* input) override;
};

class TDRotationEffectInfo
	:public EffectInfo
{
public:
	D2D1_VECTOR_3F vec;

public:
	TDRotationEffectInfo(D2D1_VECTOR_3F);
	~TDRotationEffectInfo();

	ID2D1Image* GetOutputImage(ID2D1Image* input) override;
};

class BrightnessEffectInfo
	:public EffectInfo
{
public:
	float whiteStart, whiteEnd, blackStart, blackEnd;

public:
	BrightnessEffectInfo(float whiteStart, float whiteEnd, float blackStart, float blackEnd);
	~BrightnessEffectInfo();

	ID2D1Image* GetOutputImage(ID2D1Image* input) override;
};

class GaussianBlurEffectInfo
	:public EffectInfo
{
public:
	float level;

public:
	GaussianBlurEffectInfo(float level);
	~GaussianBlurEffectInfo();

	ID2D1Image* GetOutputImage(ID2D1Image* input) override;
};