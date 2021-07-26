#include "stdafx.h"
#include "TextureManager.h"

using namespace std::experimental::filesystem;

TextureManager::TextureManager()
	:isLoaded_(true), filesLoaded_(0), filesToLoadPerFrame_(0)
{
	CoInitializeEx(NULL, COINIT_MULTITHREADED);
	//wic factory를 생성한다.
	HR(
		CoCreateInstance(CLSID_WICImagingFactory, NULL,
			CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&wicFactory_))
	);
}

TextureManager::~TextureManager()
{
	for (auto iter : textures_)
		delete iter.second;

	wicFactory_->Release();
	CoUninitialize();
}

Texture* TextureManager::Load(const std::string & path)
{
	if (!exists(path))
		Trace(__FILE__, __LINE__, -1, "Texture file could not be found :" + path);

	if (!textures_[path])
	{
		textures_[path] = new Texture(path);
	}

	return textures_[path];
}

void TextureManager::Unload(const std::string & path)
{
	SafeDelete(textures_[path]);
}

void TextureManager::LoadAll(const std::string & rootPath, int fl)
{
	for (recursive_directory_iterator iter(rootPath); iter != recursive_directory_iterator(); ++iter)
	{
		if (iter->path().extension() == ".png" ||
			iter->path().extension() == ".dds" ||
			iter->path().extension() == ".jpg" ||
			iter->path().extension() == ".jpeg" ||
			iter->path().extension() == ".gif" ||
			iter->path().extension() == ".bmp")
			paths_.push_back(iter->path());
	}
	filesLoaded_ = 0;
	filesToLoadPerFrame_ = fl;
	pathIter_ = paths_.begin();
	isLoaded_ = false;
}

bool TextureManager::IsLoading()
{
	return !isLoaded_;
}

float TextureManager::GetProgressRate()
{
	if (isLoaded_) return 1.f;
	return (float)filesLoaded_ / paths_.size();
}

std::string TextureManager::GetCurrentLoadingPath()
{
	if (isLoaded_) return "Loaded!";

	return (*pathIter_).string();
}

void TextureManager::UnloadAll(const std::string & rootPath)
{
	std::list<path> paths;
	for (recursive_directory_iterator iter(rootPath); iter != recursive_directory_iterator(); ++iter)
	{
		if (iter->path().extension() == ".png" ||
			iter->path().extension() == ".dds" ||
			iter->path().extension() == ".jpg" ||
			iter->path().extension() == ".jpeg" ||
			iter->path().extension() == ".gif" ||
			iter->path().extension() == ".bmp")
			paths.push_back(iter->path());
	}
	for (auto& iter : paths)
	{
		SafeDelete(textures_[iter.string()]);
	}
}

void TextureManager::Update()
{
	if (isLoaded_) return;

	for (int i = 0; i < filesToLoadPerFrame_; i++)
	{
		Load((*pathIter_++).string());
		filesLoaded_++;
		if (pathIter_ == paths_.end())
		{
			isLoaded_ = true;
			paths_.clear();
			break;
		}
	}
}
