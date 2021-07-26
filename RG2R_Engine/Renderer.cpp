#include "stdafx.h"
#include "Renderer.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::SetZ_index(float index)
{
	this->z_index = index;
}

float Renderer::GetZ_index()
{
	return z_index;
}