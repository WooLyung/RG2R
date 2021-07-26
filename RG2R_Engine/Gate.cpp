#include "stdafx.h"
#include "Gate.h"
#include "CommandList.h"
#include "Command.h"

Gate::Gate(long x, long y, Dir dir)
{
	tilePos = Vec2L(x, y);

	spriteRenderer = AttachComponent<SpriteRenderer>();
	effect = AttachComponent<Effect>()
		->PushEffectInfo(new ColorMatrixEffectInfo(nowColor));
	transform = GetComponent<Transform>()
		->SetAnchor(64, 64)
		->SetPos(x, y);

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

Gate::~Gate()
{
}

Dir Gate::GetDir()
{
	return dir;
}

void Gate::SetColor(Color8 newColor)
{
	color = newColor;
	toColor = Color(color.r, color.g, color.b, 1);
	changeColor->Start();
}

void Gate::SetColor(Color newColor)
{
	toColor = newColor;
	changeColor->Start();
}

void Gate::SetDir(Dir dir)
{
	this->dir = dir;

	switch (dir)
	{
		case Dir::RIGHT:
			transform->SetRot(0);
			break;
		case Dir::DOWN:
			transform->SetRot(90);
			break;
		case Dir::LEFT:
			transform->SetRot(180);
			break;
		case Dir::UP:
			transform->SetRot(270);
			break;
	}
}

Transform* Gate::GetTransform()
{
	return transform;
}

SpriteRenderer* Gate::GetSpriteRenderer()
{
	return spriteRenderer;
}

void Gate::SetPos(int x, int y)
{
	transform->SetPos(x, y);
	tilePos = Vec2L(x, y);
}

void Gate::SetRot(Dir dir)
{
	int rotCount = 0;

	if (dir == DOWN) rotCount = 1;
	else if (dir == LEFT) rotCount = 2;
	else if (dir == UP) rotCount = 3;

	SetDir(dir);
	while (rotCount--)
	{
		for (int i = 0; i < input.size(); i++)
		{
			if (input[i].x == 1 && input[i].y == 0)
			{
				input[i].x = 0;
				input[i].y = -1;
			}
			else if (input[i].x == 0 && input[i].y == -1)
			{
				input[i].x = -1;
				input[i].y = 0;
			}
			else if (input[i].x == -1 && input[i].y == 0)
			{
				input[i].x = 0;
				input[i].y = 1;
			}
			else if (input[i].x == 0 && input[i].y == 1)
			{
				input[i].x = 1;
				input[i].y = 0;
			}
		}
		for (int i = 0; i < output.size(); i++)
		{
			if (output[i].x == 1 && output[i].y == 0)
			{
				output[i].x = 0;
				output[i].y = -1;
			}
			else if (output[i].x == 0 && output[i].y == -1)
			{
				output[i].x = -1;
				output[i].y = 0;
			}
			else if (output[i].x == -1 && output[i].y == 0)
			{
				output[i].x = 0;
				output[i].y = 1;
			}
			else if (output[i].x == 0 && output[i].y == 1)
			{
				output[i].x = 1;
				output[i].y = 0;
			}
		}
	}
}

void Gate::SetStatic(bool isStatic)
{
	this->isStatic = isStatic;

	if (isStatic)
	{
		auto obj = new Object;
		obj->AttachComponent<SpriteRenderer>()->SetTexture("Resources/Sprites/Gates/static.png");
		obj->GetComponent<Transform>()->SetAnchor(64, 64);
		obj->ChangeParent(this);
	}
}

bool Gate::GetStatic()
{
	return isStatic;
}