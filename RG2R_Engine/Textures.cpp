#include "stdafx.h"
#include "Textures.h"
#include "Engine.h"

Textures::Textures()
{
}

Textures::~Textures()
{
}

Textures* Textures::PushTexture(const std::string& path)
{
	Texture* texture = RG2R_TextureM->Load(path);
	textures.push_back(texture);

	return this;
}

Texture* Textures::PopTexture()
{
	Texture* tex = textures[textures.size() - 1];
	textures.pop_back();

	return tex;
}

Texture* Textures::GetTexture(int index)
{
	return textures[index];
}

int Textures::GetSize()
{
	return textures.size();
}