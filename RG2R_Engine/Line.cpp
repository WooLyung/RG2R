#include "stdafx.h"
#include "Line.h"
#include "SpriteRenderer.h"
#include "Dust.h"
#include "Engine.h"
#include "SettingData.h"
#include "SoundMaster.h"

Line::Line(long x, long y)
{
	tilePos = Vec2L(x, y);

	spriteRenderer = AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/Lines/line1.png");
	effect = AttachComponent<Effect>()->ClearEffectInfo()
		->PushEffectInfo(new ColorMatrixEffectInfo(nowColor));
	transform = GetComponent<Transform>()
		->SetAnchor(64, 64)
		->SetPos(x, y);
}

Line::~Line()
{
}

void Line::OnStart()
{
	changeColor = new CommandList;
	changeColor->PushCommand([=]() {
		if (nowColor.r == toColor.r && nowColor.g == toColor.g && nowColor.b == toColor.b && nowColor.a == toColor.a)
		{
			changeColor->Stop();
		}
		else
		{
			if (nowColor.r > toColor.r)
			{
				nowColor.r -= 0.04f;
				if (nowColor.r <= toColor.r)
				{
					nowColor.r = toColor.r;
				}
			}
			else if (nowColor.r < toColor.r)
			{
				nowColor.r += 0.04f;
				if (nowColor.r >= toColor.r)
				{
					nowColor.r = toColor.r;
				}
			}
			if (nowColor.b > toColor.b)
			{
				nowColor.b -= 0.04f;
				if (nowColor.b <= toColor.b)
				{
					nowColor.b = toColor.b;
				}
			}
			else if (nowColor.b < toColor.b)
			{
				nowColor.b += 0.04f;
				if (nowColor.b >= toColor.b)
				{
					nowColor.b = toColor.b;
				}
			}
			if (nowColor.g > toColor.g)
			{
				nowColor.g -= 0.04f;
				if (nowColor.g <= toColor.g)
				{
					nowColor.g = toColor.g;
				}
			}
			else if (nowColor.g < toColor.g)
			{
				nowColor.g += 0.04f;
				if (nowColor.g >= toColor.g)
				{
					nowColor.g = toColor.g;
				}
			}
			if (nowColor.a > toColor.a)
			{
				nowColor.a -= 0.04f;
				if (nowColor.a <= toColor.a)
				{
					nowColor.a = toColor.a;
				}
			}
			else if (nowColor.a < toColor.a)
			{
				nowColor.a += 0.04f;
				if (nowColor.a >= toColor.a)
				{
					nowColor.a = toColor.a;
				}
			}

			effect->ClearEffectInfo()
				->PushEffectInfo(new ColorMatrixEffectInfo(nowColor));
		}
		}, 0.01f);
	changeColor->SetIsLoop(true);
	commandLists.push_back(changeColor);
}

Transform* Line::GetTransform()
{
	return transform;
}

SpriteRenderer* Line::GetSpriteRenderer()
{
	return spriteRenderer;
}

void Line::SetColor(Color8 newColor)
{
	color = newColor;	
	toColor = Color(color.r, color.g, color.b, 1);
	changeColor->Start();
}

void Line::SetColor(Color newColor)
{
	toColor = newColor;
	changeColor->Start();
}

void Line::SetSprite()
{
	if (output == Vec2L(0, 0))
	{
		if (input == Vec2L(-1, 0))
		{
			transform->SetRot(180);
		}
		else if (input == Vec2L(0, 1))
		{
			transform->SetRot(-90);
		}
		else if (input == Vec2L(1, 0))
		{
			transform->SetRot(0);
		}
		else if (input == Vec2L(0, -1))
		{
			transform->SetRot(-270);
		}
	}
	else if (output == Vec2L(1, 0))
	{
		if (input == Vec2L(0, 0))
		{
			transform->SetRot(0);
		}
		else if (input == Vec2L(-1, 0))
		{
			spriteRenderer->SetTexture("Resources/Sprites/Lines/line2.png");
		}
		else if (input == Vec2L(0, 1))
		{
			spriteRenderer->SetTexture("Resources/Sprites/Lines/line3.png");
			transform->SetRot(0);
		}
		else if (input == Vec2L(0, -1))
		{
			spriteRenderer->SetTexture("Resources/Sprites/Lines/line3.png");
			transform->SetRot(90);
		}
	}
	else if (output == Vec2L(-1, 0))
	{
		if (input == Vec2L(0, 0))
		{
			transform->SetRot(180);
		}
		else if (input == Vec2L(1, 0))
		{
			spriteRenderer->SetTexture("Resources/Sprites/Lines/line2.png");
		}
		else if (input == Vec2L(0, 1))
		{
			spriteRenderer->SetTexture("Resources/Sprites/Lines/line3.png");
			transform->SetRot(270);
		}
		else if (input == Vec2L(0, -1))
		{
			spriteRenderer->SetTexture("Resources/Sprites/Lines/line3.png");
			transform->SetRot(180);
		}
	}
	else if (output == Vec2L(0, 1))
	{
		if (input == Vec2L(0, 0))
		{
			transform->SetRot(270);
		}
		else if (input == Vec2L(1, 0))
		{
			spriteRenderer->SetTexture("Resources/Sprites/Lines/line3.png");
			transform->SetRot(0);
		}
		else if (input == Vec2L(-1, 0))
		{
			spriteRenderer->SetTexture("Resources/Sprites/Lines/line3.png");
			transform->SetRot(270);
		}
		else if (input == Vec2L(0, -1))
		{
			spriteRenderer->SetTexture("Resources/Sprites/Lines/line2.png");
			transform->SetRot(90);
		}
	}
	else if (output == Vec2L(0, -1))
	{
		if (input == Vec2L(0, 0))
		{
			transform->SetRot(90);
		}
		else if (input == Vec2L(1, 0))
		{
			spriteRenderer->SetTexture("Resources/Sprites/Lines/line3.png");
			transform->SetRot(90);
		}
		else if (input == Vec2L(-1, 0))
		{
			spriteRenderer->SetTexture("Resources/Sprites/Lines/line3.png");
			transform->SetRot(180);
		}
		else if (input == Vec2L(0, 1))
		{
			spriteRenderer->SetTexture("Resources/Sprites/Lines/line2.png");
			transform->SetRot(90);
		}
	}

	SoundMaster::GetInstance()->PlayEffectSound(SoundID::LINE_CONNECT);
}

void Line::OnDestroy()
{
	if (SettingData::GetInstance()->effect)
	{
		for (int i = 0; i < 4; i++)
		{
			Dust* dust = new Dust;
			dust->GetComponent<Transform>()->SetPos(transform->GetPos());
			RG2R_SceneM->GetScene()->AttachObject(dust);
		}
	}
}