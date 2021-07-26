#include "stdafx.h"
#include "GateF.h"

GateF::GateF()
{
	spriteRenderer = AttachComponent<SpriteRenderer>();
	transform = GetComponent<Transform>()
		->SetAnchor(64, 64);
	effect = AttachComponent<Effect>();

	auto obj1 = new Object;
	outline = obj1->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/Gates/battery_uncolored.png");
	outline->SetIsEnable(false);
	obj1->GetComponent<Transform>()
		->SetAnchor(64, 64);
	AttachChild(obj1);

	auto obj2 = new Object;
	staticObj = obj2->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/Gates/static.png");
	staticObj->SetIsEnable(false);
	obj2->GetComponent<Transform>()
		->SetAnchor(64, 64);
	AttachChild(obj2);

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

GateF::~GateF()
{
}

SpriteRenderer* GateF::GetSpriteRenderer()
{
	return spriteRenderer;
}

Transform* GateF::GetTransform()
{
	return transform;
}

Effect* GateF::GetEffect()
{
	return effect;
}

void GateF::SetPos(Vec2L pos_)
{
	pos = pos_;
	transform->SetPos(pos.x, pos.y);
}

void GateF::SetIsStatic(bool isStatic)
{
	this->isStatic = isStatic;
	staticObj->SetIsEnable(isStatic);
}

void GateF::SetColor(std::string color)
{
	this->color = color;

	if (color == "white")
		toColor = Color(1, 1, 1, 1);
	else if (color == "red")
		toColor = Color(1, 0, 0, 1);
	else if (color == "green")
		toColor = Color(0, 1, 0, 1);
	else if (color == "blue")
		toColor = Color(0, 0, 1, 1);
	else if (color == "cyan")
		toColor = Color(0, 1, 1, 1);
	else if (color == "yellow")
		toColor = Color(1, 1, 0, 1);
	else if (color == "magenta")
		toColor = Color(1, 0, 1, 1);

	changeColor->Start();
}