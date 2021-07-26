#pragma once
#include"Math.h"
class Texture
{
private:
	ID2D1Bitmap* bitmap_;
public:
	Texture(const std::string& path);
	~Texture();

	ID2D1Bitmap* GetBitmap() const { return bitmap_; }
	Size2F GetSize();
	void Render(const Rect& visibleRect);
};