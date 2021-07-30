#pragma once
#include <string>
#include <vector>
#include "Texture.h"

class Textures
{
private:
	std::vector<Texture*> textures;

public:
	Textures();
	~Textures();

	Textures* PushTexture(const std::string&);
	Textures* PushTexture(Texture* texture);
	Texture* PopTexture();
	Texture* GetTexture(int);
	int GetSize();
};