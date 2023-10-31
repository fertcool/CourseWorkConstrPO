#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include "stdafx.h"
#include <unordered_map> 

class TextureManager
{
	std::unordered_map<std::string, Texture*> tex_map;
	Texture* LoadTexture(std::string path);
public:
	TextureManager();
	~TextureManager();
	void add(std::string path);
	Texture* get(std::string path);
	void remove(std::string name);

};
#endif